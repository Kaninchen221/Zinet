#pragma once

#include "Zinet/Engine/ZtFlipbook.hpp"

#include <gtest/gtest.h>

namespace zt::engine::tests
{

	class FlipbookSimpleTests : public ::testing::Test
	{
	protected:

		static_assert(std::is_base_of_v<gl::Flipbook, engine::Flipbook>);
		static_assert(std::is_default_constructible_v<Flipbook>);

		static_assert(std::is_copy_constructible_v<Flipbook>);
		static_assert(std::is_copy_assignable_v<Flipbook>);

		static_assert(std::is_move_constructible_v<Flipbook>);
		static_assert(std::is_move_assignable_v<Flipbook>);

		void SetUp() override
		{
		}

		void TearDown() override
		{
		}
	};

	TEST_F(FlipbookSimpleTests, Pass)
	{
	}

}