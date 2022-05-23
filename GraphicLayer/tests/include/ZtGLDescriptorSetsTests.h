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

#include "gtest/gtest.h"

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
			GLFW::InitGLFW();

			window.create();
			instance.createApplicationInfo();
			instance.createInstanceCreateInfo();
			instance.create(context);
			surface.create(instance, window);
			physicalDevice.create(instance);
			device.create(physicalDevice, surface);

			descriptorPool.createPoolSize();
			vk::DescriptorPoolCreateInfo descriptorPoolCreateInfo = descriptorPool.createCreateInfo();
			descriptorPool.create(device, descriptorPoolCreateInfo);

			descriptorSetLayout.createDescriptorSetLayoutBinding();
			vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo = descriptorSetLayout.createDescriptorSetLayoutCreateInfo();
			descriptorSetLayout.create(device, descriptorSetLayoutCreateInfo);

			vk::DescriptorSetAllocateInfo allocateInfo = descriptorSetLayout.createAllocateInfo(descriptorPool);
			descriptorSets = DescriptorSets{ device, allocateInfo };
		}

		void TearDown() override
		{
			GLFW::DeinitGLFW();
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

	TEST_F(DescriptorSetsTests, CreateWriteDescriptorSet)
	{
		vk::DescriptorBufferInfo bufferInfo;
		vk::WriteDescriptorSet writeDescriptorSet = descriptorSets->createWriteDescriptorSet(0u, bufferInfo);
		
		ASSERT_EQ(writeDescriptorSet.dstSet, *(*descriptorSets)[0]);
		ASSERT_EQ(writeDescriptorSet.dstBinding, 0);
		ASSERT_EQ(writeDescriptorSet.dstArrayElement, 0);
		ASSERT_EQ(writeDescriptorSet.descriptorType, vk::DescriptorType::eUniformBuffer);
		ASSERT_EQ(writeDescriptorSet.descriptorCount, 1);
		ASSERT_EQ(writeDescriptorSet.pBufferInfo, &bufferInfo);
		ASSERT_EQ(writeDescriptorSet.pImageInfo, nullptr);
		ASSERT_EQ(writeDescriptorSet.pTexelBufferView, nullptr);
	}
}
