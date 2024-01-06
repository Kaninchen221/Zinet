#pragma once

#include "Zinet/GraphicLayer/ZtGLDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLSwapChain.hpp"
#include "Zinet/GraphicLayer/ZtGLSwapChainSupportDetails.hpp"
#include "Zinet/GraphicLayer/ZtGLSurface.hpp"
#include "Zinet/GraphicLayer/ZtGLSemaphore.hpp"
#include "Zinet/GraphicLayer/ZtGLFence.hpp"
#include "Zinet/GraphicLayer/ZtGLInstance.hpp"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.hpp"

#include "Zinet/Window/ZtGLFW.hpp"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class SwapChainTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		wd::Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		SwapChainSupportDetails swapChainSupportDetails;
		SwapChain swapChain;

		void SetUp() override
		{
			wd::GLFW::Init();

			window.create();
			vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
			instance.populateRequiredExtensions();
			vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
			instance.create(context, instanceCreateInfo);
			surface.create(instance, window);
			physicalDevice.create(instance);

			vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
			vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(instance, physicalDevice, surface, deviceQueueCreateInfo);
			device.create(physicalDevice, deviceCreateInfo);

			swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);
		}

		void TearDown() override
		{
			wd::GLFW::Deinit();
		}
	};

	TEST(SwapChain, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<SwapChain, VulkanObject<vk::raii::SwapchainKHR>>);
	}

	TEST(SwapChain, CreateSwapChainCreateInfo)
	{
		SwapChain swapChain;

		Surface surface;
		SwapChainSupportDetails swapChainSupportDetails;
		wd::Window window;

		vk::SwapchainCreateInfoKHR creatInfo = swapChain.createCreateInfo(swapChainSupportDetails, surface, window);

		ASSERT_NE(creatInfo, vk::SwapchainCreateInfoKHR());
	}

	TEST_F(SwapChainTests, Create)
	{
		vk::SwapchainCreateInfoKHR creatInfo = swapChain.createCreateInfo(swapChainSupportDetails, surface, window);
		swapChain.create(device, creatInfo);
		const vk::raii::SwapchainKHR& internal = swapChain.getInternal();

		ASSERT_NE(*internal, *vk::raii::SwapchainKHR(std::nullptr_t()));
	}

	TEST_F(SwapChainTests, GetImages)
	{
		vk::SwapchainCreateInfoKHR creatInfo = swapChain.createCreateInfo(swapChainSupportDetails, surface, window);
		swapChain.create(device, creatInfo);
		std::vector<vk::Image> images = swapChain.getImages();
		std::vector<vk::Image> rawImages = swapChain.getInternal().getImages();

		ASSERT_EQ(images.size(), rawImages.size());
		for (const vk::Image& image : images)
		{
			ASSERT_TRUE(image);
		}

		images.clear();
	}

	TEST_F(SwapChainTests, AcquireNextImage)
	{
// 		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
// 		vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(instance, physicalDevice, surface, deviceQueueCreateInfo);
// 		device.create(physicalDevice, deviceCreateInfo);

		vk::SwapchainCreateInfoKHR creatInfo = swapChain.createCreateInfo(swapChainSupportDetails, surface, window);
		swapChain.create(device, creatInfo);
		
		uint64_t timeout = 1;

		Semaphore semaphore;
		semaphore.create(device);

		Fence fence;
		vk::FenceCreateInfo fenceCreateInfo = fence.createSignaledFenceCreateInfo();
		fence.create(device, fenceCreateInfo);
		device.resetFence(fence);

		std::pair<vk::Result, uint32_t> nextImage = swapChain.acquireNextImage(timeout, semaphore, fence);

		device.waitForFence(fence, 1000u);
	}
}