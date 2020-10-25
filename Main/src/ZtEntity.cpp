#include "Zinet/Main/ECRS/ZtEntity.h"

#include "Zinet/Main/ZtMainException.h"
#include "Zinet/Main/ZtLogger.h"

namespace zt {

	Entity::Entity()
	{
	}

	Entity::Entity(const Entity& other)
	{
		*this = other;
	}

	Entity::Entity(Entity&& other)
	{
		*this = std::move(other);
	}

	Entity& Entity::operator=(const Entity& other)
	{
		copyComponents(other.components);
		copyResources(other.resources);
		return *this;
	}

	Entity& Entity::operator=(Entity&& other)
	{
		moveComponents(other.components);
		moveResources(other.resources);
		return *this;
	}

	bool Entity::addComponent(const Key& name, ComponentPtr component)
	{
		return add<Components, ComponentPtr>(
			components,
			name,
			component
			);
	}

	Entity::ComponentPtr Entity::getComponent(const Key& name)
	{
		return get<Components, ComponentPtr>(components, name);
	}

	bool Entity::removeComponent(const Key& name)
	{
		return remove<Components>(components, name);
	}

	size_t Entity::componentsCount() const noexcept
	{
		return count<Components>(components);
	}

	bool Entity::addResource(const Key& name, ResourcePtr resource)
	{
		return add<Resources, ResourcePtr>(
			resources,
			name,
			resource
			);
	}

	Entity::ResourcePtr Entity::getResource(const Key& name)
	{
		return get<Resources, ResourcePtr>(resources, name);
	}

	bool Entity::removeResource(const Key& name)
	{
		return remove<Resources>(resources, name);
	}

	size_t Entity::resourcesCount() const noexcept
	{
		return count<Resources>(resources);
	}

	void Entity::copyComponents(const Components& componentsToCopy)
	{
		copy<Components>(componentsToCopy, components);
	}

	void Entity::copyResources(const Resources& resourcesToCopy)
	{
		copy<Resources>(resourcesToCopy, resources);
	}

	void Entity::moveComponents(Components& componentsToMove)
	{
		move<Components>(componentsToMove, this->components);
	}

	void Entity::moveResources(Resources& resourcesToMove)
	{
		move<Resources>(resourcesToMove, resources);
	}

}