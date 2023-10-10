#pragma once

#include "Zinet/Engine/ECS/ZtComponent.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::engine::ecs::tests
{

	class ComponentSimpleTests : public ::testing::Test
	{
	protected:

		Component component;

		static_assert(std::is_default_constructible_v<Component>);
		static_assert(std::is_copy_constructible_v<Component>);
		static_assert(std::is_move_constructible_v<Component>);
		static_assert(std::is_destructible_v<Component>);
	};

	TEST_F(ComponentSimpleTests, Pass)
	{

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

