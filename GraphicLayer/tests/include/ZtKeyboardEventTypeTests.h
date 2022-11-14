#pragma once

#include "Zinet/GraphicLayer/ZtKeyboardEventType.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class ZtKeyboardEventTypeTests : public ::testing::Test
	{
	protected:

		KeyboardEventType keyboardEventType{};

	};

	TEST_F(ZtKeyboardEventTypeTests, ConstructionTest)
	{}

}