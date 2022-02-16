#pragma once

#include "Zinet/GraphicLayer/ZtMouse.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtMousePositionEventTests : public ::testing::Test
	{
	protected:

		MousePositionEvent positionEvent;

	};

	TEST_F(ZtMousePositionEventTests, PositionTest)
	{
		positionEvent.position = glm::dvec2();
	}

}