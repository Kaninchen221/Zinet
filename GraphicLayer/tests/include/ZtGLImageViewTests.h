#pragma once

#include "Zinet/GraphicLayer/ZtGLImageView.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLSwapChain.h"

#include <memory>

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ImageViewTests : public ::testing::Test
	{
	protected:

		std::unique_ptr<ImageView> imageView;

		ImageViewTests()
			: imageView(std::make_unique<ImageView>())
		{}

	};

	TEST(ImageView, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<ImageView, VulkanObject<vk::raii::ImageView>>);
	}

	TEST_F(ImageViewTests, CreateImageViewCreateInfoTest)
	{
		vk::Image image;
		vk::Format format;
		vk::ImageViewCreateInfo imageViewCreateInfo = imageView->createImageViewCreateInfo(image, format);

		ASSERT_NE(imageViewCreateInfo, vk::ImageViewCreateInfo());
	}

	TEST_F(ImageViewTests, CreateImageTest)
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

		Device device;
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
		vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice, surface, deviceQueueCreateInfo);
		device.create(physicalDevice, deviceCreateInfo);

		std::unique_ptr<SwapChain> swapChain = std::make_unique<SwapChain>();
		swapChain->create(device, swapChainSupportDetails, surface, window);

		std::vector<vk::Image> images = swapChain->getImages();
		vk::SurfaceFormatKHR surfaceFormat = swapChainSupportDetails.pickFormat();
		imageView->create(device, images[0], surfaceFormat.format);
		
		ASSERT_NE(*imageView->getInternal(), *vk::raii::ImageView(std::nullptr_t{}));
		
		imageView.reset();
		swapChain.reset();
		
		GLFW::DeinitGLFW();
	}
}