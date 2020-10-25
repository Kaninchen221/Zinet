#pragma once

#include "Zinet/Main/ZtMainConfig.h"
#include "Zinet/Main/ECRS/ZtComponentBase.h"
#include "Zinet/Main/ECRS/ZtResourceBase.h"

#include <vector>
#include <memory>
#include <map>
#include <string>
#include <type_traits>

namespace zt {

	class ZINET_MAIN_API Entity final {

		inline static std::string LoggerName = "Entity";

	public:

		using Key = std::string;

		using ComponentPtr = std::shared_ptr<ComponentBase>;
		using Components = std::map<Key, ComponentPtr>;

		using ResourcePtr = std::shared_ptr<ResourceBase>;
		using Resources = std::map<Key, ResourcePtr>;

		Entity();
		Entity(const Entity& other);
		Entity(Entity&& other);

		Entity& operator = (const Entity& other);
		Entity& operator = (Entity&& other);

		~Entity() noexcept = default;

		bool addComponent(const Key& name, ComponentPtr component);
		ComponentPtr getComponent(const Key& name);
		bool removeComponent(const Key& name);
		size_t componentsCount() const noexcept;

		bool addResource(const Key& name, ResourcePtr resource);
		ResourcePtr getResource(const Key& name);
		bool removeResource(const Key& name);
		size_t resourcesCount() const noexcept;

	private:

		template<class Container, class Element>
		bool add(Container& container, const Key& name, Element elementToAdd);

		template<class Container>
		bool remove(Container& container, const Key& name);

		template<class Container, class Element>
		Element get(Container& container, const Key& name);

		template<class Container>
		size_t count(const Container& container) const;

		void copyComponents(const Components& componentsToCopy);
		void copyResources(const Resources& resourcesToCopy);

		template<class Container>
		void copy(const Container& source, Container& target);

		void moveComponents(Components& componentsToMove);
		void moveResources(Resources& resourcesToMove);

		template<class Container>
		void move(Container& source, Container& target);
			
		Components components;
		Resources resources;

	};

	template<class Container, class Element>
	inline bool Entity::add(Container& container, const Key& name, Element elementToAdd)
	{
		thread_local std::string errorMessage = "Can't add element : ";

		using InsertResult = decltype(container.insert({ name, elementToAdd }));
		InsertResult result;

		try {
			result = container.insert({ name, elementToAdd });
		}
		catch (const std::exception& ex) {
			throw MainException(errorMessage + ex.what());
		}

		if (!result.second) {
			Logger::Warn(LoggerName, errorMessage + "element already exists");
		}

		return result.second;
	}

	template<class Container>
	inline bool Entity::remove(Container& container, const Key& name)
	{
		thread_local std::string errorMessage = "Can't remove element : ";

		using RemoveResult = decltype(container.erase(name));
		RemoveResult result;

		try {
			result = container.erase(name);
		}
		catch (const std::exception& ex) {
			throw zt::MainException(errorMessage + ex.what());
		}

		if (result == 0u) {
			Logger::Warn(LoggerName, errorMessage + name + " doesn't exists");
			return false;
		}

		return true;
	}

	template<class Container, class Element>
	inline Element Entity::get(Container& container, const Key& name)
	{
		thread_local std::string errorMessage = "Can't get element : ";

		using FindResult = decltype(container.find(name));
		FindResult result;

		try {
			result = container.find(name);
		}
		catch (const std::exception& ex) {
			throw MainException(errorMessage + ex.what());
		}

		if (result == container.end()) {
			Logger::Warn(LoggerName, errorMessage + "no such element is found");
			return Element();
		}

		return result->second;
	}

	template<class Container>
	inline size_t Entity::count(const Container& container) const
	{
		return container.size();
	}

	template<class Container>
	inline void Entity::copy(const Container& container, Container& target)
	{
		for (const auto& pair : container) {

			using RawElement = decltype(*pair.second);
			using Element = decltype(pair.second);

			auto name = pair.first;
			auto copyOf = pair.second->getCopy();

			target.insert({ name, copyOf });

		}
	}

	template<class Container>
	inline void Entity::move(Container& source, Container& target)
	{
		target = std::move(source);
	}

}