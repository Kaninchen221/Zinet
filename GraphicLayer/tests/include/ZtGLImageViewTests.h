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

		// Must be destroyed before device and SwapChain
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
		vk::ImageViewCreateInfo imageViewCreateInfo = imageView->createCreateInfo(image, format);

		ASSERT_NE(imageViewCreateInfo, vk::ImageViewCreateInfo());
	}

	TEST_F(ImageViewTests, CreateImageTest)
	{
		GLFW::Init();

		Window window;
		window.create();

		Context context;
		Instance instance;
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		instance.getRequiredExtensions();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);

		SwapChainSupportDetails swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);

		Device device;
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
		vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice, surface, deviceQueueCreateInfo);
		device.create(physicalDevice, deviceCreateInfo);

		SwapChain swapChain;
		swapChain.create(device, swapChainSupportDetails, surface, window);

		std::vector<vk::Image> images = swapChain.getImages();
		vk::SurfaceFormatKHR surfaceFormat = swapChainSupportDetails.pickFormat();
		vk::ImageViewCreateInfo imageViewCreateInfo = imageView->createCreateInfo(images[0], surfaceFormat.format);
		imageView->create(device, imageViewCreateInfo);
		
		ASSERT_NE(*imageView->getInternal(), *vk::raii::ImageView(std::nullptr_t{}));
		
		imageView.reset();
		
		GLFW::Deinit();
	}
}