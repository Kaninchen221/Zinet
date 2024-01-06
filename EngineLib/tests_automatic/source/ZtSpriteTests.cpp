#pragma once

#include "Zinet/Engine/ZtSprite.hpp"

#include <gtest/gtest.h>

namespace zt::engine::tests
{

	class SpriteSimpleTests : public ::testing::Test
	{
	protected:

		static_assert(std::is_base_of_v<gl::Sprite, engine::Sprite>);
		static_assert(std::is_default_constructible_v<Sprite>);

		static_assert(std::is_copy_constructible_v<Sprite>);
		static_assert(std::is_copy_assignable_v<Sprite>);

		static_assert(std::is_move_constructible_v<Sprite>);
		static_assert(std::is_move_assignable_v<Sprite>);

		void SetUp() override
		{
		}

		void TearDown() override
		{
		}
	};

	TEST_F(SpriteSimpleTests, Pass)
	{
	}

}