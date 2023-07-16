#pragma once

#include "Zinet/GraphicLayer/ZtGLFramebuffer.h"
#include "Zinet/GraphicLayer/ZtGLImageView.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLSwapChain.h"
#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLRenderPass.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class FramebufferTests : public ::testing::Test
	{
	protected:

		std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>();

	};

	TEST(Framebuffer, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<Framebuffer, VulkanObject<vk::raii::Framebuffer>>);
	}

	TEST_F(FramebufferTests, CreateCreateInfoTest)
	{
		ImageView imageView;
		RenderPass renderPass;
		vk::Extent2D swapChainExtent;

		vk::FramebufferCreateInfo createInfo = framebuffer->createCreateInfo(
			imageView,
			renderPass,
			swapChainExtent);

		ASSERT_NE(createInfo, vk::FramebufferCreateInfo{});
	}

	TEST_F(FramebufferTests, CreateTest)
	{
		GLFW::Init();

		Context context;
		Instance instance;
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		instance.populateRequiredExtensions();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);

		Window window;
		window.create();

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);

		SwapChainSupportDetails swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);

		vk::Extent2D swapChainExtent = swapChainSupportDetails.pickSwapExtent(window);
		vk::SurfaceFormatKHR surfaceFormat = swapChainSupportDetails.pickFormat();

		Device device;
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
		vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice, surface, deviceQueueCreateInfo);
		device.create(physicalDevice, deviceCreateInfo);

		RenderPass renderPass;
		renderPass.createColorAttachmentDescription(surfaceFormat.format);
		renderPass.createColorAttachmentReference();
		renderPass.createSubpassDescription();
		renderPass.createSubpassDependency();

		vk::RenderPassCreateInfo createInfo = renderPass.createRenderPassCreateInfo();
		renderPass.create(device, createInfo);

		std::unique_ptr<SwapChain> swapChain = std::make_unique<SwapChain>();
		vk::SwapchainCreateInfoKHR creatInfo = swapChain->createCreateInfo(swapChainSupportDetails, surface, window);
		swapChain->create(device, creatInfo);

		ImageView imageView;
		std::vector<vk::Image> images = swapChain->getImages();
		std::uint32_t mipmapLevels = 1u;
		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(images[0], mipmapLevels, surfaceFormat.format);
		imageView.create(device, imageViewCreateInfo);

		vk::FramebufferCreateInfo framebufferCreateInfo = framebuffer->createCreateInfo(imageView, renderPass, swapChainExtent);
		framebuffer->create(device, framebufferCreateInfo);

		ASSERT_NE(*framebuffer->getInternal(), *vk::raii::Framebuffer{ std::nullptr_t{} });

		framebuffer.reset();
		swapChain.reset();

		GLFW::Deinit();
	}

}
