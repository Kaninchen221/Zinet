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

#include "gtest/gtest.h"

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
			instance.createApplicationInfo();
			instance.createInstanceCreateInfo();
			instance.create(context);
			surface.create(instance, window);
			physicalDevice.create(instance);

			vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
			vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice, surface, deviceQueueCreateInfo);
			device.create(physicalDevice, deviceCreateInfo);

			vk::DescriptorPoolSize poolSize = descriptorPool.createPoolSize();
			vk::DescriptorPoolCreateInfo createInfo = descriptorPool.createCreateInfo(poolSize);
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

	TEST(DescriptorPool, CreatePoolSize)
	{
		DescriptorPool descriptorPool;
		vk::DescriptorPoolSize actualPoolSize = descriptorPool.createPoolSize();

		ASSERT_EQ(actualPoolSize.descriptorCount, 1u);
	}

	TEST(DescriptorPool, CreateCreateInfo)
	{
		DescriptorPool descriptorPool;
		vk::DescriptorPoolSize poolSize = descriptorPool.createPoolSize();
		vk::DescriptorPoolCreateInfo createInfo = descriptorPool.createCreateInfo(poolSize);

		ASSERT_EQ(createInfo.poolSizeCount, 1u);
		ASSERT_EQ(createInfo.pPoolSizes, &poolSize);
		ASSERT_EQ(createInfo.maxSets, 1u);
		ASSERT_EQ(createInfo.flags, vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet);
	}

	TEST_F(DescriptorPoolTests, CreateAllocateInfo)
	{
		DescriptorSetLayout descriptorSetLayout;
		vk::DescriptorSetLayoutBinding descriptorSetLayoutBinding = descriptorSetLayout.createDescriptorSetLayoutBinding();
		vk::DescriptorSetLayoutCreateInfo createInfo = descriptorSetLayout.createDescriptorSetLayoutCreateInfo(descriptorSetLayoutBinding);
		descriptorSetLayout.create(device, createInfo);

		vk::DescriptorSetAllocateInfo allocateInfo = descriptorPool.createDescriptorSetAllocateInfo(descriptorSetLayout);

		ASSERT_EQ(allocateInfo.descriptorPool, *descriptorPool.getInternal());
		ASSERT_EQ(allocateInfo.descriptorSetCount, 1u);
		ASSERT_EQ(allocateInfo.pSetLayouts, &*descriptorSetLayout.getInternal());
	}

	TEST_F(DescriptorPoolTests, Create)
	{
		ASSERT_NE(*descriptorPool.getInternal(), *vk::raii::DescriptorPool{ std::nullptr_t{} });
	}

}
