#pragma once

#include "Zinet/Engine/ECS/ZtComponentWeakRef.hpp"
#include "Zinet/Engine/ECS/ZtComponentStrongRef.hpp"

#include "Zinet/Core/ZtTypeTraits.hpp"

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
		const core::ID entityID{ 3u };

		static_assert(!std::is_default_constructible_v<ComponentWeakRefT>);
		static_assert(std::is_copy_constructible_v<ComponentWeakRefT>);
		static_assert(std::is_copy_assignable_v<ComponentWeakRefT>);
		static_assert(std::is_move_constructible_v<ComponentWeakRefT>);
		static_assert(std::is_move_assignable_v<ComponentWeakRefT>);
		static_assert(std::is_destructible_v<ComponentWeakRefT>);

		void createComponentStrongRef()
		{
			core::UniqueID componentID{ 2u };
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

		componentStrongRef.invalidateOwnerID();
		isValid = componentWeakRef.isValid();
		ASSERT_FALSE(isValid);
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

	TEST_F(ComponentWeakRefSimpleTests, GetOwnerEntityID)
	{
		typedef core::ID(Component::* ExpectedFunction)() const;
		static_assert(core::IsFunctionEqual<ExpectedFunction>(&Component::getOwnerID));

		core::ID ownerEntityID = componentStrongRef.getOwnerID();
		EXPECT_EQ(ownerEntityID, core::ID::InvalidIDNumber);

		createComponentStrongRef();
		ownerEntityID = componentStrongRef.getOwnerID();
		EXPECT_EQ(ownerEntityID, entityID);
	}
}
