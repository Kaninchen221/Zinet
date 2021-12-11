#pragma once

#include "Zinet/GraphicLayer/ZtKeyboardEvent.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtKeyboardEventTests : public ::testing::Test
	{
	protected:

		KeyboardEvent keyboardEvent{};

	};

	TEST_F(ZtKeyboardEventTests, TypeTest)
	{
		KeyboardEventType Type = keyboardEvent.Type;
	}

	TEST_F(ZtKeyboardEventTests, KeyTest)
	{
		KeyboardKey Key = keyboardEvent.Key;
	}

}