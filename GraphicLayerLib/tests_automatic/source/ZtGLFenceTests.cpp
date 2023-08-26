#pragma once

#include "Zinet/GraphicLayer/ZtGLFence.h"
#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

#include "Zinet/Window/ZtWindow.h"
#include "Zinet/Window/ZtGLFW.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class FenceTests : public ::testing::Test
	{
	protected:

		static_assert(std::derived_from<Fence, VulkanObject<vk::raii::Fence>>);

		Context context;
		Instance instance;
		wd::Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		Fence fence;

		void SetUp() override
		{
			wd::GLFW::Init();

			vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
			instance.populateRequiredExtensions();
			vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
			instance.create(context, instanceCreateInfo);
			window.create();
			surface.create(instance, window);
			physicalDevice.create(instance);

			vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
			vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(instance, physicalDevice, surface, deviceQueueCreateInfo);
			device.create(physicalDevice, deviceCreateInfo);
		}

		void TearDown() override
		{
			wd::GLFW::Deinit();
		}
	};

	TEST(Fence, CreateSignaledFenceCreateInfo)
	{
		Fence fence;
		vk::FenceCreateInfo fenceCreateInfo = fence.createSignaledFenceCreateInfo();
		vk::FenceCreateInfo expectedCreateInfo;
		expectedCreateInfo.flags = vk::FenceCreateFlagBits::eSignaled;

		ASSERT_EQ(fenceCreateInfo, expectedCreateInfo);
	}

	TEST(Fence, CreateUnsignaledFenceCreateInfo)
	{
		Fence fence;
		vk::FenceCreateInfo fenceCreateInfo = fence.createUnsignaledFenceCreateInfo();
		vk::FenceCreateInfo expectedCreateInfo{};

		ASSERT_EQ(fenceCreateInfo, expectedCreateInfo);
	}

	TEST_F(FenceTests, CreateUnsignaledTest)
	{
		vk::FenceCreateInfo fenceCreateInfo = fence.createUnsignaledFenceCreateInfo();
		fence.create(device, fenceCreateInfo);

		ASSERT_TRUE(fence.isValid());
	}

	TEST_F(FenceTests, CreateSignaledTest)
	{
		vk::FenceCreateInfo fenceCreateInfo = fence.createSignaledFenceCreateInfo();
		fence.create(device, fenceCreateInfo);

		ASSERT_TRUE(fence.isValid());
	}

	TEST_F(FenceTests, GetStatusTest)
	{
		vk::FenceCreateInfo fenceCreateInfo = fence.createSignaledFenceCreateInfo();
		fence.create(device, fenceCreateInfo);
		vk::Result result = fence.getStatus();

		ASSERT_EQ(result, vk::Result::eSuccess);
	}
}
