#pragma once

#include "Zinet/GraphicLayer/ZtGLSwapChainSupportDetails.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class SwapChainSupportDetailsTests : public ::testing::Test
	{
	protected:

		SwapChainSupportDetails swapChainSupportDetails;

	};

	TEST_F(SwapChainSupportDetailsTests, PropertiesTest)
	{
		const vk::SurfaceCapabilitiesKHR& surfaceCapabilities = swapChainSupportDetails.surfaceCapabilities;
		const std::vector<vk::SurfaceFormatKHR>& surfaceFormats = swapChainSupportDetails.surfaceFormats;
		const std::vector<vk::PresentModeKHR>& presentModes = swapChainSupportDetails.presentModes;
	}

	TEST_F(SwapChainSupportDetailsTests, PickFormatTest)
	{
		GLFW::InitGLFW();

		Window window;
		window.create();

		Context context;
		Instance instance;
		instance.createInstanceCreateInfo();
		instance.create(context);

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);

		SwapChainSupportDetails swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);

		vk::SurfaceFormatKHR format = swapChainSupportDetails.pickFormat();

		ASSERT_NE(format, vk::SurfaceFormatKHR());

		GLFW::DeinitGLFW();
	}

	TEST_F(SwapChainSupportDetailsTests, PickPresentModeTest)
	{
		GLFW::InitGLFW();

		Window window;
		window.create();

		Context context;
		Instance instance;
		instance.createInstanceCreateInfo();
		instance.create(context);

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);

		SwapChainSupportDetails swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);

		vk::PresentModeKHR presentMode = swapChainSupportDetails.pickPresentMode();

		ASSERT_NE(presentMode, vk::PresentModeKHR());

		GLFW::DeinitGLFW();
	}

	TEST_F(SwapChainSupportDetailsTests, PickSwapExtentTest)
	{
		GLFW::InitGLFW();

		Window window;
		window.create();

		Context context;
		Instance instance;
		instance.createInstanceCreateInfo();
		instance.create(context);

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);

		SwapChainSupportDetails swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);

		vk::Extent2D swapExtent = swapChainSupportDetails.pickSwapExtent(window);
		ASSERT_NE(swapExtent, vk::Extent2D());

		GLFW::DeinitGLFW();
	}
}