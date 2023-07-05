#pragma once

#include "Zinet/GraphicLayer/ZtGLMouseButton.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
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