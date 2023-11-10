#pragma once

#include "Zinet/Window/ZtGLFW.h"

#include <gtest/gtest.h>

namespace zt::wd
{

	class GLFWTests : public ::testing::Test
	{
	protected:

		GLFW glfw;

	};

	TEST_F(GLFWTests, IsInitialized)
	{
		bool isInitialized = glfw.isInitialized();
		ASSERT_FALSE(isInitialized);

		GLFW glfw2;
		glfw2.Init();
		isInitialized = glfw2.isInitialized();
		ASSERT_TRUE(isInitialized);

		isInitialized = glfw.isInitialized();
		ASSERT_TRUE(isInitialized);
	}

	TEST_F(GLFWTests, InitGLFWTest)
	{
		const bool result = GLFW::Init();

		ASSERT_TRUE(result);

		GLFW::Deinit();
	}

	TEST_F(GLFWTests, DeinitGLFWTest)
	{
		GLFW::Init();
		GLFW::Deinit();
	}

}
