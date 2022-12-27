#pragma once

#include "Zinet/GraphicLayer/ZtGLKeyboardEventType.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class KeyboardEventTypeTests : public ::testing::Test
	{
	protected:

		KeyboardEventType keyboardEventType{};

	};

	TEST_F(KeyboardEventTypeTests, Construction)
	{}

}