#pragma once

#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

class ZtWindowTests : public ::testing::Test
{
protected:

	ZtWindow Window{};

};

TEST_F(ZtWindowTests, InitGLFWTest)
{
	Window.InitGLFW();
}

TEST_F(ZtWindowTests, CreateWindowTest)
{
	Window.InitGLFW();
	Window.CreateWindow();

	GLFWwindow* RawPointer = Window.GetInternalWindow();
	ASSERT_TRUE(RawPointer);
}

TEST_F(ZtWindowTests, InitGLADTest)
{
	bool IsGladLoaded = gladLoadGL();
	ASSERT_FALSE(IsGladLoaded);

	Window.InitGLFW();
	Window.CreateWindow();
	Window.InitGLAD();

	IsGladLoaded = gladLoadGL();
	ASSERT_TRUE(IsGladLoaded);
}

TEST_F(ZtWindowTests, InitOpenGL)
{
	Window.InitGLFW();
	Window.CreateWindow();
	Window.InitGLAD();
	Window.InitOpenGL();
}

TEST_F(ZtWindowTests, SetViewportTest)
{
	Window.InitGLFW();
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

	Window.InitGLFW();
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
	Window.InitGLFW();
	Window.CreateWindow();
	Window.BindFramebufferSizeCallback();

	GLFWwindow* WindowPointer = Window.GetInternalWindow();
	GLFWframebuffersizefun ActualPointer = glfwSetFramebufferSizeCallback(WindowPointer, nullptr);
	GLFWframebuffersizefun ExpectedPointer = &ZtWindow::FramebufferSizeCallback;

	ASSERT_EQ(ActualPointer, ExpectedPointer);
}

TEST_F(ZtWindowTests, IsOpenTest)
{
	Window.InitGLFW();
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
	Window.InitGLFW();
	Window.CreateWindow();
	Window.Clear();
}

TEST_F(ZtWindowTests, SwapBuffersTest)
{
	Window.InitGLFW();
	Window.CreateWindow();
	Window.SwapBuffers();
}

TEST_F(ZtWindowTests, PolygonOnlyModeTest)
{
	Window.InitGLFW();
	Window.CreateWindow();
	Window.PolygonOnlyMode();
}

TEST_F(ZtWindowTests, FillModeTest)
{
	Window.InitGLFW();
	Window.CreateWindow();
	Window.FillMode();
}

TEST_F(ZtWindowTests, PointsModeTest)
{
	Window.InitGLFW();
	Window.CreateWindow();
	Window.PointsMode();
}

TEST_F(ZtWindowTests, ShouldBeClosedTest)
{
	Window.InitGLFW();
	Window.CreateWindow();
	GLboolean ShouldBeClosed = Window.ShouldBeClosed();

	ASSERT_FALSE(ShouldBeClosed);
}