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

	GLFWwindow* RawPointer = Window.GetInternalWindow();
	ASSERT_TRUE(RawPointer);
}

TEST_F(ZtWindowTests, SetViewportTest)
{
	Window.CreateWindow();

	int X = 0;
	int Y = 0;
	int Width = 800;
	int Height = 800;

	Window.SetViewport(X, Y, Width, Height);

	GLint Viewport[4];
	glGetIntegerv(GL_VIEWPORT, Viewport);

	ASSERT_EQ(X, Viewport[0]);
	ASSERT_EQ(Y, Viewport[1]);
	ASSERT_EQ(Width, Viewport[2]);
	ASSERT_EQ(Height, Viewport[3]);
}

TEST_F(ZtWindowTests, SetClearColorTest)
{
	float ExpectedColor[4] = {
		0.2f, 0.3f, 0.3f, 1.0f
	};

	Window.CreateWindow();
	Window.SetClearColor(ExpectedColor[0], ExpectedColor[1], ExpectedColor[2], ExpectedColor[3]);

	float ActualColor[4];
	glGetFloatv(GL_COLOR_CLEAR_VALUE, ActualColor);

	for (int Index = 0; Index < 4; Index++)
	{
		ASSERT_EQ(ExpectedColor[Index], ActualColor[Index]);
	}
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

TEST_F(ZtWindowTests, IsOpenTest)
{
	Window.CreateWindow();

	bool IsOpen = Window.IsOpen();
	ASSERT_TRUE(IsOpen);

	GLFWwindow* WindowPointer = Window.GetInternalWindow();
	glfwSetWindowShouldClose(WindowPointer, true);

	IsOpen = Window.IsOpen();
	ASSERT_FALSE(IsOpen);
}

TEST_F(ZtWindowTests, ClearTest)
{
	Window.CreateWindow();
	Window.Clear();
}

TEST_F(ZtWindowTests, SwapBuffersTest)
{
	Window.CreateWindow();
	Window.SwapBuffers();
}

TEST_F(ZtWindowTests, ShouldBeClosedTest)
{
	Window.CreateWindow();
	GLboolean ShouldBeClosed = Window.ShouldBeClosed();

	ASSERT_FALSE(ShouldBeClosed);
}

TEST_F(ZtWindowTests, GetEvent)
{
	ZtEvent* Event = Window.GetEvent();
}