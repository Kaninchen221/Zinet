#pragma once

#include "Zinet/Engine/ECS/ZtComponent.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

#include <utility>

namespace zt::engine::ecs::tests
{
	class TestComponent : public Component
	{
	public:
		void update(core::Time elapsedTime) override {}
	};

	class ComponentSimpleTests : public ::testing::Test
	{
	protected:

		const size_t expectedID = 5u;
		ComponentSimpleTests() : component{ core::UniqueID{expectedID} } {}

		Component component;

		static_assert(std::is_default_constructible_v<Component>);
		static_assert(std::is_constructible_v<Component, core::UniqueID>);
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

	TEST_F(ComponentSimpleTests, GetID)
	{
		typedef const core::UniqueID& (Component::* ExpectedFunction)() const;
		static_assert(core::IsFunctionEqual<ExpectedFunction>(&Component::getID));

		const core::UniqueID& id = component.getID();
		EXPECT_EQ(id.getNumber(), expectedID);
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

