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
	// I know this class performance is shit but I wanted more nice interface than better performance for now
	template<class ComponentType>
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

		bool removeComponent(const core::UniqueID& id) { return core::Ensure(false); /*Not implemented*/ }

		virtual void update(core::Time elapsedTime) {}

	protected:

		std::vector<ComponentStrongRefT> components;
		size_t nextIDNumber = 0u;

	};

	template<class ComponentType>
	System<ComponentType>::ComponentWeakRefT System<ComponentType>::addComponent(const Entity& entity)
	{
// 		core::UniqueID id{ nextIDNumber };
// 		ComponentT* rawComponent = new ComponentT( std::move(id), entity.getUniqueID().createID() );
// 		std::shared_ptr<ComponentT> newComponent(rawComponent);
// 		auto& componentHandle = components.emplace_back(newComponent);
// 		return componentHandle;
		
		ComponentStrongRefT& strongRef = components.emplace_back();
		core::UniqueID uniqueID{ nextIDNumber };
		++nextIDNumber;
		strongRef.create(std::move(uniqueID), entity.getUniqueID().createID());

		return ComponentWeakRefT{ &strongRef };
	}

}

