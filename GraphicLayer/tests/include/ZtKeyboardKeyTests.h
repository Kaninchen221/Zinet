#pragma once

#include "Zinet/GraphicLayer/ZtKeyboardKey.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtKeyboardKeyTests : public ::testing::Test
	{
	protected:

		KeyboardKey keyboardKey{};

	};

	TEST_F(ZtKeyboardKeyTests, ConstructTest)
	{}

}