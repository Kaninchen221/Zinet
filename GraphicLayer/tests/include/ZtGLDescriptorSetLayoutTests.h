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
			GLFW::InitGLFW();

			window.create();
			instance.createApplicationInfo();
			instance.createInstanceCreateInfo();
			instance.create(context);
			surface.create(instance, window);
			physicalDevice.create(instance);
			device.create(physicalDevice, surface);
		}

		void TearDown() override
		{
			GLFW::DeinitGLFW();
		}
	};

	TEST(DescriptorSetLayout, DerivedFrom)
	{
		static_assert(std::derived_from<DescriptorSetLayout, VulkanObject<vk::raii::DescriptorSetLayout>>);
	}

	TEST(DescriptorSetLayout, CreateDescriptorSetLayoutBinding)
	{
		DescriptorSetLayout descriptorSetLayout;
		descriptorSetLayout.createDescriptorSetLayoutBinding();
		const vk::DescriptorSetLayoutBinding& descriptorSetLayoutBinding = descriptorSetLayout.getDescriptorSetLayoutBinding();

		ASSERT_EQ(descriptorSetLayoutBinding.binding, 0);
		ASSERT_EQ(descriptorSetLayoutBinding.descriptorType, vk::DescriptorType::eUniformBuffer);
		ASSERT_EQ(descriptorSetLayoutBinding.descriptorCount, 1);
		ASSERT_EQ(descriptorSetLayoutBinding.stageFlags, vk::ShaderStageFlagBits::eVertex);
		ASSERT_EQ(descriptorSetLayoutBinding.pImmutableSamplers, nullptr);

	}

	TEST(DescriptorSetLayout, GetDescriptorSetLayoutBinding)
	{
		DescriptorSetLayout descriptorSetLayout;
		const vk::DescriptorSetLayoutBinding& descriptorSetLayoutBinding = descriptorSetLayout.getDescriptorSetLayoutBinding();

		ASSERT_EQ(descriptorSetLayoutBinding, vk::DescriptorSetLayoutBinding{});
	}

	TEST(DescriptorSetLayout, CreateDescriptorSetLayoutCreateInfo)
	{
		DescriptorSetLayout descriptorSetLayout;
		descriptorSetLayout.createDescriptorSetLayoutBinding();
		vk::DescriptorSetLayoutCreateInfo createInfo = descriptorSetLayout.createDescriptorSetLayoutCreateInfo();
		const vk::DescriptorSetLayoutBinding& descriptorSetLayoutBinding = descriptorSetLayout.getDescriptorSetLayoutBinding();

		ASSERT_EQ(createInfo.bindingCount, 1);
		ASSERT_EQ(createInfo.pBindings, &descriptorSetLayoutBinding);
	}

	TEST_F(DescriptorSetLayoutTests, CreateAllocateInfo)
	{
		DescriptorPool descriptorPool;
		descriptorPool.createPoolSize();
		vk::DescriptorPoolCreateInfo descriptorPoolCreateInfo = descriptorPool.createCreateInfo();
		descriptorPool.create(device, descriptorPoolCreateInfo);

		vk::DescriptorSetAllocateInfo allocateInfo = descriptorSetLayout.createAllocateInfo(descriptorPool);

		ASSERT_EQ(allocateInfo.descriptorPool, *descriptorPool.getInternal());
		ASSERT_EQ(allocateInfo.descriptorSetCount, 1u);
		ASSERT_EQ(allocateInfo.pSetLayouts, &*descriptorSetLayout.getInternal());
	}

	TEST_F(DescriptorSetLayoutTests, Create)
	{
		descriptorSetLayout.createDescriptorSetLayoutBinding();
		vk::DescriptorSetLayoutCreateInfo createInfo = descriptorSetLayout.createDescriptorSetLayoutCreateInfo();
		descriptorSetLayout.create(device, createInfo);

		ASSERT_NE(*descriptorSetLayout.getInternal(), *vk::raii::DescriptorSetLayout{ std::nullptr_t{} });
	}
}
