#pragma once

#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class DeviceTests : public ::testing::Test
	{
	protected:

		Instance instance;
		Device device;

		void SetUp() override
		{
			GLFW::InitGLFW();
		}

		void TearDown() override
		{
			GLFW::DeinitGLFW();
		}
	};

	TEST_F(DeviceTests, CreateQueueCreateInfo)
	{
		Window window;
		window.createWindow();

		Context context;

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
		Window window;
		window.createWindow();

		Context context;

		instance.create(context);

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);

		vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice, surface);

		ASSERT_NE(deviceCreateInfo, vk::DeviceCreateInfo());
	}

	TEST_F(DeviceTests, CreateDevice)
	{
		Context context;
		instance.createInstanceCreateInfo();
		instance.create(context);

		Window window;
		window.createWindow();

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);
		device.create(physicalDevice, surface);
		vk::raii::Device& internal = device.getInternal();

		ASSERT_NE(*internal, *vk::raii::Device(std::nullptr_t()));

		surface.destroy(instance);
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
		device.create(physicalDevice, surface);
		Queue queue = device.createQueue(queueFamilyIndex);

		ASSERT_NE(*queue.getInternal(), *vk::raii::Queue(std::nullptr_t()));

		surface.destroy(instance);
	}

}