#pragma once

#include "Zinet/GraphicLayer/ZtGLDescriptorSets.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorSetLayout.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorPool.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class DescriptorSetsTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		DescriptorPool descriptorPool;
		DescriptorSetLayout descriptorSetLayout;
		std::optional<DescriptorSets> descriptorSets;

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
			vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(instance, physicalDevice, surface, deviceQueueCreateInfo);
			device.create(physicalDevice, deviceCreateInfo);

			vk::DescriptorPoolSize uniformPoolSize = descriptorPool.createUniformPoolSize();
			vk::DescriptorPoolSize imageSamplerPoolSize = descriptorPool.createImageSamplerPoolSize();

			std::vector<vk::DescriptorPoolSize> poolSizes = { uniformPoolSize, imageSamplerPoolSize };
			vk::DescriptorPoolCreateInfo descriptorPoolCreateInfo = descriptorPool.createCreateInfo(poolSizes);
			descriptorPool.create(device, descriptorPoolCreateInfo);

			vk::DescriptorSetLayoutBinding uniformLayoutBinding = descriptorSetLayout.createUniformLayoutBinding();
			vk::DescriptorSetLayoutBinding imageSamplerLayoutBinding = descriptorSetLayout.createImageSamplerLayoutBinding();

			std::vector<vk::DescriptorSetLayoutBinding> bindings = { uniformLayoutBinding, imageSamplerLayoutBinding };
			vk::DescriptorSetLayoutCreateInfo createInfo = descriptorSetLayout.createDescriptorSetLayoutCreateInfo(bindings);
			descriptorSetLayout.create(device, createInfo);

			std::vector<vk::DescriptorSetLayout> descriptorSetLayouts = { *descriptorSetLayout.getInternal() };
			vk::DescriptorSetAllocateInfo allocateInfo = descriptorPool.createDescriptorSetAllocateInfo(descriptorSetLayouts);
			descriptorSets = DescriptorSets{ device, allocateInfo };
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST(DescriptorSets, DerivedFromDescriptorSets)
	{
		static_assert(std::derived_from<DescriptorSets, vk::raii::DescriptorSets>);
	}

	TEST_F(DescriptorSetsTests, Construct)
	{
		ASSERT_NE(*(*descriptorSets)[0], *vk::raii::DescriptorSet{ std::nullptr_t{} });
	}

	TEST_F(DescriptorSetsTests, CreateBufferWriteDescriptorSet)
	{
		typedef vk::WriteDescriptorSet(DescriptorSets::* ExpectedFunctionDeclaration)(size_t, const vk::DescriptorBufferInfo&, std::uint32_t);
		using FunctionDeclaration = decltype(&DescriptorSets::createBufferWriteDescriptorSet);

		vk::DescriptorBufferInfo bufferInfo;
		size_t expectedIndex = 0u;
		vk::WriteDescriptorSet writeDescriptorSet = descriptorSets->createBufferWriteDescriptorSet(expectedIndex, bufferInfo, 0u);
		
		ASSERT_EQ(writeDescriptorSet.dstSet, *(*descriptorSets)[expectedIndex]);
		ASSERT_EQ(writeDescriptorSet.dstBinding, 0);
		ASSERT_EQ(writeDescriptorSet.dstArrayElement, 0);
		ASSERT_EQ(writeDescriptorSet.descriptorType, vk::DescriptorType::eUniformBuffer);
		ASSERT_EQ(writeDescriptorSet.descriptorCount, 1);
		ASSERT_EQ(writeDescriptorSet.pBufferInfo, &bufferInfo);
		ASSERT_EQ(writeDescriptorSet.pImageInfo, nullptr);
		ASSERT_EQ(writeDescriptorSet.pTexelBufferView, nullptr);
	}

	TEST_F(DescriptorSetsTests, CreateImageWriteDescriptorSet)
	{
		typedef vk::WriteDescriptorSet(DescriptorSets::* ExpectedFunctionDeclaration)(size_t, const vk::DescriptorImageInfo&, std::uint32_t);
		using FunctionDeclaration = decltype(&DescriptorSets::createImageWriteDescriptorSet);

		vk::DescriptorImageInfo imageInfo;
		size_t expectedIndex = 0u;
		vk::WriteDescriptorSet writeDescriptorSet = descriptorSets->createImageWriteDescriptorSet(expectedIndex, imageInfo, 1u);
	
		ASSERT_EQ(writeDescriptorSet.dstSet, *(*descriptorSets)[expectedIndex]);
		ASSERT_EQ(writeDescriptorSet.dstBinding, 1);
		ASSERT_EQ(writeDescriptorSet.dstArrayElement, 0);
		ASSERT_EQ(writeDescriptorSet.descriptorType, vk::DescriptorType::eCombinedImageSampler);
		ASSERT_EQ(writeDescriptorSet.descriptorCount, 1);
		ASSERT_EQ(writeDescriptorSet.pBufferInfo, nullptr);
		ASSERT_EQ(writeDescriptorSet.pImageInfo, &imageInfo);
		ASSERT_EQ(writeDescriptorSet.pTexelBufferView, nullptr);
	}
}
