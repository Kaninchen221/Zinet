#pragma once

#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class GLContextTests : public ::testing::Test
	{
	protected:

		Context context;

	};

	TEST_F(GLContextTests, InitGLFWTest)
	{
		bool result = context.initGLFW();

		ASSERT_TRUE(result);
	}

	TEST_F(GLContextTests, DeinitGLFWTest)
	{
		context.initGLFW();
		context.deinitGLFW();
	}

	TEST_F(GLContextTests, FillModeTest)
	{
		context.initGLFW();
		Window window;
		window.createWindow();
		Context::FillMode();
	}

	TEST_F(GLContextTests, PolygonOnlyModeTest)
	{
		context.initGLFW();
		Window window;
		window.createWindow();
		Context::PolygonOnlyMode();
	}

	TEST_F(GLContextTests, PointsModeTest)
	{
		context.initGLFW();
		Window window;
		window.createWindow();
		Context::PointsMode();
	}

	TEST_F(GLContextTests, CreateInstanceTest)
	{
		context.initGLFW();
		
	}
}