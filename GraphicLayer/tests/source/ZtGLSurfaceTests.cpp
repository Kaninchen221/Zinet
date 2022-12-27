#pragma once

#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class SurfaceTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;

		void SetUp() override
		{
			GLFW::Init();

			window.create();
			vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
			instance.populateRequiredExtensions();
			vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
			instance.create(context, instanceCreateInfo);
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}

	};

	TEST(Surface, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<Surface, VulkanObject<vk::raii::SurfaceKHR>>);
	}

	TEST_F(SurfaceTests, Create)
	{
		bool result = surface.create(instance, window);

		ASSERT_TRUE(result);

		vk::raii::SurfaceKHR& internalSurface = surface.getInternal();

		ASSERT_NE(*internalSurface, *vk::raii::SurfaceKHR{ std::nullptr_t{} });
	}

}