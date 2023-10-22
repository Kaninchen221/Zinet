#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"

#include "Zinet/Engine/ECS/ZtComponent.h"

namespace zt::engine::ecs
{
	template<std::derived_from<Component> ComponentType>
	class ComponentStrongRef;

	template<std::derived_from<Component> ComponentType>
	class ComponentWeakRef
	{
	public:

		using ComponentT = ComponentType;
		using ComponentStrongRefT = ComponentStrongRef<ComponentT>;

		ComponentWeakRef() = delete;
		ComponentWeakRef(ComponentStrongRefT* newComponentStrongRef);
		ComponentWeakRef(const ComponentWeakRef& other) = default;
		ComponentWeakRef(ComponentWeakRef&& other) = default;

		ComponentWeakRef& operator = (const ComponentWeakRef& other) = default;
		ComponentWeakRef& operator = (ComponentWeakRef&& other) = default;

		~ComponentWeakRef() noexcept = default;

		bool isValid() const;

		const ComponentT* get() const;
		ComponentT* get();

		const ComponentT* operator -> () const { return get(); }
		ComponentT* operator -> () { return get(); }

		const core::ID getOwnerID() const { return ownerID; }
		core::ID getOwnerID() { return ownerID; }

	protected:

		ComponentStrongRefT* componentStrongRef = nullptr;
		core::ID ownerID;

	};

	template<std::derived_from<Component> ComponentType>
	ComponentWeakRef<ComponentType>::ComponentWeakRef(ComponentStrongRefT* newComponentStrongRef)
		: componentStrongRef{ newComponentStrongRef }
	{
		if (componentStrongRef)
		{
			ownerID = componentStrongRef->getOwnerID();
		}
	}

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
		{
			bool isStrongRefValid = componentStrongRef->isValid();
			bool isEntityOwnerIDValid = (ownerID == componentStrongRef->getOwnerID());
			return isStrongRefValid && isEntityOwnerIDValid;
		}
		else
		{
			return false;
		}
	}

}

