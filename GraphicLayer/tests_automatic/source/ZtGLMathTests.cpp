#pragma once

#include "Zinet/GraphicLayer/ZtGLMath.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{
	// TODO (low) Test it
	// TODO (low) Add From and To functions for Vector2, Vector3 and Vector4
	class MathTests : public ::testing::Test
	{
	protected:

		static_assert(!std::is_default_constructible_v<Math>);
		static_assert(!std::is_copy_constructible_v<Math>);
		static_assert(!std::is_move_constructible_v<Math>);
		static_assert(!std::is_copy_assignable_v<Math>);
		static_assert(!std::is_move_assignable_v<Math>);
		static_assert(!std::is_destructible_v<Math>);
	};

	TEST_F(MathTests, Pass)
	{

	}
}
