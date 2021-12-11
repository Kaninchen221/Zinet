#pragma once

#include "Zinet/GraphicLayer/ZtMouseButton.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtMouseButtonTests : public ::testing::Test
	{
	protected:

		MouseButton button;

	};

	TEST_F(ZtMouseButtonTests, AssignTest)
	{
		button = MouseButton::RIGHT;
	}

}