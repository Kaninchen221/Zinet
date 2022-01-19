#pragma once

#include "Zinet/GraphicLayer/ZtGLDevice.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class DeviceTests : public ::testing::Test
	{
	protected:

		Instance instance;
		Device device;

	};

	TEST_F(DeviceTests, CreateQueueCreateInfo)
	{
		Context context;
		instance.createInstance(context);
		PhysicalDevice physicalDevice = instance.pickPhysicalDevice();
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice);

		ASSERT_NE(deviceQueueCreateInfo, vk::DeviceQueueCreateInfo());
	}

	TEST_F(DeviceTests, CreateDeviceCreateInfo)
	{
		PhysicalDevice physicalDevice;
		vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice);

		ASSERT_NE(deviceCreateInfo, vk::DeviceCreateInfo());
	}

	TEST_F(DeviceTests, CreateDevice)
	{
		Context context;
		instance.createInstance(context);
		PhysicalDevice physicalDevice = instance.pickPhysicalDevice();
		device.createDevice(physicalDevice);
		const vk::raii::Device& internal = device.getInternal();

		ASSERT_NE(*internal, *vk::raii::Device(std::nullptr_t()));
	}

	TEST_F(DeviceTests, CreateQueue)
	{
		Context context;
		instance.createInstance(context);
		PhysicalDevice physicalDevice = instance.pickPhysicalDevice();
		device.createDeviceQueueCreateInfo(physicalDevice);

		uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex();
		device.createDevice(physicalDevice);
		Queue queue = device.createQueue(queueFamilyIndex);

		ASSERT_NE(*queue.getInternal(), *vk::raii::Queue(std::nullptr_t()));
	}

}