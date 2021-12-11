#pragma once

#include "Zinet/GraphicLayer/ZtWindow.h"

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
		window.CreateWindow();

		GLFWwindow* InternalWindow = window.GetInternalWindow();
		ASSERT_TRUE(InternalWindow);
	}

	TEST_F(ZtWindowTests, SetViewportTest)
	{
		window.CreateWindow();

		int X = 0;
		int Y = 0;
		int Width = 800;
		int Height = 800;

		window.SetViewport(X, Y, Width, Height);
	}

	TEST_F(ZtWindowTests, SetClearColorTest)
	{
		float Red{};
		float Green{};
		float Blue{};
		float Alpha{};

		window.CreateWindow();
		window.SetClearColor(Red, Green, Blue, Alpha);
	}

	TEST_F(ZtWindowTests, BindFramebufferSizeCallbackTest)
	{
		window.CreateWindow();
		window.BindFramebufferSizeCallback();

		GLFWwindow* WindowPointer = window.GetInternalWindow();
		GLFWframebuffersizefun ActualPointer = glfwSetFramebufferSizeCallback(WindowPointer, nullptr);
		GLFWframebuffersizefun ExpectedPointer = &Window::FramebufferSizeCallback;

		ASSERT_EQ(ActualPointer, ExpectedPointer);
	}

	//TEST_F(ZtWindowTests, IsOpenTest)
	//{
	//	Window.CreateWindow();
	//
	//	bool IsOpen = Window.IsOpen();
	//	ASSERT_TRUE(IsOpen);
	//
	//	GLFWwindow* WindowPointer = Window.GetInternalWindow();
	//	glfwSetWindowShouldClose(WindowPointer, true);
	//
	//	IsOpen = Window.IsOpen();
	//	ASSERT_FALSE(IsOpen);
	//}
	//
	//TEST_F(ZtWindowTests, ClearTest)
	//{
	//	Window.CreateWindow();
	//	Window.Clear();
	//}
	//
	//TEST_F(ZtWindowTests, SwapBuffersTest)
	//{
	//	Window.CreateWindow();
	//	Window.SwapBuffers();
	//}
	//
	//TEST_F(ZtWindowTests, ShouldBeClosedTest)
	//{
	//	Window.CreateWindow();
	//	GLboolean ShouldBeClosed = Window.ShouldBeClosed();
	//
	//	ASSERT_FALSE(ShouldBeClosed);
	//}
	//
	TEST_F(ZtWindowTests, GetEventTest)
	{
		Event* Event = window.GetEvent();
	}
	//
	//TEST_F(ZtWindowTests, BindCallbacksTest)
	//{
	//	Window.CreateWindow();
	//	Window.BindCallbacks();
	//}

}