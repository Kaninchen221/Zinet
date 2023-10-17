#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"

#include "Zinet/Engine/ECS/ZtComponent.h"
#include "Zinet/Engine/ECS/ZtComponentWeakRef.h"

#include <optional>
#include <type_traits>

namespace zt::engine::ecs
{
	template<std::derived_from<Component> ComponentType>
	class ComponentStrongRef
	{

	public:

		using ComponentT = ComponentType;
		using ComponentWeakRefT = ComponentWeakRef<ComponentT>;

		ComponentStrongRef() = default;
		ComponentStrongRef(const ComponentStrongRef& other) = default;
		ComponentStrongRef(ComponentStrongRef&& other) = default;
		
		ComponentStrongRef& operator = (const ComponentStrongRef& other) = default;
		ComponentStrongRef& operator = (ComponentStrongRef&& other) = default;
		
		~ComponentStrongRef() = default;
	
		void create(core::UniqueID&& newUniqueID, core::ID newOwnerID);

		bool isValid() const { return component.has_value(); }

		void destroy() { component.reset(); }

		const ComponentT* get() const;
		ComponentT* get();

		const ComponentT* operator -> () const { return get(); }
		ComponentT* operator -> () { return get(); }

		ComponentWeakRefT createWeakRef();

		const core::ID getOwnerID() const { return ownerID; }
		core::ID getOwnerID() { return ownerID; }

		void invalidateOwnerID() { ownerID = core::ID{}; }

	protected:

		std::optional<ComponentT> component;
		core::ID ownerID;

	};

	template<std::derived_from<Component> ComponentType>
	ComponentWeakRef<ComponentType> ComponentStrongRef<ComponentType>::createWeakRef()
	{
		return ComponentWeakRefT{ this };
	}

	template<std::derived_from<Component> ComponentType>
	void ComponentStrongRef<ComponentType>::create(core::UniqueID&& newUniqueID, core::ID entityID)
	{
		component = std::make_optional<ComponentT>(std::move(newUniqueID), entityID);
		ownerID = entityID;
	}

	template<std::derived_from<Component> ComponentType>
	typename const ComponentStrongRef<ComponentType>::ComponentT* ComponentStrongRef<ComponentType>::get() const
	{
		if (isValid())
			return &component.value();
		else
			return nullptr;
	}

	template<std::derived_from<Component> ComponentType>
	typename ComponentStrongRef<ComponentType>::ComponentT* ComponentStrongRef<ComponentType>::get()
	{
		if (isValid())
			return &component.value();
		else
			return nullptr;
	}
}

