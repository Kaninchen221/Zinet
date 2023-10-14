#pragma once

#include "Zinet/Engine/ECS/ZtEntity.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>
#include "gtest/internal/gtest-filepath.h"

namespace zt::engine::ecs::tests
{

	class EntitySimpleTests : public ::testing::Test
	{
	protected:

		Entity entity;

		static_assert(std::is_default_constructible_v<Entity>);
		static_assert(std::is_constructible_v<Entity, core::UniqueID>);
		static_assert(!std::is_copy_constructible_v<Entity>);
		static_assert(!std::is_copy_assignable_v<Entity>);
		static_assert(std::is_move_constructible_v<Entity>);
		static_assert(std::is_move_assignable_v<Entity>);
		static_assert(std::is_destructible_v<Entity>);
	};

	TEST_F(EntitySimpleTests, getID)
	{
		typedef const core::UniqueID& (Entity::* ExpectedFunction)() const;
		static_assert(core::IsFunctionEqual<ExpectedFunction>(&Entity::getID));

		const core::UniqueID& id = entity.getID();
		EXPECT_EQ(id, core::UniqueID::InvalidIDNumber);

	}
}
