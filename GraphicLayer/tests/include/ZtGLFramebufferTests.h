#pragma once

#include "Zinet/GraphicLayer/ZtGLFramebuffer.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class FramebufferTests : public ::testing::Test
	{
	protected:

		std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>();

	};

	TEST_F(FramebufferTests, GetInternalTest)
	{
		vk::raii::Framebuffer& internal = framebuffer->getInternal();
	}

	TEST_F(FramebufferTests, CreateFramebufferCreateInfoTest)
	{
		ImageView imageView;
		RenderPass renderPass;
		vk::Extent2D swapChainExtent;

		vk::FramebufferCreateInfo createInfo = framebuffer->createFramebufferCreateInfo(
			imageView,
			renderPass,
			swapChainExtent);

		ASSERT_NE(createInfo, vk::FramebufferCreateInfo{});
	}

	TEST_F(FramebufferTests, CreateTest)
	{
		GLFW::InitGLFW();

		Context context;
		Instance instance;
		instance.createInstanceCreateInfo();
		instance.create(context);

		Window window;
		window.createWindow();

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);

		SwapChainSupportDetails swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);

		vk::Extent2D swapChainExtent = swapChainSupportDetails.pickSwapExtent(window);
		vk::SurfaceFormatKHR surfaceFormat = swapChainSupportDetails.pickFormat();

		Device device;
		device.create(physicalDevice, surface);

		RenderPass renderPass;
		renderPass.createAttachmentDescription(surfaceFormat.format);
		renderPass.createAttachmentReference();
		renderPass.createSubpassDescription();
		renderPass.createSubpassDependency();
		renderPass.create(device);

		std::unique_ptr<SwapChain> swapChain = std::make_unique<SwapChain>();
		swapChain->create(device, swapChainSupportDetails, surface, window);

		ImageView imageView;
		std::vector<vk::Image> images = swapChain->getImages();
		imageView.create(device, images[0], surfaceFormat.format);

		framebuffer->create(
			device,
			imageView,
			renderPass,
			swapChainExtent);

		ASSERT_NE(*framebuffer->getInternal(), *vk::raii::Framebuffer{ std::nullptr_t{} });

		framebuffer.reset();
		swapChain.reset();

		GLFW::DeinitGLFW();
	}

}
