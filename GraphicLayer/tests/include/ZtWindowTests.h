#pragma once

#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

class ZtWindowTests : public ::testing::Test
{
protected:

	ZtWindow Window{};

};

TEST_F(ZtWindowTests, CreateWindowTest)
{
	Window.CreateWindow();

	GLFWwindow* InternalWindow = Window.GetInternalWindow();
	ASSERT_TRUE(InternalWindow);
}

TEST_F(ZtWindowTests, SetViewportTest)
{
	Window.CreateWindow();

	int X = 0;
	int Y = 0;
	int Width = 800;
	int Height = 800;

	Window.SetViewport(X, Y, Width, Height);
}

TEST_F(ZtWindowTests, SetClearColorTest)
{
	float Red{};
	float Green{};
	float Blue{};
	float Alpha{};

	Window.CreateWindow();
	Window.SetClearColor(Red, Green, Blue, Alpha);
}

TEST_F(ZtWindowTests, BindFramebufferSizeCallbackTest)
{
	Window.CreateWindow();
	Window.BindFramebufferSizeCallback();

	GLFWwindow* WindowPointer = Window.GetInternalWindow();
	GLFWframebuffersizefun ActualPointer = glfwSetFramebufferSizeCallback(WindowPointer, nullptr);
	GLFWframebuffersizefun ExpectedPointer = &ZtWindow::FramebufferSizeCallback;

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
	ZtEvent* Event = Window.GetEvent();
}
//
//TEST_F(ZtWindowTests, BindCallbacksTest)
//{
//	Window.CreateWindow();
//	Window.BindCallbacks();
//}