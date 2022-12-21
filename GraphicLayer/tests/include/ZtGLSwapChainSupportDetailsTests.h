#pragma once

#include "Zinet/GraphicLayer/ZtGLSwapChainSupportDetails.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class SwapChainSupportDetailsTests : public ::testing::Test
	{
	protected:

		SwapChainSupportDetails swapChainSupportDetails;

	};

	TEST_F(SwapChainSupportDetailsTests, PropertiesTest)
	{
		[[maybe_unused]] const vk::SurfaceCapabilitiesKHR& surfaceCapabilities = swapChainSupportDetails.surfaceCapabilities;
		[[maybe_unused]] const std::vector<vk::SurfaceFormatKHR>& surfaceFormats = swapChainSupportDetails.surfaceFormats;
		[[maybe_unused]] const std::vector<vk::PresentModeKHR>& presentModes = swapChainSupportDetails.presentModes;
	}

	TEST_F(SwapChainSupportDetailsTests, PickFormatTest)
	{
		GLFW::Init();

		Window window;
		window.create();

		Context context;
		Instance instance;
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		instance.populateRequiredExtensions();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);

		swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);

		vk::SurfaceFormatKHR format = swapChainSupportDetails.pickFormat();

		ASSERT_NE(format, vk::SurfaceFormatKHR());

		GLFW::Deinit();
	}

	TEST_F(SwapChainSupportDetailsTests, PickPresentModeTest)
	{
		GLFW::Init();

		Window window;
		window.create();

		Context context;
		Instance instance;
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		instance.populateRequiredExtensions();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);

		swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);

		vk::PresentModeKHR presentMode = swapChainSupportDetails.pickPresentMode();

		ASSERT_NE(presentMode, vk::PresentModeKHR());

		GLFW::Deinit();
	}

	TEST_F(SwapChainSupportDetailsTests, PickSwapExtentTest)
	{
		GLFW::Init();

		Window window;
		window.create();

		Context context;
		Instance instance;
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		instance.populateRequiredExtensions();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);

		swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);

		vk::Extent2D swapExtent = swapChainSupportDetails.pickSwapExtent(window);
		ASSERT_NE(swapExtent, vk::Extent2D());

		GLFW::Deinit();
	}
}