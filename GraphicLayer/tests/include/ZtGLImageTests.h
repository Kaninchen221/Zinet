#pragma once

#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLSwapChain.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class ImageTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		Image image;

		void SetUp() override
		{
			GLFW::Init();

			window.create();
			vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
			instance.getRequiredExtensions();
			vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
			instance.create(context, instanceCreateInfo);
			surface.create(instance, window);
			physicalDevice.create(instance);

			vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
			vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice, surface, deviceQueueCreateInfo);
			device.create(physicalDevice, deviceCreateInfo);
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST(Image, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<Image, VulkanObject<vk::raii::Image>>);
	}

	TEST(Image, CreateCreateInfo)
	{
		Image image;
		std::uint32_t expectedWidth = 0u;
		std::uint32_t expectedHeight = 0u;
		vk::ImageCreateInfo createInfo = image.createCreateInfo(expectedWidth, expectedHeight);

		ASSERT_EQ(createInfo.imageType, vk::ImageType::e2D);
		ASSERT_EQ(createInfo.extent.width, expectedWidth);
		ASSERT_EQ(createInfo.extent.height, expectedHeight);
		ASSERT_EQ(createInfo.extent.depth, 1);
		ASSERT_EQ(createInfo.mipLevels, 1);
		ASSERT_EQ(createInfo.arrayLayers, 1);
		ASSERT_EQ(createInfo.format, vk::Format::eR8G8B8A8Srgb);
		ASSERT_EQ(createInfo.tiling, vk::ImageTiling::eOptimal);
		ASSERT_EQ(createInfo.initialLayout, vk::ImageLayout::eUndefined);
		ASSERT_EQ(createInfo.usage, vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled);
		ASSERT_EQ(createInfo.sharingMode, vk::SharingMode::eExclusive);
		ASSERT_EQ(createInfo.samples, vk::SampleCountFlagBits::e1);
	}

	TEST_F(ImageTests, Create)
	{
		std::uint32_t expectedWidth = 1u;
		std::uint32_t expectedHeight = 1u;
		vk::ImageCreateInfo createInfo = image.createCreateInfo(expectedWidth, expectedHeight);
		
		image.create(device, createInfo);

		ASSERT_NE(*image.getInternal(), *vk::raii::Image{ std::nullptr_t{} });
	}

}
