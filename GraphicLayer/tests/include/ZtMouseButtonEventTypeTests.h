#pragma once

#include "Zinet/GraphicLayer/ZtMouseButtonEventType.h"

#include "gtest/gtest.h"

class ZtMouseButtonEventTypeTests : public ::testing::Test
{
protected:

	ZtMouseButtonEventType MouseButtonEventType;

};

TEST_F(ZtMouseButtonEventTypeTests, AssignTest)
{
	MouseButtonEventType = ZtMouseButtonEventType::Pressed;
}