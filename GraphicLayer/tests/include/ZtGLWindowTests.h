#pragma once

#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtWindowTests : public ::testing::Test
	{
	protected:

		Window window{};

		void SetUp() override
		{
			GLFW::Init();
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST_F(ZtWindowTests, Create)
	{
		window.create();

		GLFWwindow* internalWindow = window.getInternal();
		ASSERT_TRUE(internalWindow);
	}

	TEST_F(ZtWindowTests, BindFramebufferSizeCallbackTest)
	{
		window.create();
		window.bindFramebufferSizeCallback();

		GLFWwindow* glfwWindow = window.getInternal();
		GLFWframebuffersizefun actualPointer = glfwSetFramebufferSizeCallback(glfwWindow, nullptr);
		GLFWframebuffersizefun expectedPointer = &Window::FramebufferSizeCallback;

		ASSERT_EQ(actualPointer, expectedPointer);
	}

	TEST_F(ZtWindowTests, IsOpenTest)
	{
		window.create();
	
		bool isOpen = window.isOpen();
		ASSERT_TRUE(isOpen);
	
		GLFWwindow* glfwWindow = window.getInternal();
		glfwSetWindowShouldClose(glfwWindow, true);
	
		isOpen = window.isOpen();
		ASSERT_FALSE(isOpen);
	}
	
	TEST_F(ZtWindowTests, ShouldBeClosedTest)
	{
		window.create();
		GLboolean shouldBeClosed = window.shouldBeClosed();
	
		ASSERT_FALSE(shouldBeClosed);
	}
	
	TEST_F(ZtWindowTests, GetEventTest)
	{
		Event* event = window.getEvent();
	}
	
	TEST_F(ZtWindowTests, BindCallbacksTest)
	{
		window.create();
		window.bindCallbacks();
	}

}