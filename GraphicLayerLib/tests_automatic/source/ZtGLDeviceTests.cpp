#pragma once

#include "Zinet/GraphicLayer/ZtGLDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLFence.hpp"
#include "Zinet/GraphicLayer/ZtGLQueue.hpp"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLSurface.hpp"
#include "Zinet/GraphicLayer/ZtGLInstance.hpp"

#include "Zinet/Window/ZtWindow.hpp"
#include "Zinet/Window/ZtGLFW.hpp"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class DeviceTests : public ::testing::Test
	{
	protected:

		static_assert(std::derived_from<Device, VulkanObject<vk::raii::Device>>);

		Context context;
		Instance instance;
		wd::Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;

		void SetUp() override
		{
			wd::GLFW::Init();

			window.create();
			vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
			instance.populateRequiredExtensions();
			vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
			instance.create(context, instanceCreateInfo);
			surface.create(instance, window);
			physicalDevice.create(instance);
		}

		void TearDown() override
		{
			wd::GLFW::Deinit();
		}
	};

	TEST_F(DeviceTests, CreateQueueCreateInfo)
	{
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);

		ASSERT_NE(deviceQueueCreateInfo, vk::DeviceQueueCreateInfo());
	}

	TEST_F(DeviceTests, CreateDeviceCreateInfo)
	{
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
		vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(instance, physicalDevice, surface, deviceQueueCreateInfo);

		ASSERT_NE(deviceCreateInfo, vk::DeviceCreateInfo());
	}

	TEST_F(DeviceTests, CreateDevice)
	{
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
		vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(instance, physicalDevice, surface, deviceQueueCreateInfo);
		device.create(physicalDevice, deviceCreateInfo);
		vk::raii::Device& internal = device.getInternal();

		ASSERT_NE(*internal, *vk::raii::Device(std::nullptr_t()));
	}

	TEST_F(DeviceTests, WaitForFence)
	{
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
		vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(instance, physicalDevice, surface, deviceQueueCreateInfo);
		device.create(physicalDevice, deviceCreateInfo);

		Fence fence;
		vk::FenceCreateInfo fenceCreateInfo = fence.createSignaledFenceCreateInfo();
		fence.create(device, fenceCreateInfo);

		uint64_t timeout = 1;
		[[maybe_unused]] vk::Result result = device.waitForFence(fence, timeout);
	}

	TEST_F(DeviceTests, ResetFence)
	{
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
		vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(instance, physicalDevice, surface, deviceQueueCreateInfo);
		device.create(physicalDevice, deviceCreateInfo);

		Fence fence;
		vk::FenceCreateInfo fenceCreateInfo = fence.createSignaledFenceCreateInfo();
		fence.create(device, fenceCreateInfo);

		device.resetFence(fence);
	}
}