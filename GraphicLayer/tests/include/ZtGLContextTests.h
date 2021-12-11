#pragma once

#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class GLContextTests : public ::testing::Test
	{
	protected:

		Context GLContext;

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
		Window Window;
		Window.CreateWindow();
		Context::FillMode();
	}

	TEST_F(GLContextTests, PolygonOnlyModeTest)
	{
		GLContext.InitGLFW();
		Window Window;
		Window.CreateWindow();
		Context::PolygonOnlyMode();
	}

	TEST_F(GLContextTests, PointsModeTest)
	{
		GLContext.InitGLFW();
		Window Window;
		Window.CreateWindow();
		Context::PointsMode();
	}

}