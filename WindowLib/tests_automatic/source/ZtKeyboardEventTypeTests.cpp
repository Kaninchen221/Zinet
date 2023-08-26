#pragma once

#include "Zinet/Window/ZtKeyboardEventType.h"

#include <gtest/gtest.h>

namespace zt::window::tests
{

	class KeyboardEventTypeTests : public ::testing::Test
	{
	protected:

		KeyboardEventType keyboardEventType{};

	};

	TEST_F(KeyboardEventTypeTests, Construction)
	{}

}