#pragma once

#include "Zinet/GraphicLayer/ZtGLFence.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class FenceTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		Fence fence;

		void SetUp() override
		{
			GLFW::Init();

			vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
			instance.populateRequiredExtensions();
			vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
			instance.create(context, instanceCreateInfo);
			window.create();
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

	TEST(Fence, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<Fence, VulkanObject<vk::raii::Fence>>);
	}

	TEST(Fence, CreateFenceCreateInfoTest)
	{
		Fence fence;
		vk::FenceCreateInfo createInfo = fence.createFenceCreateInfo();

		ASSERT_EQ(createInfo, vk::FenceCreateInfo{});
	}

	TEST_F(FenceTests, CreateTest)
	{
		fence.createUnsignaled(device);

		ASSERT_NE(*fence.getInternal(), *vk::raii::Fence{ std::nullptr_t{} });
	}

	TEST_F(FenceTests, CreateSignaledTest)
	{
		fence.createSignaled(device);

		ASSERT_NE(*fence.getInternal(), *vk::raii::Fence{ std::nullptr_t{} });
	}

	TEST_F(FenceTests, GetStatusTest)
	{
		fence.createSignaled(device);
		vk::Result result = fence.getStatus();

		ASSERT_EQ(result, vk::Result::eSuccess);
	}
}
