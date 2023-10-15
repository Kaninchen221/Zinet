#pragma once

#include "Zinet/Engine/ECS/ZtComponentStrongRef.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::engine::ecs::tests
{

	class ComponentStrongRefSimpleTests : public ::testing::Test
	{
	protected:

		using ComponentStrongRefT = ComponentStrongRef<Component>;
		ComponentStrongRefT componentStrongRef;

		static_assert(std::is_default_constructible_v<ComponentStrongRefT>);
		static_assert(!std::is_copy_constructible_v<ComponentStrongRefT>);
		static_assert(!std::is_copy_assignable_v<ComponentStrongRefT>);
		static_assert(std::is_move_constructible_v<ComponentStrongRefT>);
		static_assert(std::is_move_assignable_v<ComponentStrongRefT>);
		static_assert(std::is_destructible_v<ComponentStrongRefT>);
	};

	TEST_F(ComponentStrongRefSimpleTests, Create)
	{
		componentStrongRef.create();
	}

	TEST_F(ComponentStrongRefSimpleTests, IsValid)
	{
		bool isValid = componentStrongRef.isValid();
		EXPECT_FALSE(isValid);

		componentStrongRef.create();
		isValid = componentStrongRef.isValid();
		EXPECT_TRUE(isValid);
	}

	TEST_F(ComponentStrongRefSimpleTests, Destroy)
	{
		componentStrongRef.create();
		bool isValid = componentStrongRef.isValid();
		ASSERT_TRUE(isValid);

		componentStrongRef.destroy();
		isValid = componentStrongRef.isValid();
		ASSERT_FALSE(isValid);
	}

	TEST_F(ComponentStrongRefSimpleTests, ArrowOperator)
	{
		Component* component = componentStrongRef.operator->();
		EXPECT_FALSE(component);

		componentStrongRef.create();
		component = componentStrongRef.operator->();
		EXPECT_TRUE(component);
	}

	TEST_F(ComponentStrongRefSimpleTests, Get)
	{
		Component* component = componentStrongRef.get();
		EXPECT_FALSE(component);

		componentStrongRef.create();
		component = componentStrongRef.get();
		EXPECT_TRUE(component);
	}

	class ComponentStrongRefTests : public ::testing::Test
	{
	protected:

		//ComponentStrongRef componentStrongRef;

	};

	TEST_F(ComponentStrongRefTests, Pass)
	{

	}
}