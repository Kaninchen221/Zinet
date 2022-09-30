#pragma once

#include "Zinet/GraphicLayer/ZtGLStagingBuffer.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"
#include "Zinet/GraphicLayer/ZtGLBuffer.h"
#include "Zinet/GraphicLayer/ZtGLImageBuffer.h"
#include "Zinet/GraphicLayer/ZtGLSampler.h"
#include "Zinet/GraphicLayer/ZtGLImageView.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ImageBufferTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		ImageBuffer imageBuffer;

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

			vk::BufferCreateInfo createInfo = imageBuffer.createCreateInfo(8u);
			imageBuffer.create(device, createInfo);
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST(ImageBuffer, DerivedFromBuffer)
	{
		static_assert(std::derived_from<ImageBuffer, Buffer>);
	}

	TEST_F(ImageBufferTests, CreateDescriptorImageInfo)
	{
		Sampler sampler;
		ImageView imageView;
		vk::ImageLayout imageLayout{};
		vk::DescriptorImageInfo info = imageBuffer.createDescriptorImageInfo(sampler, imageView, imageLayout);

		ASSERT_EQ(info.sampler, *sampler.getInternal());
		ASSERT_EQ(info.imageView, *imageView.getInternal());
		ASSERT_EQ(info.imageLayout, imageLayout);
	}
}