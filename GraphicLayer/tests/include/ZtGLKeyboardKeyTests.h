#pragma once

#include "Zinet/GraphicLayer/ZtGLKeyboardKey.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class KeyboardKeyTests : public ::testing::Test
	{
	protected:

		KeyboardKey keyboardKey{};

	};

	TEST_F(KeyboardKeyTests, Construct)
	{}

}