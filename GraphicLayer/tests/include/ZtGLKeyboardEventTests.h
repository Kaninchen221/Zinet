#pragma once

#include "Zinet/GraphicLayer/ZtGLKeyboardEvent.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class KeyboardEventTests : public ::testing::Test
	{
	protected:

		KeyboardEvent keyboardEvent{};

	};

	TEST_F(KeyboardEventTests, Type)
	{
		[[maybe_unused]] KeyboardEventType type = keyboardEvent.type;
	}

	TEST_F(KeyboardEventTests, Key)
	{
		[[maybe_unused]] KeyboardKey key = keyboardEvent.key;
	}

}