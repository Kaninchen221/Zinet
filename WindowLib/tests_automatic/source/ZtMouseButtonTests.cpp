#pragma once

#include "Zinet/Window/ZtMouseButton.h"

#include <gtest/gtest.h>

namespace zt::window::tests
{

	class MouseButtonTests : public ::testing::Test
	{
	protected:

		MouseButton button;

	};

	TEST_F(MouseButtonTests, Assign)
	{
		button = MouseButton::RIGHT;
	}

}