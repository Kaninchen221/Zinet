#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"
#include "Zinet/Engine/ECS/ZtComponent.h"
#include "Zinet/Engine/ECS/ZtEntity.h"
#include "Zinet/Engine/ECS/ZtComponentWeakRef.h"
#include "Zinet/Engine/ECS/ZtComponentStrongRef.h"

#include "Zinet/Core/ZtDebug.h"
#include "Zinet/Core/ZtIDTypes.h"

#include <vector>
#include <memory>

namespace zt::engine::ecs
{
	template<std::derived_from<Component> ComponentType>
	class System
	{
	public:

		using ComponentT = ComponentType;
		using ComponentWeakRefT = ComponentWeakRef<ComponentT>;
		using ComponentStrongRefT = ComponentStrongRef<ComponentT>;

		static_assert(std::is_base_of_v<Component, ComponentT>);

		System() = default;
		System(const System& other) = default;
		System(System&& other) = default;

		System& operator = (const System& other) = default;
		System& operator = (System&& other) = default;

		~System() = default;

		std::vector<ComponentStrongRefT>& getComponents() { return components; }
		const std::vector<ComponentStrongRefT>& getComponents() const { return components; }

		ComponentWeakRefT addComponent(const Entity& entity);

		bool destroyComponent(const core::ID& ownerID);

		virtual void update(core::Time elapsedTime) {}

	protected:

		std::vector<ComponentStrongRefT> components;
		size_t nextIDNumber = 0u;

	};

	template<std::derived_from<Component> ComponentType>
	System<ComponentType>::ComponentWeakRefT System<ComponentType>::addComponent(const Entity& entity)
	{
		ComponentStrongRefT& strongRef = components.emplace_back();
		core::UniqueID uniqueID{ nextIDNumber };
		++nextIDNumber;
		strongRef.create(std::move(uniqueID), entity.getUniqueID().createID());

		return ComponentWeakRefT{ &strongRef };
	}

	template<std::derived_from<Component> ComponentType>
	bool System<ComponentType>::destroyComponent(const core::ID& ownerID)
	{
		for (auto& componentStrongRef : components)
		{
			if (componentStrongRef.getOwnerID() == ownerID)
			{
				componentStrongRef.destroy();
				return true;
			}
		}

		return false;
	}

}

