#pragma once

#include "Zinet/Engine/ECS/ZtComponent.hpp"

#include "Zinet/Core/ZtTypeTraits.hpp"

#include <gtest/gtest.h>

#include <utility>

namespace zt::engine::ecs::tests
{
	class TestComponent : public Component
	{
	public:
		void update(core::Time elapsedTime) override {}

		bool isReadyToUse() const override { return Component::isReadyToUse(); }
	};

	class ComponentSimpleTests : public ::testing::Test
	{
	protected:

		const size_t expectedID = 5u;
		const size_t expectedEntityID = 7u;
		ComponentSimpleTests() : component{ core::UniqueID{expectedID}, core::ID{expectedEntityID} } {}

		Component component;

		static_assert(std::is_default_constructible_v<Component>);
		static_assert(std::is_constructible_v<Component, core::UniqueID, core::ID>);
		static_assert(!std::is_copy_constructible_v<Component>);
		static_assert(!std::is_copy_assignable_v<Component>);
		static_assert(std::is_move_constructible_v<Component>);
		static_assert(std::is_move_assignable_v<Component>);
		static_assert(std::is_destructible_v<Component>);
	};

	TEST_F(ComponentSimpleTests, Update)
	{
		core::Time elapsedTime;
		component.update(elapsedTime);
	}

	TEST_F(ComponentSimpleTests, GetUniqueID)
	{
		typedef const core::UniqueID& (Component::* ExpectedFunction)() const;
		static_assert(core::IsFunctionEqual<ExpectedFunction>(&Component::getUniqueID));

		const core::UniqueID& uniqueID = component.getUniqueID();
		EXPECT_EQ(uniqueID.getNumber(), expectedID);
	}

	TEST_F(ComponentSimpleTests, GetOwnerEntityID)
	{
		typedef core::ID (Component::* ExpectedFunction)() const;
		static_assert(core::IsFunctionEqual<ExpectedFunction>(&Component::getOwnerID));

		core::ID ownerEntityID = component.getOwnerID();
		EXPECT_EQ(ownerEntityID, expectedEntityID);
	}

	TEST_F(ComponentSimpleTests, IsReadyToUse)
	{
		const bool isReadyToUse = component.isReadyToUse();
		EXPECT_TRUE(isReadyToUse);
	}

	class ComponentTests : public ::testing::Test
	{
	protected:

		Component component;

	};

	TEST_F(ComponentTests, Pass)
	{

	}
}

