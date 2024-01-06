#pragma once

#include "Zinet/GraphicLayer/ZtGLSampler.hpp"
#include "Zinet/GraphicLayer/ZtGLDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLSurface.hpp"
#include "Zinet/GraphicLayer/ZtGLInstance.hpp"

#include "Zinet/Window/ZtWindow.hpp"
#include "Zinet/Window/ZtGLFW.hpp"

#include <memory>

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class SamplerTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		wd::Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		Sampler sampler;

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
		}

		void TearDown() override
		{
			wd::GLFW::Deinit();
		}
	};

	TEST(Sampler, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<Sampler, VulkanObject<vk::raii::Sampler>>);
	}

	TEST(Sampler, CreateCreateInfo)
	{
		Sampler sampler;

		std::uint32_t expectedMaxLod = 0u;
		vk::SamplerCreateInfo createInfo = sampler.createCreateInfo(expectedMaxLod);

		ASSERT_EQ(createInfo.magFilter, vk::Filter::eNearest);
		ASSERT_EQ(createInfo.minFilter, vk::Filter::eNearest);
		ASSERT_EQ(createInfo.addressModeU, vk::SamplerAddressMode::eClampToBorder);
		ASSERT_EQ(createInfo.addressModeV, vk::SamplerAddressMode::eClampToBorder);
		ASSERT_EQ(createInfo.addressModeW, vk::SamplerAddressMode::eClampToBorder);
		ASSERT_EQ(createInfo.anisotropyEnable, VK_FALSE);
		ASSERT_EQ(createInfo.borderColor, vk::BorderColor::eIntOpaqueBlack);
		ASSERT_EQ(createInfo.unnormalizedCoordinates, VK_FALSE); 
		ASSERT_EQ(createInfo.compareEnable, VK_FALSE);
		ASSERT_EQ(createInfo.compareOp, vk::CompareOp::eAlways);
		ASSERT_EQ(createInfo.mipmapMode, vk::SamplerMipmapMode::eNearest);
		ASSERT_EQ(createInfo.mipLodBias, 0.0f);
		ASSERT_EQ(createInfo.minLod, 0.0f);
		ASSERT_EQ(createInfo.maxLod, expectedMaxLod);
	}

	TEST_F(SamplerTests, Create)
	{
		vk::SamplerCreateInfo createInfo = sampler.createCreateInfo();
		sampler.create(device, createInfo);

		ASSERT_NE(*sampler.getInternal(), *vk::raii::Sampler{ std::nullptr_t{} });
	}
}