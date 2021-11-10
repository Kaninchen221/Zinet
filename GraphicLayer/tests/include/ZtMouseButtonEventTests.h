#pragma once

#include "Zinet/GraphicLayer/ZtMouseButtonEvent.h"

#include "gtest/gtest.h"

class ZtMouseButtonEventTests : public ::testing::Test
{
protected:

	ZtMouseButtonEvent MouseButtonEvent;

};

TEST_F(ZtMouseButtonEventTests, ButtonTest)
{
	MouseButtonEvent.Button = ZtMouseButton();
}

TEST_F(ZtMouseButtonEventTests, TypeTest)
{
	MouseButtonEvent.Type = ZtMouseButtonEventType();
}

TEST_F(ZtMouseButtonEventTests, CompareTest)
{
	MouseButtonEvent.Button = ZtMouseButton::MIDDLE;
	MouseButtonEvent.Type = ZtMouseButtonEventType::Released;

	ZtMouseButtonEvent Other;
	Other.Button = ZtMouseButton::MIDDLE;
	Other.Type = ZtMouseButtonEventType::Released;

	bool AreEqual = MouseButtonEvent == Other;
	ASSERT_TRUE(AreEqual);
}