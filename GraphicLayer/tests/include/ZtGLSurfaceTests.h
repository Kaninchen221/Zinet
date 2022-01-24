#pragma once

#include "Zinet/GraphicLayer/ZtGLSurface.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class SurfaceTests : public ::testing::Test
	{
	protected:

		Surface surface;

	};

	TEST_F(SurfaceTests, CreateTest)
	{
		GLFW::InitGLFW();

		Context context;
		Instance instance;
		instance.createInstanceCreateInfo();
		instance.createInstance(context);

		Window window;
		window.createWindow();

		bool result = surface.create(instance, window);

		ASSERT_TRUE(result);

		VkSurfaceKHR internalSurface = surface.getInternal();

		ASSERT_NE(internalSurface, VkSurfaceKHR());

		surface.destroySurface(instance);

		GLFW::DeinitGLFW();
	}

	TEST_F(SurfaceTests, GetSurfaceTest)
	{
		VkSurfaceKHR internalSurface = surface.getInternal();

		ASSERT_EQ(internalSurface, VkSurfaceKHR());
	}

}