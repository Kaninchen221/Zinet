#pragma once

#include "Zinet/GraphicLayer/ZtGLMouseButtonEventType.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class MouseButtonEventTypeTests : public ::testing::Test
	{
	protected:

		MouseButtonEventType mouseButtonEventType;

	};

	TEST_F(MouseButtonEventTypeTests, Assign)
	{
		mouseButtonEventType = MouseButtonEventType::Pressed;
	}

}