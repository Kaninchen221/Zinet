#pragma once

#include "Zinet/GraphicLayer/ZtMouseButton.h"

#include "gtest/gtest.h"

class ZtMouseButtonTests : public ::testing::Test
{
protected:

	ZtMouseButton Button;

};

TEST_F(ZtMouseButtonTests, AssignTest)
{
	Button = ZtMouseButton::RIGHT;
}