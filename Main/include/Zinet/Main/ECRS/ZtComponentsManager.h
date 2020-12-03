#pragma once

#include "Zinet/Main/ZtMainConfig.h"
#include "Zinet/Main/ZtMainException.h"
#include "Zinet/Main/ECRS/ZtComponent.h"
#include "Zinet/Main/ZtIdentificator.h"

#include <tuple>
#include <type_traits>

#include "plf_colony.h"

namespace zt {

	template<typename ... ComponentTypes>
	class ZINET_MAIN_API ComponentsManager {

		static constexpr bool AreTypesDerivedFromComponent() noexcept;
		static_assert(AreTypesDerivedFromComponent(), "All ComponentTypes must derived from Component class");

		template<typename ComponentDerivedClass>
		static constexpr bool IsOneOfComponentTypes() noexcept;

		template<typename ComponentDerivedClass>
		static constexpr void MustBeOneOfComponentTypes() noexcept;

	public:

		template<typename T>
		using Container = plf::colony<T>;

		template<typename T>
		using Iterator = typename Container<T>::iterator;

		ComponentsManager() = default;
		ComponentsManager(const ComponentsManager& other) = default;
		ComponentsManager(ComponentsManager&& other) = default;

		ComponentsManager& operator = (const ComponentsManager& other) = default;
		ComponentsManager& operator = (ComponentsManager&& other) = default;

		~ComponentsManager() noexcept = default;

		template<typename ComponentDerivedClass>
		Iterator<ComponentDerivedClass> createComponent(Identificator ownerIdentificator);

		template<typename ComponentDerivedClass>
		Iterator<ComponentDerivedClass> addComponent(const ComponentDerivedClass& component);

		template<typename ComponentDerivedClass>
		Container<ComponentDerivedClass>& getComponentsByType() noexcept;

		template<typename ComponentDerivedClass>
		Iterator<ComponentDerivedClass> getComponentByIdentificator(Identificator identificator);

		template<typename ComponentDerivedClass>
		bool removeComponentByIdentificator(Identificator identificator);

		size_t removeAllComponentsByEntityOwnerIdentificator(Identificator ownerIdentificator);

	private:

		template<typename ComponentDerivedClass>
		typename Container<ComponentDerivedClass>::iterator findComponentByIdentificator(Container<ComponentDerivedClass>& container, Identificator identificator);

		template<typename ComponentDerivedClass>
		bool isFoundComponentValid(const Container<ComponentDerivedClass>& container, typename const Container<ComponentDerivedClass>::iterator& iterator) const;

		std::tuple<
			Container<typename ComponentTypes> ...
		> components;

	};

	template<typename ...ComponentTypes>
	inline size_t ComponentsManager<ComponentTypes ...>::removeAllComponentsByEntityOwnerIdentificator(Identificator ownerIdentificator)
	{
		size_t removedComponentsCount = 0u;

		auto wraper = [&](auto& container) -> void {

			auto it = container.begin();
			while (it != container.end()) {

				auto componentOwnerId = it->getOwnerIdentificator();
				if (componentOwnerId == ownerIdentificator) {
					auto newIt = container.erase(it);
					it = newIt;
					++removedComponentsCount;
				}
				else {
					++it;
				}

			}
		};

		(wraper(std::get<Container<ComponentTypes>>(components)), ...);

		return removedComponentsCount;
	}

	template<typename ...ComponentTypes>
	inline constexpr bool ComponentsManager<ComponentTypes ...>::AreTypesDerivedFromComponent() noexcept
	{
		return (std::is_base_of_v<Component, ComponentTypes> && ...);
	}

	template<typename ...ComponentTypes>
	template<typename ComponentDerivedClass>
	inline constexpr void ComponentsManager<ComponentTypes ...>::MustBeOneOfComponentTypes() noexcept
	{
		static_assert(IsOneOfComponentTypes<ComponentDerivedClass>(), 
			"ComponentDerivedClass must be on of the ComponentTypes");
	}

	template<typename ...ComponentTypes>
	template<typename ComponentDerivedClass>
	inline constexpr bool ComponentsManager<ComponentTypes ...>::IsOneOfComponentTypes() noexcept
	{
		return ((std::is_same<ComponentDerivedClass, ComponentTypes>::value) | ...);
	}

	template<typename ...ComponentTypes>
	template<typename ComponentDerivedClass>
	inline ComponentsManager<ComponentTypes ...>::Iterator<ComponentDerivedClass> ComponentsManager<ComponentTypes ...>::createComponent(Identificator ownerIdentificator)
	{
		MustBeOneOfComponentTypes<ComponentDerivedClass>();

		auto& componentsContainer = getComponentsByType<ComponentDerivedClass>();
		
		ComponentDerivedClass component(ownerIdentificator);
		auto itToInsertedComponent = componentsContainer.insert(component);
		
		return itToInsertedComponent;
	}

	template<typename ...ComponentTypes>
	template<typename ComponentDerivedClass>
	inline ComponentsManager<ComponentTypes ...>::Container<ComponentDerivedClass>& ComponentsManager<ComponentTypes ...>::getComponentsByType() noexcept
	{
		MustBeOneOfComponentTypes<ComponentDerivedClass>();

		auto& componentsContainer = std::get<Container<ComponentDerivedClass>>(components);

		return componentsContainer;
	}

	template<typename ...ComponentTypes>
	template<typename ComponentDerivedClass>
	ComponentsManager<ComponentTypes ...>::Iterator<ComponentDerivedClass> ComponentsManager<ComponentTypes ...>::addComponent(const ComponentDerivedClass& component)
	{
		MustBeOneOfComponentTypes<ComponentDerivedClass>();

		auto& componentsContainer = getComponentsByType<ComponentDerivedClass>();

		auto insertedComponentIt = componentsContainer.insert(component);

		return insertedComponentIt;
	}

	template<typename ...ComponentTypes>
	template<typename ComponentDerivedClass>
	inline ComponentsManager<ComponentTypes ...>::Iterator<ComponentDerivedClass> ComponentsManager<ComponentTypes ...>::getComponentByIdentificator(Identificator identificator)
	{
		MustBeOneOfComponentTypes<ComponentDerivedClass>();

		auto& componentsContainer = getComponentsByType<ComponentDerivedClass>();

		auto findResult = findComponentByIdentificator<ComponentDerivedClass>(componentsContainer, identificator);

		if (isFoundComponentValid(componentsContainer, findResult)) {
			return findResult;
		}

		throw MainException("Can't find component with id : " + std::to_string(identificator.getNumber()));
	}

	template<typename ...ComponentTypes>
	template<typename ComponentDerivedClass>
	inline bool ComponentsManager<ComponentTypes ...>::removeComponentByIdentificator(Identificator identificator) 
	{	
		MustBeOneOfComponentTypes<ComponentDerivedClass>();

		auto& componentsContainer = getComponentsByType<ComponentDerivedClass>();
		
		auto findResult = findComponentByIdentificator<ComponentDerivedClass>(componentsContainer, identificator);
		
		if (isFoundComponentValid(componentsContainer, findResult)) {
			componentsContainer.erase(findResult);
			return true;
		}

		return false;
	}

	template<typename ...ComponentTypes>
	template<typename ComponentDerivedClass>
	inline typename ComponentsManager<ComponentTypes ...>::Container<ComponentDerivedClass>::iterator ComponentsManager<ComponentTypes ...>::findComponentByIdentificator(Container<ComponentDerivedClass>& container, Identificator identificator) 
	{
		MustBeOneOfComponentTypes<ComponentDerivedClass>();
	
		for (auto elementIt = container.begin(); elementIt != container.end(); ++elementIt) {
			auto elementOwnerId = elementIt->getIdentificator();
			if (elementOwnerId == identificator) {
				return elementIt;
			}
		}

		return container.end();
	}

	template<typename ...ComponentTypes>
	template<typename ComponentDerivedClass>
	inline bool ComponentsManager<ComponentTypes ...>::isFoundComponentValid(const Container<ComponentDerivedClass>& container, typename const Container<ComponentDerivedClass>::iterator& iterator) const
	{
		MustBeOneOfComponentTypes<ComponentDerivedClass>();

		auto invalidIterator = container.end();

		if (iterator == invalidIterator) {
			return false;
		}
		else {
			return true;
		}
	}
}


