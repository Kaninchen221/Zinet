#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"

#include "Zinet/Engine/ECS/ZtComponent.h"
#include "Zinet/Engine/ECS/ZtComponentStrongRef.h"

namespace zt::engine::ecs
{

	template<std::derived_from<Component> ComponentType>
	class ComponentWeakRef
	{
	public:

		using ComponentT = ComponentType;
		using ComponentStrongRefT = ComponentStrongRef<ComponentT>;

		ComponentWeakRef() = delete;
		ComponentWeakRef(ComponentStrongRefT* newComponentStrongRef) : componentStrongRef{ newComponentStrongRef } {}
		ComponentWeakRef(const ComponentWeakRef& other) = default;
		ComponentWeakRef(ComponentWeakRef&& other) = default;

		ComponentWeakRef& operator = (const ComponentWeakRef& other) = default;
		ComponentWeakRef& operator = (ComponentWeakRef&& other) = default;

		~ComponentWeakRef() = default;

		bool isValid() const;

		const ComponentT* get() const;
		ComponentT* get();

		const ComponentT* operator -> () const { return get(); }
		ComponentT* operator -> () { return get(); }

	protected:

		ComponentStrongRefT* componentStrongRef = nullptr;

	};

	template<std::derived_from<Component> ComponentType>
	typename const ComponentWeakRef<ComponentType>::ComponentT* ComponentWeakRef<ComponentType>::get() const
	{
		if (isValid())
			return componentStrongRef->get();
		else
			return nullptr;
	}

	template<std::derived_from<Component> ComponentType>
	typename ComponentWeakRef<ComponentType>::ComponentT* ComponentWeakRef<ComponentType>::get()
	{
		if (isValid())
			return componentStrongRef->get();
		else
			return nullptr;
	}

	template<std::derived_from<Component> ComponentType>
	bool ComponentWeakRef<ComponentType>::isValid() const
	{
		if (componentStrongRef)
			return componentStrongRef->isValid();
		else
			return false;
	}

}

