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
		mouseButtonEvent.Button = MouseButton();
	}

	TEST_F(ZtMouseButtonEventTests, TypeTest)
	{
		mouseButtonEvent.Type = MouseButtonEventType();
	}

	TEST_F(ZtMouseButtonEventTests, CompareTest)
	{
		mouseButtonEvent.Button = MouseButton::MIDDLE;
		mouseButtonEvent.Type = MouseButtonEventType::Released;

		MouseButtonEvent Other;
		Other.Button = MouseButton::MIDDLE;
		Other.Type = MouseButtonEventType::Released;

		bool AreEqual = mouseButtonEvent == Other;
		ASSERT_TRUE(AreEqual);
	}

}