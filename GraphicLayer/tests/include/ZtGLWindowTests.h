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
			GLFW::InitGLFW();
		}

		void TearDown() override
		{
			GLFW::DeinitGLFW();
		}
	};

	TEST_F(ZtWindowTests, Create)
	{
		window.create();

		GLFWwindow* internalWindow = window.getInternal();
		ASSERT_TRUE(internalWindow);
	}

	TEST_F(ZtWindowTests, SetViewportTest)
	{
		window.create();

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

		window.create();
		window.setClearColor(red, green, blue, alpha);
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
	
	TEST_F(ZtWindowTests, ClearTest)
	{
		window.create();
		window.clear();
	}
	
	TEST_F(ZtWindowTests, SwapBuffersTest)
	{
		window.create();
		window.swapBuffers();
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