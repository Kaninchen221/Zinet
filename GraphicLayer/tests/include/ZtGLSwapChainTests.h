#pragma once

#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLSwapChain.h"
#include "Zinet/GraphicLayer/ZtGLSwapChainSupportDetails.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class SwapChainTests : public ::testing::Test
	{
	protected:

		std::unique_ptr<SwapChain> swapChain;

		SwapChainTests()
		{
			swapChain = std::make_unique<SwapChain>();
		}
	};

	TEST_F(SwapChainTests, GetInternalTest)
	{
		const vk::raii::SwapchainKHR& internal = swapChain->getInternal();
	}

	TEST_F(SwapChainTests, CreateTest)
	{
		GLFW::InitGLFW();

		Window window;
		window.createWindow();

		Context context;
		Instance instance;
		instance.createInstanceCreateInfo();
		instance.create(context);

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);

		SwapChainSupportDetails swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);

		Device device;
		device.create(physicalDevice, surface);

		swapChain->create(device, swapChainSupportDetails, surface, window);
		const vk::raii::SwapchainKHR& internal = swapChain->getInternal();

		ASSERT_NE(*internal, *vk::raii::SwapchainKHR(std::nullptr_t()));

		swapChain.reset();
		surface.destroy(instance);

		GLFW::DeinitGLFW();
	}

	TEST_F(SwapChainTests, CreateSwapChainCreateInfoTest)
	{
		Surface surface;
		SwapChainSupportDetails swapChainSupportDetails;
		Window window;

		vk::SwapchainCreateInfoKHR creatInfo = swapChain->createSwapChainCreateInfo(swapChainSupportDetails, surface, window);

		ASSERT_NE(creatInfo, vk::SwapchainCreateInfoKHR());
	}
}