#pragma once

#include "Zinet/GraphicLayer/ZtGLCommandPool.hpp"
#include "Zinet/GraphicLayer/ZtGLContext.hpp"
#include "Zinet/GraphicLayer/ZtGLInstance.hpp"
#include "Zinet/GraphicLayer/ZtGLSurface.hpp"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLDevice.hpp"

#include "Zinet/Window/ZtWindow.hpp"
#include "Zinet/Window/ZtGLFW.hpp"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class CommandPoolTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		wd::Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		CommandPool commandPool;

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

	TEST(CommandPool, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<CommandPool, VulkanObject<vk::raii::CommandPool>>);
	}

	TEST(CommandPool, CreateCommandPoolCreateInfoTest)
	{
		CommandPool commandPool;
		uint32_t queueFamilyIndex{};
		vk::CommandPoolCreateInfo createInfo = commandPool.createCommandPoolCreateInfo(queueFamilyIndex);

		ASSERT_NE(createInfo, vk::CommandPoolCreateInfo{});
	}

	TEST_F(CommandPoolTests, CreateCommandPoolTest)
	{
		uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
		commandPool.create(device, queueFamilyIndex);

		ASSERT_NE(*commandPool.getInternal(), *vk::raii::CommandPool{ std::nullptr_t{} });
	}

}
