#pragma once

#include "Zinet/GraphicLayer/ZtMouseButtonEvent.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtMouseButtonEventTests : public ::testing::Test
	{
	protected:

		MouseButtonEvent mouseButtonEvent;

	};

	TEST_F(ZtMouseButtonEventTests, ButtonTest)
	{
		mouseButtonEvent.button = MouseButton();
	}

	TEST_F(ZtMouseButtonEventTests, TypeTest)
	{
		mouseButtonEvent.type = MouseButtonEventType();
	}

	TEST_F(ZtMouseButtonEventTests, CompareTest)
	{
		mouseButtonEvent.button = MouseButton::MIDDLE;
		mouseButtonEvent.type = MouseButtonEventType::Released;

		MouseButtonEvent other;
		other.button = MouseButton::MIDDLE;
		other.type = MouseButtonEventType::Released;

		bool areEqual = mouseButtonEvent == other;
		ASSERT_TRUE(areEqual);
	}

}