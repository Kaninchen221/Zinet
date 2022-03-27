#pragma once

#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLSwapChain.h"
#include "Zinet/GraphicLayer/ZtGLSwapChainSupportDetails.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLSemaphore.h"
#include "Zinet/GraphicLayer/ZtGLFence.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class SwapChainTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		SwapChainSupportDetails swapChainSupportDetails;
		SwapChain swapChain;

		void SetUp() override
		{
			GLFW::InitGLFW();

			window.createWindow();
			instance.createApplicationInfo();
			instance.createInstanceCreateInfo();
			instance.create(context);
			surface.create(instance, window);
			physicalDevice.create(instance);
			device.create(physicalDevice, surface);
			swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);
		}

		void TearDown() override
		{
			GLFW::DeinitGLFW();
		}
	};

	TEST(SwapChain, GetInternal)
	{
		SwapChain swapChain;
		vk::raii::SwapchainKHR& internal = swapChain.getInternal();

		ASSERT_EQ(*internal, *vk::raii::SwapchainKHR{ std::nullptr_t{} });
	}

	TEST(SwapChain, CreateSwapChainCreateInfo)
	{
		SwapChain swapChain;

		Surface surface;
		SwapChainSupportDetails swapChainSupportDetails;
		Window window;

		vk::SwapchainCreateInfoKHR creatInfo = swapChain.createSwapChainCreateInfo(swapChainSupportDetails, surface, window);

		ASSERT_NE(creatInfo, vk::SwapchainCreateInfoKHR());
	}

	TEST_F(SwapChainTests, Create)
	{
		swapChain.create(device, swapChainSupportDetails, surface, window);
		const vk::raii::SwapchainKHR& internal = swapChain.getInternal();

		ASSERT_NE(*internal, *vk::raii::SwapchainKHR(std::nullptr_t()));
	}

	TEST_F(SwapChainTests, GetImages)
	{
		swapChain.create(device, swapChainSupportDetails, surface, window);
		std::vector<vk::Image> images = swapChain.getImages();
		std::vector<VkImage> rawImages = swapChain.getInternal().getImages();

		ASSERT_EQ(images.size(), rawImages.size());
		for (const vk::Image& image : images)
		{
			ASSERT_TRUE(image);
		}

		images.clear();
	}

	TEST_F(SwapChainTests, AcquireNextImage)
	{
		device.create(physicalDevice, surface);
		swapChain.create(device, swapChainSupportDetails, surface, window);
		
		uint64_t timeout = 1;

		Semaphore semaphore;
		semaphore.create(device);

		Fence fence;
		fence.create(device);
		device.resetFence(fence);

		std::pair<vk::Result, uint32_t> nextImage = swapChain.acquireNextImage(timeout, semaphore, fence);

		device.waitForFence(fence, 1000u);
	}
}