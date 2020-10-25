#include "Zinet/Main/ECRS/ZtSystemBase.h"

namespace zt {

	size_t SystemBase::scanComponents(Entity::Components& components) {
		return 0u;
	}

	void SystemBase::addComponent(const ComponentPtr& component)
	{
	}

	bool SystemBase::isComponentInteresting(const ComponentPtr& component) const
	{
		return false;
	}

	size_t SystemBase::scanResources(Entity::Resources& resources) {
		return 0u;
	}

	void SystemBase::addResource(const ResourcePtr& resource)
	{
	}

	bool SystemBase::isResourceInteresting(const ResourcePtr& resource) const
	{
		return false;
	}
}