#pragma once

#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ContextTests : public ::testing::Test
	{
	protected:

		Context context;

	};

	TEST_F(ContextTests, CreateQueueCreateInfo)
	{
		vk::raii::PhysicalDevice physicalDevice = context.instanceHelper.pickPhysicalDevice();
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = context.createDeviceQueueCreateInfo(physicalDevice);

		ASSERT_NE(deviceQueueCreateInfo, vk::DeviceQueueCreateInfo());
	}

	TEST_F(ContextTests, CreateDeviceCreateInfo)
	{
		vk::DeviceCreateInfo deviceCreateInfo = context.createDeviceCreateInfo();

		ASSERT_NE(deviceCreateInfo, vk::DeviceCreateInfo());
	}

	TEST_F(ContextTests, CreateDevice)
	{
		vk::raii::PhysicalDevice physicalDevice = context.instanceHelper.pickPhysicalDevice();
		context.createDeviceQueueCreateInfo(physicalDevice);
		context.createDeviceCreateInfo();
		vk::raii::Device device = context.createDevice(physicalDevice);

		ASSERT_NE(*device, *vk::raii::Device(std::nullptr_t()));
	}
	
	TEST_F(ContextTests, CreateQueue)
	{
		vk::raii::PhysicalDevice physicalDevice = context.instanceHelper.pickPhysicalDevice();
		context.createDeviceQueueCreateInfo(physicalDevice);

		PhysicalDevice physicalDeviceHelper;
		uint32_t queueFamilyIndex = physicalDeviceHelper.pickQueueFamilyIndex(physicalDevice);
		vk::raii::Device device = context.createDevice(physicalDevice);
		vk::raii::Queue queue = context.createQueue(device, queueFamilyIndex);

		ASSERT_NE(*queue, *vk::raii::Queue(std::nullptr_t()));
	}
}