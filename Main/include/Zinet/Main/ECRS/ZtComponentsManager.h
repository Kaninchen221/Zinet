#pragma once

#include "Zinet/Main/ZtMainConfig.h"
#include "Zinet/Main/ECRS/ZtComponent.h"
#include "Zinet/Main/ZtIdentificator.h"

#include <tuple>
#include <vector>
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

		ComponentsManager() = default;
		ComponentsManager(const ComponentsManager& other) = default;
		ComponentsManager(ComponentsManager&& other) = default;

		ComponentsManager& operator = (const ComponentsManager& other) = default;
		ComponentsManager& operator = (ComponentsManager&& other) = default;

		~ComponentsManager() noexcept = default;

		template<typename ComponentDerivedClass>
		Identificator createComponent(Identificator ownerIdentificator);

		template<typename ComponentDerivedClass>
		Identificator addComponent(const ComponentDerivedClass& component);

		template<typename ComponentDerivedClass>
		Container<ComponentDerivedClass>& getComponentsByType() noexcept;

		template<typename ComponentDerivedClass>
		ComponentDerivedClass* getComponentByIdentificator(Identificator identificator);

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
	inline Identificator ComponentsManager<ComponentTypes ...>::createComponent(Identificator ownerIdentificator)
	{
		MustBeOneOfComponentTypes<ComponentDerivedClass>();

		auto& componentsContainer = getComponentsByType<ComponentDerivedClass>();
		
		ComponentDerivedClass component(ownerIdentificator);
		auto itToInsertedComponent = componentsContainer.insert(component);
		auto componentId = itToInsertedComponent->getIdentificator();

		return componentId;
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
	Identificator ComponentsManager<ComponentTypes ...>::addComponent(const ComponentDerivedClass& component)
	{
		MustBeOneOfComponentTypes<ComponentDerivedClass>();

		auto& componentsContainer = getComponentsByType<ComponentDerivedClass>();

		auto insertedComponentIt = componentsContainer.insert(component);
		auto insertedComponentIdentificator = insertedComponentIt->getIdentificator();

		return insertedComponentIdentificator;
	}

	template<typename ...ComponentTypes>
	template<typename ComponentDerivedClass>
	inline ComponentDerivedClass* ComponentsManager<ComponentTypes ...>::getComponentByIdentificator(Identificator identificator) 
	{
		MustBeOneOfComponentTypes<ComponentDerivedClass>();

		auto& componentsContainer = getComponentsByType<ComponentDerivedClass>();

		auto findResult = findComponentByIdentificator<ComponentDerivedClass>(componentsContainer, identificator);

		if (isFoundComponentValid(componentsContainer, findResult)) {
			return &(*findResult);
		}

		return nullptr;
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


