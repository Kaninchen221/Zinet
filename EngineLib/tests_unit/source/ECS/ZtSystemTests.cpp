#pragma once

#include "Zinet/Engine/ECS/ZtSystem.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::engine::ecs::tests
{
	class TestComponent : public Component
	{
	public:
		inline static const int startValue = 10;
		int value = startValue;
	};

	class SystemSimpleTests : public ::testing::Test
	{
	protected:

		using TestSystem = System<TestComponent>;
		TestSystem system;

		static_assert(std::is_default_constructible_v<TestSystem>);
		static_assert(std::is_copy_constructible_v<TestSystem>);
		static_assert(std::is_move_constructible_v<TestSystem>);
		static_assert(std::is_destructible_v<TestSystem>);
		static_assert(std::is_same_v<TestComponent, TestSystem::ComponentT>);
		static_assert(std::is_same_v<TestComponent*, TestSystem::ComponentHandleT>);
	};

	TEST_F(SystemSimpleTests, getComponents)
	{
		bool result = core::TestGetters<std::vector<TestComponent>, TestSystem>(&TestSystem::getComponents, &TestSystem::getComponents, system);
		ASSERT_TRUE(result); 
	}

	TEST_F(SystemSimpleTests, addComponent)
	{
		TestComponent simpleComponent;
		system.addComponent(simpleComponent);

		auto& components = system.getComponents();
		EXPECT_EQ(components.size(), 1u);
	}

	class SystemTests : public ::testing::Test
	{
	protected:

		System<TestComponent> system;

	};

	TEST_F(SystemTests, Pass)
	{

	}
}
