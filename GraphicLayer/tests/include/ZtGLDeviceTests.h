#pragma once

#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLFence.h"
#include "Zinet/GraphicLayer/ZtGLQueue.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class DeviceTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;

		void SetUp() override
		{
			GLFW::InitGLFW();

			window.createWindow();
			instance.createApplicationInfo();
			instance.createInstanceCreateInfo();
			instance.create(context);
			surface.create(instance, window);
			physicalDevice.create(instance);
		}

		void TearDown() override
		{
			surface.destroy(instance);
			GLFW::DeinitGLFW();
		}
	};

	TEST_F(DeviceTests, CreateQueueCreateInfo)
	{
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);

		ASSERT_NE(deviceQueueCreateInfo, vk::DeviceQueueCreateInfo());
	}

	TEST_F(DeviceTests, CreateDeviceCreateInfo)
	{
		vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice, surface);

		ASSERT_NE(deviceCreateInfo, vk::DeviceCreateInfo());
	}

	TEST_F(DeviceTests, CreateDevice)
	{
		device.create(physicalDevice, surface);
		vk::raii::Device& internal = device.getInternal();

		ASSERT_NE(*internal, *vk::raii::Device(std::nullptr_t()));
	}

	TEST_F(DeviceTests, CreateQueue)
	{
		device.create(physicalDevice, surface);

		uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
		device.createDeviceQueueCreateInfo(physicalDevice, surface);
		Queue queue = device.createQueue(queueFamilyIndex);

		ASSERT_NE(*queue.getInternal(), *vk::raii::Queue(std::nullptr_t()));
	}

	TEST_F(DeviceTests, WaitForFence)
	{
		device.create(physicalDevice, surface);

		Fence fence;
		fence.create(device);

		uint64_t timeout = 1;
		vk::Result result = device.waitForFence(fence, timeout);
	}
}