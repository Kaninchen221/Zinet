#pragma once

#include "Zinet/Engine/ECS/ZtSystem.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::engine::ecs::tests
{
	class TestComponent : public Component
	{
	public:

		TestComponent(core::UniqueID&& uniqueID, core::ID entityID) : Component(std::move(uniqueID), entityID) {}

		inline static const int startValue = 10;
		int value = startValue;
	};

	class TestSystem : public System<TestComponent>
	{
	public:
		void update(core::Time elapsedTime) override {}
	};

	class SystemSimpleTests : public ::testing::Test
	{
	protected:

		using TestSystem = System<TestComponent>;
		TestSystem system;

		static_assert(std::is_default_constructible_v<TestSystem>);
		static_assert(std::is_copy_constructible_v<TestSystem>);
		static_assert(std::is_copy_assignable_v<TestSystem>);
		static_assert(std::is_move_constructible_v<TestSystem>);
		static_assert(std::is_move_assignable_v<TestSystem>);
		static_assert(std::is_destructible_v<TestSystem>);
		static_assert(std::is_same_v<TestComponent, TestSystem::ComponentT>);
		static_assert(std::is_same_v<std::weak_ptr<TestComponent>, TestSystem::ComponentWeakHandleT>);
		static_assert(std::is_same_v<std::shared_ptr<TestComponent>, TestSystem::ComponentHandleT>);
	};

	TEST_F(SystemSimpleTests, GetComponents)
	{
		bool result = core::TestGetters<std::vector<TestSystem::ComponentHandleT>, TestSystem>(&TestSystem::getComponents, &TestSystem::getComponents, system);
		ASSERT_TRUE(result); 
	}

	TEST_F(SystemSimpleTests, AddComponent)
	{
		const size_t entityUniqueIDNumber = 8u;
		core::UniqueID entityUniqueID{ entityUniqueIDNumber };
		const Entity entity{ std::move(entityUniqueID) };
		TestSystem::ComponentHandleT component = system.addComponent(entity);
		EXPECT_TRUE(component);

		component = system.addComponent(entity);
		EXPECT_TRUE(component);

		const auto& components = system.getComponents();
		ASSERT_EQ(components.size(), 2u);
		EXPECT_TRUE(components[0]->getUniqueID() == 0u);
		EXPECT_TRUE(components[0]->getOwnerEntityID() == entityUniqueIDNumber);
		EXPECT_TRUE(components[1]->getUniqueID() == 1u);
		EXPECT_TRUE(components[1]->getOwnerEntityID() == entityUniqueIDNumber);
	}

	TEST_F(SystemSimpleTests, RemoveComponent)
	{
		core::UniqueID id{ 5u };
		EXPECT_DEBUG_DEATH(system.removeComponent(id), "");
	}

	TEST_F(SystemSimpleTests, Update)
	{
		core::Time elapsedTime;
		system.update(elapsedTime);
	}
}
