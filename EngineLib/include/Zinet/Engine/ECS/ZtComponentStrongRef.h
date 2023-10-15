#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"

#include "Zinet/Engine/ECS/ZtComponent.h"

#include <optional>
#include <type_traits>

namespace zt::engine::ecs
{
	template<std::derived_from<Component> ComponentType>
	class ComponentStrongRef
	{
		using ComponentT = ComponentType;

	public:
		ComponentStrongRef() = default;
		ComponentStrongRef(const ComponentStrongRef& other) = default;
		ComponentStrongRef(ComponentStrongRef&& other) = default;
		
		ComponentStrongRef& operator = (const ComponentStrongRef& other) = default;
		ComponentStrongRef& operator = (ComponentStrongRef&& other) = default;
		
		~ComponentStrongRef() = default;
	
		void create() { component = std::make_optional<ComponentT>(); }

		bool isValid() const { return component.has_value(); }

		void destroy() { component.reset(); }

		const ComponentT* get() const;
		ComponentT* get();

		const ComponentT* operator -> () const { return get(); }
		ComponentT* operator -> () { return get(); }

	protected:

		std::optional<ComponentT> component;

	};

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

