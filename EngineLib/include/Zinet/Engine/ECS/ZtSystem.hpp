#pragma once

#include "Zinet/Engine/ZtEngineConfig.hpp"
#include "Zinet/Engine/ECS/ZtComponent.hpp"
#include "Zinet/Engine/ECS/ZtEntity.hpp"
#include "Zinet/Engine/ECS/ZtComponentWeakRef.hpp"
#include "Zinet/Engine/ECS/ZtComponentStrongRef.hpp"

#include "Zinet/Core/ZtDebug.hpp"
#include "Zinet/Core/ZtIDTypes.hpp"

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
		System(const System& other) = delete;
		System(System&& other) = default;

		System& operator = (const System& other) = delete;
		System& operator = (System&& other) = default;

		~System() noexcept = default;

		std::vector<ComponentStrongRefT>& getComponents() { return componentsStrongRefs; }
		const std::vector<ComponentStrongRefT>& getComponents() const { return componentsStrongRefs; }

		ComponentWeakRefT addComponent(const Entity& entity);

		bool destroyComponent(const core::ID& ownerID);

		virtual bool initialize() { return true; }

		virtual void preUpdate(core::Time elapsedTime);

		virtual void update(core::Time elapsedTime);

		virtual void postUpdate(core::Time elapsedTime);

	protected:

		std::vector<ComponentStrongRefT> componentsStrongRefs;
		size_t nextIDNumber = 0u;

		ComponentWeakRefT tryRecreateComponent(const Entity& entity);
		ComponentStrongRefT& createNewComponent(const Entity& entity);
		
	};

	template<std::derived_from<Component> ComponentType>
	System<ComponentType>::ComponentWeakRefT System<ComponentType>::addComponent(const Entity& entity)
	{
		ComponentWeakRefT weakRef = tryRecreateComponent(entity);
		if (weakRef.isValid())
			return weakRef;

		return createNewComponent(entity).createWeakRef();
	}

	template<std::derived_from<Component> ComponentType>
	bool System<ComponentType>::destroyComponent(const core::ID& ownerID)
	{
		for (auto& componentStrongRef : componentsStrongRefs)
		{
			if (componentStrongRef.getOwnerID() == ownerID)
			{
				componentStrongRef.destroy();
				return true;
			}
		}

		return false;
	}

	template<std::derived_from<Component> ComponentType>
	void System<ComponentType>::preUpdate(core::Time elapsedTime)
	{
		for (auto& component : componentsStrongRefs)
		{
			if (component.isValid())
			{
				component->preUpdate(elapsedTime);
			}
		}
	}

	template<std::derived_from<Component> ComponentType>
	void System<ComponentType>::update(core::Time elapsedTime)
	{
		for (auto& component : componentsStrongRefs)
		{
			if (component.isValid())
			{
				component->update(elapsedTime);
			}
		}
	}

	template<std::derived_from<Component> ComponentType>
	void System<ComponentType>::postUpdate(core::Time elapsedTime)
	{
		for (auto& component : componentsStrongRefs)
		{
			if (component.isValid())
			{
				component->postUpdate(elapsedTime);
			}
		}
	}

	template<std::derived_from<Component> ComponentType>
	System<ComponentType>::ComponentWeakRefT System<ComponentType>::tryRecreateComponent(const Entity& entity)
	{
		for (size_t uniqueIDNumber = 0u; auto& componentStrongRef : componentsStrongRefs)
		{
			if (!componentStrongRef.isValid())
			{
				core::UniqueID uniqueID{ uniqueIDNumber };
				componentStrongRef.create(std::move(uniqueID), entity.getUniqueID().createID());
				return componentStrongRef.createWeakRef();
			}

			++uniqueIDNumber;
		}

		return ComponentWeakRefT{ nullptr };
	}

	template<std::derived_from<Component> ComponentType>
	typename System<ComponentType>::ComponentStrongRefT& System<ComponentType>::createNewComponent(const Entity& entity)
	{
		ComponentStrongRefT& strongRef = componentsStrongRefs.emplace_back();
		core::UniqueID uniqueID{ nextIDNumber };
		++nextIDNumber;
		strongRef.create(std::move(uniqueID), entity.getUniqueID().createID());

		return strongRef;
	}
}

