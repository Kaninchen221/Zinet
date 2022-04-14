#pragma once

#include "Zinet/GraphicLayer/ZtGLCommandPool.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class CommandPoolTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		CommandPool commandPool;

		void SetUp() override
		{
			GLFW::InitGLFW();

			instance.createInstanceCreateInfo();
			instance.create(context);

			window.create();

			surface.create(instance, window);

			physicalDevice.create(instance);

			device.create(physicalDevice, surface);
		}

		void TearDown() override
		{
			GLFW::DeinitGLFW();
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
