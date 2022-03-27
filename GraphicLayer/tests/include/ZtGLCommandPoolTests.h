#pragma once

#include "Zinet/GraphicLayer/ZtGLCommandPool.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class CommandPoolTests : public ::testing::Test
	{
	protected:

		std::unique_ptr<CommandPool> commandPool = std::make_unique<CommandPool>();

	};

	TEST_F(CommandPoolTests, GetInternalTest)
	{
		vk::raii::CommandPool& internal = commandPool->getInternal();
	}

	TEST_F(CommandPoolTests, CreateCommandPoolCreateInfoTest)
	{
		uint32_t queueFamilyIndex{};
		vk::CommandPoolCreateInfo createInfo = commandPool->createCommandPoolCreateInfo(queueFamilyIndex);

		ASSERT_NE(createInfo, vk::CommandPoolCreateInfo{});
	}

	TEST_F(CommandPoolTests, CreateCommandPoolTest)
	{
		GLFW::InitGLFW();

		Context context;
		Instance instance;
		instance.createInstanceCreateInfo();
		instance.create(context);

		Window window;
		window.createWindow();

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);

		Device device;
		device.create(physicalDevice, surface);

		uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
		commandPool->create(device, queueFamilyIndex);

		ASSERT_NE(*commandPool->getInternal(), *vk::raii::CommandPool{ std::nullptr_t{} });

		commandPool.reset();

		GLFW::DeinitGLFW();
	}

}
