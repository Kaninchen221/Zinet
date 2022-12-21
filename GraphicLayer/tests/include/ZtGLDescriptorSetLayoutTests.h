#pragma once

#include "Zinet/GraphicLayer/ZtGLDescriptorSetLayout.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorPool.h"

#include <gtest/gtest.h>

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
			vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
			instance.populateRequiredExtensions();
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

	TEST(DescriptorSetLayout, DerivedFrom)
	{
		static_assert(std::derived_from<DescriptorSetLayout, VulkanObject<vk::raii::DescriptorSetLayout>>);
	}

	TEST(DescriptorSetLayout, CreateUniformLayoutBinding)
	{
		DescriptorSetLayout descriptorSetLayout;
		vk::DescriptorSetLayoutBinding uniformLayoutBinding = descriptorSetLayout.createUniformLayoutBinding();

		ASSERT_EQ(uniformLayoutBinding.binding, 0);
		ASSERT_EQ(uniformLayoutBinding.descriptorType, vk::DescriptorType::eUniformBuffer);
		ASSERT_EQ(uniformLayoutBinding.descriptorCount, 1);
		ASSERT_EQ(uniformLayoutBinding.stageFlags, vk::ShaderStageFlagBits::eVertex);
		ASSERT_EQ(uniformLayoutBinding.pImmutableSamplers, nullptr);

	}

	TEST(DescriptorSetLayout, CreateImageSamplerLayoutBinding)
	{
		DescriptorSetLayout descriptorSetLayout;
		vk::DescriptorSetLayoutBinding imageSamplerLayoutBinding = descriptorSetLayout.createImageSamplerLayoutBinding();

		ASSERT_EQ(imageSamplerLayoutBinding.binding, 1);
		ASSERT_EQ(imageSamplerLayoutBinding.descriptorType, vk::DescriptorType::eCombinedImageSampler);
		ASSERT_EQ(imageSamplerLayoutBinding.descriptorCount, 1);
		ASSERT_EQ(imageSamplerLayoutBinding.stageFlags, vk::ShaderStageFlagBits::eFragment);
		ASSERT_EQ(imageSamplerLayoutBinding.pImmutableSamplers, nullptr);

	}

	TEST(DescriptorSetLayout, CreateDescriptorSetLayoutCreateInfo)
	{
		DescriptorSetLayout descriptorSetLayout;
		vk::DescriptorSetLayoutBinding uniformLayoutBinding = descriptorSetLayout.createUniformLayoutBinding();
		vk::DescriptorSetLayoutBinding imageSamplerLayoutBinding = descriptorSetLayout.createImageSamplerLayoutBinding();

		std::vector<vk::DescriptorSetLayoutBinding> bindings = { uniformLayoutBinding, imageSamplerLayoutBinding };
		vk::DescriptorSetLayoutCreateInfo createInfo = descriptorSetLayout.createDescriptorSetLayoutCreateInfo(bindings);

		ASSERT_EQ(createInfo.bindingCount, bindings.size());
		ASSERT_EQ(createInfo.pBindings, bindings.data());
	}

	TEST_F(DescriptorSetLayoutTests, Create)
	{
		vk::DescriptorSetLayoutBinding uniformLayoutBinding = descriptorSetLayout.createUniformLayoutBinding();
		vk::DescriptorSetLayoutBinding imageSamplerLayoutBinding = descriptorSetLayout.createImageSamplerLayoutBinding();

		std::vector<vk::DescriptorSetLayoutBinding> bindings = { uniformLayoutBinding, imageSamplerLayoutBinding };
		vk::DescriptorSetLayoutCreateInfo createInfo = descriptorSetLayout.createDescriptorSetLayoutCreateInfo(bindings);
		descriptorSetLayout.create(device, createInfo);

		ASSERT_NE(*descriptorSetLayout.getInternal(), *vk::raii::DescriptorSetLayout{ std::nullptr_t{} });
	}
}
