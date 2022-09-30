#pragma once

#include "Zinet/GraphicLayer/ZtGLSampler.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"

#include <memory>

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class SamplerTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		Sampler sampler;

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

	TEST(Sampler, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<Sampler, VulkanObject<vk::raii::Sampler>>);
	}

	TEST(Sampler, CreateCreateInfo)
	{
		Sampler sampler;
		vk::SamplerCreateInfo createInfo = sampler.createCreateInfo();

		ASSERT_EQ(createInfo.magFilter, vk::Filter::eLinear);
		ASSERT_EQ(createInfo.minFilter, vk::Filter::eLinear);
		ASSERT_EQ(createInfo.addressModeU, vk::SamplerAddressMode::eRepeat);
		ASSERT_EQ(createInfo.addressModeV, vk::SamplerAddressMode::eRepeat);
		ASSERT_EQ(createInfo.addressModeW, vk::SamplerAddressMode::eRepeat);
		ASSERT_EQ(createInfo.anisotropyEnable, VK_FALSE);
		ASSERT_EQ(createInfo.borderColor, vk::BorderColor::eIntOpaqueBlack);
		ASSERT_EQ(createInfo.unnormalizedCoordinates, VK_FALSE); 
		ASSERT_EQ(createInfo.compareEnable, VK_FALSE);
		ASSERT_EQ(createInfo.compareOp, vk::CompareOp::eAlways);
		ASSERT_EQ(createInfo.mipmapMode, vk::SamplerMipmapMode::eLinear);
		ASSERT_EQ(createInfo.mipLodBias, 0.0f);
		ASSERT_EQ(createInfo.minLod, 0.0f);
		ASSERT_EQ(createInfo.maxLod, 0.0f);
	}

	TEST_F(SamplerTests, Create)
	{
		vk::SamplerCreateInfo createInfo = sampler.createCreateInfo();
		sampler.create(device, createInfo);

		ASSERT_NE(*sampler.getInternal(), *vk::raii::Sampler{ std::nullptr_t{} });
	}
}