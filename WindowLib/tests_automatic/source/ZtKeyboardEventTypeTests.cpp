#pragma once

#include "Zinet/Window/ZtKeyboardEventType.h"

#include <gtest/gtest.h>

namespace zt::wd::tests
{

	class KeyboardEventTypeTests : public ::testing::Test
	{
	protected:

		KeyboardEventType keyboardEventType{};

	};

	TEST_F(KeyboardEventTypeTests, Construction)
	{}

}