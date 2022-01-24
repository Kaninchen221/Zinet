#pragma once

#include "Zinet/GraphicLayer/ZtGLWindow.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtWindowTests : public ::testing::Test
	{
	protected:

		Window window{};

	};

	TEST_F(ZtWindowTests, CreateWindowTest)
	{
		window.createWindow();

		GLFWwindow* internalWindow = window.getInternalWindow();
		ASSERT_TRUE(internalWindow);
	}

	TEST_F(ZtWindowTests, SetViewportTest)
	{
		window.createWindow();

		int x = 0;
		int y = 0;
		int width = 800;
		int height = 800;

		window.setViewport(x, y, width, height);
	}

	TEST_F(ZtWindowTests, SetClearColorTest)
	{
		float red{};
		float green{};
		float blue{};
		float alpha{};

		window.createWindow();
		window.setClearColor(red, green, blue, alpha);
	}

	TEST_F(ZtWindowTests, BindFramebufferSizeCallbackTest)
	{
		window.createWindow();
		window.bindFramebufferSizeCallback();

		GLFWwindow* glfwWindow = window.getInternalWindow();
		GLFWframebuffersizefun actualPointer = glfwSetFramebufferSizeCallback(glfwWindow, nullptr);
		GLFWframebuffersizefun expectedPointer = &Window::FramebufferSizeCallback;

		ASSERT_EQ(actualPointer, expectedPointer);
	}

	TEST_F(ZtWindowTests, IsOpenTest)
	{
		window.createWindow();
	
		bool isOpen = window.isOpen();
		ASSERT_TRUE(isOpen);
	
		GLFWwindow* glfwWindow = window.getInternalWindow();
		glfwSetWindowShouldClose(glfwWindow, true);
	
		isOpen = window.isOpen();
		ASSERT_FALSE(isOpen);
	}
	
	TEST_F(ZtWindowTests, ClearTest)
	{
		window.createWindow();
		window.clear();
	}
	
	TEST_F(ZtWindowTests, SwapBuffersTest)
	{
		window.createWindow();
		window.swapBuffers();
	}
	
	TEST_F(ZtWindowTests, ShouldBeClosedTest)
	{
		window.createWindow();
		GLboolean shouldBeClosed = window.shouldBeClosed();
	
		ASSERT_FALSE(shouldBeClosed);
	}
	
	TEST_F(ZtWindowTests, GetEventTest)
	{
		Event* event = window.getEvent();
	}
	
	TEST_F(ZtWindowTests, BindCallbacksTest)
	{
		window.createWindow();
		window.bindCallbacks();
	}

}