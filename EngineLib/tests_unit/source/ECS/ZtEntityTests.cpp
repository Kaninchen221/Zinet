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
		static_assert(std::is_constructible_v<Entity, Types::EntityID>);
		static_assert(std::is_copy_constructible_v<Entity>);
		static_assert(std::is_move_constructible_v<Entity>);

	};

	TEST_F(EntitySimpleTests, InvalidID)
	{
		Types::EntityID invalidID = Entity::InvalidID;
		EXPECT_EQ(invalidID, std::numeric_limits<Types::EntityID>::max());
	}

	TEST_F(EntitySimpleTests, getID)
	{
		Types::EntityID id = entity.getID();
		EXPECT_EQ(id, Entity::InvalidID);

		Types::EntityID expectedID = 6u;
		Entity otherEntity{ expectedID };
		id = otherEntity.getID();
		EXPECT_EQ(id, expectedID);
	}
}
