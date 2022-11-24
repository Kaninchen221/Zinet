#pragma once

#include "Zinet/GraphicLayer/ZtGLMouse.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class MousePositionEventTests : public ::testing::Test
	{
	protected:

		MousePositionEvent positionEvent;

	};

	TEST_F(MousePositionEventTests, Position)
	{
		positionEvent.position = glm::dvec2();
	}

}