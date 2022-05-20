#pragma once

#include "Zinet/GraphicLayer/ZtGLDescriptorPool.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

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
			GLFW::InitGLFW();

			window.create();
			instance.createApplicationInfo();
			instance.createInstanceCreateInfo();
			instance.create(context);
			surface.create(instance, window);
			physicalDevice.create(instance);
			device.create(physicalDevice, surface);

			descriptorPool.createPoolSize();
			vk::DescriptorPoolCreateInfo createInfo = descriptorPool.createCreateInfo();
			descriptorPool.create(device, createInfo);
		}

		void TearDown() override
		{
			GLFW::DeinitGLFW();
		}
	};

	TEST(DescriptorPool, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<DescriptorPool, VulkanObject<vk::raii::DescriptorPool>>);
	}

	TEST(DescriptorPool, CreatePoolSize)
	{
		DescriptorPool descriptorPool;
		const vk::DescriptorPoolSize& actualPoolSize = descriptorPool.createPoolSize();

		ASSERT_EQ(actualPoolSize.descriptorCount, 1u);

		const vk::DescriptorPoolSize& expectedPoolSize = descriptorPool.getPoolSize();
		ASSERT_EQ(&actualPoolSize, &expectedPoolSize);
	}

	TEST(DescriptorPool, GetPoolSize)
	{
		DescriptorPool descriptorPool;
		const vk::DescriptorPoolSize& poolSize = descriptorPool.getPoolSize();

		ASSERT_EQ(poolSize, vk::DescriptorPoolSize{});
	}

	TEST(DescriptorPool, CreateCreateInfo)
	{
		DescriptorPool descriptorPool;
		vk::DescriptorPoolCreateInfo createInfo = descriptorPool.createCreateInfo();

		ASSERT_EQ(createInfo.poolSizeCount, 1u);

		const vk::DescriptorPoolSize& expectedPoolSize = descriptorPool.getPoolSize();
		ASSERT_EQ(createInfo.pPoolSizes, &expectedPoolSize);
		ASSERT_EQ(createInfo.maxSets, 1u);
	}

	TEST_F(DescriptorPoolTests, Create)
	{
		ASSERT_NE(*descriptorPool.getInternal(), *vk::raii::DescriptorPool{ std::nullptr_t{} });
	}

}
