#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"
#include "Zinet/Engine/ECS/ZtComponent.h"

#include <vector>

namespace zt::engine::ecs
{
	template<class ComponentType>
	class System
	{
	public:

		using ComponentT = ComponentType;
		using ComponentHandleT = ComponentT*;

		System() = default;
		System(const System& other) = default;
		System(System&& other) = default;

		System& operator = (const System& other) = default;
		System& operator = (System&& other) = default;

		~System() = default;

		std::vector<ComponentT>& getComponents() { return components; }
		const std::vector<ComponentT>& getComponents() const { return components; }

		void addComponent(ComponentT& component);

	protected:

		std::vector<ComponentT> components;

	};

	template<class ComponentType>
	void System<ComponentType>::addComponent(ComponentT& component)
	{
		components.push_back(component);
	}

}

