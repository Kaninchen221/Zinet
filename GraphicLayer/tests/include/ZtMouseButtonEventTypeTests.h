#pragma once

#include "Zinet/GraphicLayer/ZtMouseButtonEventType.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class ZtMouseButtonEventTypeTests : public ::testing::Test
	{
	protected:

		MouseButtonEventType mouseButtonEventType;

	};

	TEST_F(ZtMouseButtonEventTypeTests, AssignTest)
	{
		mouseButtonEventType = MouseButtonEventType::Pressed;
	}

}