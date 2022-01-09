#pragma once

#include "Zinet/GraphicLayer/ZtGLGLFW.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class GLFWTests : public ::testing::Test
	{
	protected:

		GLFW glfw;

	};

	TEST_F(GLFWTests, InitGLFWTest)
	{
		bool result = glfw.initGLFW();

		ASSERT_TRUE(result);
	}

	TEST_F(GLFWTests, DeinitGLFWTest)
	{
		glfw.initGLFW();
		glfw.deinitGLFW();
	}

}