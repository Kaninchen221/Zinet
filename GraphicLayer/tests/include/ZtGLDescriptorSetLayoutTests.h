#pragma once

#include "Zinet/GraphicLayer/ZtGLDescriptorSetLayout.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorPool.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class DescriptorSetLayoutTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		DescriptorSetLayout descriptorSetLayout;

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
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST(DescriptorSetLayout, DerivedFrom)
	{
		static_assert(std::derived_from<DescriptorSetLayout, VulkanObject<vk::raii::DescriptorSetLayout>>);
	}

	TEST(DescriptorSetLayout, CreateDescriptorSetLayoutBinding)
	{
		DescriptorSetLayout descriptorSetLayout;
		vk::DescriptorSetLayoutBinding descriptorSetLayoutBinding = descriptorSetLayout.createDescriptorSetLayoutBinding();

		ASSERT_EQ(descriptorSetLayoutBinding.binding, 0);
		ASSERT_EQ(descriptorSetLayoutBinding.descriptorType, vk::DescriptorType::eUniformBuffer);
		ASSERT_EQ(descriptorSetLayoutBinding.descriptorCount, 1);
		ASSERT_EQ(descriptorSetLayoutBinding.stageFlags, vk::ShaderStageFlagBits::eVertex);
		ASSERT_EQ(descriptorSetLayoutBinding.pImmutableSamplers, nullptr);

	}

	TEST(DescriptorSetLayout, CreateDescriptorSetLayoutCreateInfo)
	{
		DescriptorSetLayout descriptorSetLayout;
		vk::DescriptorSetLayoutBinding descriptorSetLayoutBinding = descriptorSetLayout.createDescriptorSetLayoutBinding();
		vk::DescriptorSetLayoutCreateInfo createInfo = descriptorSetLayout.createDescriptorSetLayoutCreateInfo(descriptorSetLayoutBinding);

		ASSERT_EQ(createInfo.bindingCount, 1);
		ASSERT_EQ(createInfo.pBindings, &descriptorSetLayoutBinding);
	}

	TEST_F(DescriptorSetLayoutTests, Create)
	{
		vk::DescriptorSetLayoutBinding descriptorSetLayoutBinding = descriptorSetLayout.createDescriptorSetLayoutBinding();
		vk::DescriptorSetLayoutCreateInfo createInfo = descriptorSetLayout.createDescriptorSetLayoutCreateInfo(descriptorSetLayoutBinding);
		descriptorSetLayout.create(device, createInfo);

		ASSERT_NE(*descriptorSetLayout.getInternal(), *vk::raii::DescriptorSetLayout{ std::nullptr_t{} });
	}
}
