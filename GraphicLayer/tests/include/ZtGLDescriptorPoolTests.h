#pragma once

#include "Zinet/GraphicLayer/ZtGLDescriptorPool.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorSetLayout.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class DescriptorPoolTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		DescriptorPool descriptorPool;

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

			vk::DescriptorPoolSize uniformPoolSize = descriptorPool.createUniformPoolSize();
			vk::DescriptorPoolSize imageSamplerPoolSize = descriptorPool.createImageSamplerPoolSize();

			std::vector<vk::DescriptorPoolSize> poolSizes = { uniformPoolSize, imageSamplerPoolSize };
			vk::DescriptorPoolCreateInfo createInfo = descriptorPool.createCreateInfo(poolSizes);
			descriptorPool.create(device, createInfo);
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST(DescriptorPool, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<DescriptorPool, VulkanObject<vk::raii::DescriptorPool>>);
	}

	TEST(DescriptorPool, CreateUniformPoolSize)
	{
		DescriptorPool descriptorPool;
		vk::DescriptorPoolSize poolSize = descriptorPool.createUniformPoolSize();

		ASSERT_EQ(poolSize.type, vk::DescriptorType::eUniformBuffer);
		ASSERT_EQ(poolSize.descriptorCount, 1u);
	}

	TEST(DescriptorPool, CreateImageSamplerPoolSize)
	{
		DescriptorPool descriptorPool;
		vk::DescriptorPoolSize poolSize = descriptorPool.createImageSamplerPoolSize();

		ASSERT_EQ(poolSize.type, vk::DescriptorType::eCombinedImageSampler);
		ASSERT_EQ(poolSize.descriptorCount, 1u);
	}

	TEST(DescriptorPool, CreateCreateInfo)
	{
		DescriptorPool descriptorPool;
		vk::DescriptorPoolSize uniformPoolSize = descriptorPool.createUniformPoolSize();
		vk::DescriptorPoolSize imageSamplerPoolSize = descriptorPool.createImageSamplerPoolSize();

		std::vector<vk::DescriptorPoolSize> poolSizes = { uniformPoolSize, imageSamplerPoolSize };
		vk::DescriptorPoolCreateInfo createInfo = descriptorPool.createCreateInfo(poolSizes);

		ASSERT_EQ(createInfo.poolSizeCount, poolSizes.size());
		ASSERT_EQ(createInfo.pPoolSizes, poolSizes.data());
		ASSERT_EQ(createInfo.maxSets, 1u);
		ASSERT_EQ(createInfo.flags, vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet);
	}

	TEST_F(DescriptorPoolTests, CreateAllocateInfo)
	{
		DescriptorSetLayout descriptorSetLayout;
		vk::DescriptorSetLayoutBinding uniformLayoutBinding = descriptorSetLayout.createUniformLayoutBinding();
		vk::DescriptorSetLayoutBinding imageSamplerLayoutBinding = descriptorSetLayout.createImageSamplerLayoutBinding();

		std::vector<vk::DescriptorSetLayoutBinding> bindings = { uniformLayoutBinding, imageSamplerLayoutBinding };
		vk::DescriptorSetLayoutCreateInfo createInfo = descriptorSetLayout.createDescriptorSetLayoutCreateInfo(bindings);
		descriptorSetLayout.create(device, createInfo);

		std::vector<vk::DescriptorSetLayout> descriptorSetLayouts = { *descriptorSetLayout.getInternal() };
		vk::DescriptorSetAllocateInfo allocateInfo = descriptorPool.createDescriptorSetAllocateInfo(descriptorSetLayouts);

		ASSERT_EQ(allocateInfo.descriptorPool, *descriptorPool.getInternal());
		ASSERT_EQ(allocateInfo.descriptorSetCount, descriptorSetLayouts.size());
		ASSERT_EQ(allocateInfo.pSetLayouts, reinterpret_cast<vk::DescriptorSetLayout*>(descriptorSetLayouts.data()));
	}

	TEST_F(DescriptorPoolTests, Create)
	{
		ASSERT_NE(*descriptorPool.getInternal(), *vk::raii::DescriptorPool{ std::nullptr_t{} });
	}

}
