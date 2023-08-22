#pragma once

#include "Zinet/Engine/ZtLoop.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class LoopTests : public ::testing::Test
	{
	protected:

		Loop loop;
	};

	TEST_F(LoopTests, GetRenderer)
	{
		EXPECT_TRUE(zt::core::TestGetters(&Loop::getRenderer, &Loop::getRenderer, loop));
	}
}
