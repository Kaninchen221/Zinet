#pragma once

#include "Zinet/GraphicLayer/ZtGLSurface.hpp"
#include "Zinet/GraphicLayer/ZtGLInstance.hpp"

#include "Zinet/Window/ZtGLFW.hpp"
#include "Zinet/Window/ZtWindow.hpp"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class SurfaceTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		wd::Window window;
		Surface surface;

		void SetUp() override
		{
			wd::GLFW::Init();

			window.create();
			vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
			instance.populateRequiredExtensions();
			vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
			instance.create(context, instanceCreateInfo);
		}

		void TearDown() override
		{
			wd::GLFW::Deinit();
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