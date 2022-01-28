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
		Window window;
		window.createWindow();

		Context context;

		Instance instance;
		instance.create(context);

		Surface surface;
		surface.create(instance, window);
		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);

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
		instance.create(context);
		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);
		device.createDevice(physicalDevice);
		const vk::raii::Device& internal = device.getInternal();

		ASSERT_NE(*internal, *vk::raii::Device(std::nullptr_t()));
	}

	TEST_F(DeviceTests, CreateQueue)
	{
		Window window;
		window.createWindow();

		Context context;

		instance.createApplicationInfo();
		instance.createInstanceCreateInfo();
		instance.create(context);

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);
		device.createDeviceQueueCreateInfo(physicalDevice, surface);

		uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
		device.createDevice(physicalDevice);
		Queue queue = device.createQueue(queueFamilyIndex);

		ASSERT_NE(*queue.getInternal(), *vk::raii::Queue(std::nullptr_t()));

		surface.destroy(instance);
	}

}