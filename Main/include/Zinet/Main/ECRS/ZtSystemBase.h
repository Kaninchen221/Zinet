#pragma once

#include "Zinet/Main/ZtMainConfig.h"
#include "Zinet/Main/ZtTime.h"

#include "Zinet/Main/ECRS/ZtEntity.h"

namespace zt {

	class ZINET_MAIN_API SystemBase {

	public:

		SystemBase() = default;
		SystemBase(const SystemBase& other) = default;
		SystemBase(SystemBase&& other) = default;

		SystemBase& operator = (const SystemBase& other) = default;
		SystemBase& operator = (SystemBase&& other) = default;
		
		~SystemBase() noexcept = default;

		virtual size_t scanEntity(Entity& entity) = 0;

		virtual void update(Time::Microseconds timeAfterLastUpdate) = 0;

	protected:

		virtual size_t scanComponents(Entity::Components& components);
		virtual void addComponent(const ComponentPtr& component);
		virtual bool isComponentInteresting(const ComponentPtr& component) const;

		virtual size_t scanResources(Entity::Resources& resources);
		virtual void addResource(const ResourcePtr& resource);
		virtual bool isResourceInteresting(const ResourcePtr& resource) const;

	};

}