#pragma once

#include "Zinet/Window/ZtMouseButtonEvent.h"

#include <gtest/gtest.h>

namespace zt::window::tests
{

	class MouseButtonEventTests : public ::testing::Test
	{
	protected:

		MouseButtonEvent mouseButtonEvent;

	};

	TEST_F(MouseButtonEventTests, Button)
	{
		mouseButtonEvent.button = MouseButton();
	}

	TEST_F(MouseButtonEventTests, Type)
	{
		mouseButtonEvent.type = MouseButtonEventType();
	}

	TEST_F(MouseButtonEventTests, Compare)
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