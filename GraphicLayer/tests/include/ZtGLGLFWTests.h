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
		bool result = GLFW::Init();

		ASSERT_TRUE(result);

		GLFW::Deinit();
	}

	TEST_F(GLFWTests, DeinitGLFWTest)
	{
		GLFW::Init();
		GLFW::Deinit();
	}

}
