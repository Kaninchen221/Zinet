#pragma once

#include "Zinet/Engine/ECS/ZtComponentWeakRef.h"
#include "Zinet/Engine/ECS/ZtComponentStrongRef.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::engine::ecs::tests
{

	class ComponentWeakRefSimpleTests : public ::testing::Test
	{
	protected:

		using ComponentWeakRefT = ComponentWeakRef<Component>;
		using ComponentStrongRefT = ComponentStrongRef<Component>;

		Component component;
		ComponentStrongRefT componentStrongRef;
		ComponentWeakRefT componentWeakRef{ nullptr };

		static_assert(!std::is_default_constructible_v<ComponentWeakRefT>);
		static_assert(std::is_copy_constructible_v<ComponentWeakRefT>);
		static_assert(std::is_copy_assignable_v<ComponentWeakRefT>);
		static_assert(std::is_move_constructible_v<ComponentWeakRefT>);
		static_assert(std::is_move_assignable_v<ComponentWeakRefT>);
		static_assert(std::is_destructible_v<ComponentWeakRefT>);

		void createComponentStrongRef()
		{
			core::UniqueID componentID{ 2u };
			core::ID entityID{ 3u };
			componentStrongRef.create(std::move(componentID), entityID);
		}
	};

	TEST_F(ComponentWeakRefSimpleTests, IsValid)
	{
		bool isValid = componentWeakRef.isValid();
		ASSERT_FALSE(isValid);

		createComponentStrongRef();
		componentWeakRef = ComponentWeakRefT{ &componentStrongRef };
		isValid = componentWeakRef.isValid();
		ASSERT_TRUE(isValid);
	}

	TEST_F(ComponentWeakRefSimpleTests, ArrowOperator)
	{
		Component* componentPtr = componentWeakRef.operator->();
		EXPECT_FALSE(componentPtr);

		createComponentStrongRef();
		componentWeakRef = ComponentWeakRefT{ &componentStrongRef };
		componentPtr = componentWeakRef.operator->();
		EXPECT_TRUE(componentPtr);
	}

	TEST_F(ComponentWeakRefSimpleTests, Get)
	{
		Component* componentPtr = componentWeakRef.get();
		EXPECT_FALSE(componentPtr);

		createComponentStrongRef();
		componentWeakRef = ComponentWeakRefT{ &componentStrongRef };
		componentPtr = componentWeakRef.get();
		EXPECT_TRUE(componentPtr);
	}
}
