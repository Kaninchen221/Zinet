#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"
#include "Zinet/Engine/ECS/ZtComponent.h"

#include "Zinet/Core/ZtDebug.h"
#include "Zinet/Core/ZtUniqueID.h"

#include <vector>
#include <memory>

namespace zt::engine::ecs
{
	// I know this class performance is shit but I wanted more nice interface than better performance
	template<class ComponentType>
	class System
	{
	public:

		using ComponentT = ComponentType;
		using ComponentWeakHandleT = std::weak_ptr<ComponentT>;
		using ComponentHandleT = std::shared_ptr<ComponentT>;

		static_assert(std::is_base_of_v<Component, ComponentT>);

		System() = default;
		System(const System& other) = default;
		System(System&& other) = default;

		System& operator = (const System& other) = default;
		System& operator = (System&& other) = default;

		~System() = default;

		std::vector<ComponentHandleT>& getComponents() { return components; }
		const std::vector<ComponentHandleT>& getComponents() const { return components; }

		ComponentHandleT addComponent();

		bool removeComponent(const core::UniqueID& id) { return core::Ensure(false); /*Not implemented*/ }

		virtual void update(core::Time elapsedTime) {}

	protected:

		std::vector<ComponentHandleT> components;
		size_t nextIDNumber = 0u;

	};

	template<class ComponentType>
	System<ComponentType>::ComponentHandleT System<ComponentType>::addComponent()
	{
		core::UniqueID id{ nextIDNumber };
		ComponentT* rawComponent = new ComponentT( std::move(id) );
		std::shared_ptr<ComponentT> newComponent(rawComponent);
		auto& componentHandle = components.emplace_back(newComponent);
		++nextIDNumber;
		return componentHandle;
	}

}

