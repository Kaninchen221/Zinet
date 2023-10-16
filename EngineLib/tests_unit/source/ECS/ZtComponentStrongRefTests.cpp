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

		void createComponentStrongRef()
		{
			core::UniqueID componentID{ 2u };
			core::ID entityID{ 3u };
			componentStrongRef.create(std::move(componentID), entityID);
		}
	};

	TEST_F(ComponentStrongRefSimpleTests, Create)
	{
		createComponentStrongRef();
	}

	TEST_F(ComponentStrongRefSimpleTests, IsValid)
	{
		bool isValid = componentStrongRef.isValid();
		EXPECT_FALSE(isValid);

		createComponentStrongRef();
		isValid = componentStrongRef.isValid();
		EXPECT_TRUE(isValid);
	}

	TEST_F(ComponentStrongRefSimpleTests, Destroy)
	{
		createComponentStrongRef();
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

		createComponentStrongRef();
		component = componentStrongRef.operator->();
		EXPECT_TRUE(component);
	}

	TEST_F(ComponentStrongRefSimpleTests, Get)
	{
		Component* component = componentStrongRef.get();
		EXPECT_FALSE(component);

		createComponentStrongRef();
		component = componentStrongRef.get();
		EXPECT_TRUE(component);
	}

	TEST_F(ComponentStrongRefSimpleTests, CreateWeakRef)
	{
		ComponentWeakRef<Component> weakRef = componentStrongRef.createWeakRef();
	}
}