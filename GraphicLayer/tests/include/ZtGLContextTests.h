#pragma once

#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

class GLContextTests : public ::testing::Test
{
protected:

	ZtGLContext GLContext;

};

TEST_F(GLContextTests, InitGLFWTest)
{
	bool Result = GLContext.InitGLFW();

	ASSERT_TRUE(Result);
}

TEST_F(GLContextTests, DeinitGLFWTest)
{
	GLContext.InitGLFW();
	GLContext.DeinitGLFW();
}

TEST_F(GLContextTests, FillModeTest)
{
	GLContext.InitGLFW();
	ZtWindow Window;
	Window.CreateWindow();
	ZtGLContext::FillMode();
}

TEST_F(GLContextTests, PolygonOnlyModeTest)
{
	GLContext.InitGLFW();
	ZtWindow Window;
	Window.CreateWindow();
	ZtGLContext::PolygonOnlyMode();
}

TEST_F(GLContextTests, PointsModeTest)
{
	GLContext.InitGLFW();
	ZtWindow Window;
	Window.CreateWindow();
	ZtGLContext::PointsMode();
}