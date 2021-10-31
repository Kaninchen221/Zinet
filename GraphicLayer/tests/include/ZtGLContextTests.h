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

TEST_F(GLContextTests, InitGLADTest)
{
	GLContext.InitGLFW();
	ZtWindow Window;
	Window.CreateWindow();
	bool Result = GLContext.InitGLAD();

	ASSERT_TRUE(Result);
}

TEST_F(GLContextTests, InitOpenGLTest)
{
	GLContext.InitGLFW();
	ZtWindow Window;
	Window.CreateWindow();
	GLContext.InitGLAD();
	bool Result = GLContext.InitOpenGL();

	ASSERT_TRUE(Result);
}

TEST_F(GLContextTests, FillModeTest)
{
	ZtGLContext::FillMode();
}

TEST_F(GLContextTests, PolygonOnlyModeTest)
{
	ZtGLContext::PolygonOnlyMode();
}

TEST_F(GLContextTests, PointsModeTest)
{
	ZtGLContext::PointsMode();
}