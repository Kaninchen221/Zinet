#pragma once

#include "Zinet/GraphicLayer/ZtMouse.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

class ZtMousePositionEventTests : public ::testing::Test
{
protected:

	ZtMousePositionEvent PositionEvent;

};

TEST_F(ZtMousePositionEventTests, PositionTest)
{
	PositionEvent.Position = glm::dvec2();
}