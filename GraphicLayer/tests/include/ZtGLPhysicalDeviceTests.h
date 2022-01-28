#pragma once

#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class PhysicalDeviceTests : public ::testing::Test
	{
	protected:

		PhysicalDevice physicalDevice;

	};

	TEST_F(PhysicalDeviceTests, GetInternalTest)
	{
		const vk::raii::PhysicalDevice& internal = physicalDevice.getInternal();
	}

	TEST_F(PhysicalDeviceTests, PickQueueFamilyIndexTest)
	{
		GLFW::InitGLFW();

		Window window;
		window.createWindow();

		Context context;

		Instance instance;
		instance.createApplicationInfo();
		instance.createInstanceCreateInfo();
		instance.create(context);

		Surface surface;
		surface.create(instance, window);

		physicalDevice.create(instance);
		uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
		constexpr uint32_t notExpectedIndex = std::numeric_limits<uint32_t>::max();

		ASSERT_NE(queueFamilyIndex, notExpectedIndex);

		surface.destroy(instance);
	}

	TEST_F(PhysicalDeviceTests, CreateFeaturesTest)
	{
		physicalDevice.createFeatures();
	}

	TEST_F(PhysicalDeviceTests, GetFeaturesTest)
	{
		physicalDevice.createFeatures();
		const vk::PhysicalDeviceFeatures& physicalDeviceFeatures = physicalDevice.getFeatures();
	}

	TEST_F(PhysicalDeviceTests, EnumeratePhysicalDevices)
	{
		Context context;
		Instance instance;
		instance.create(context);
		vk::raii::PhysicalDevices physicalDevices = std::move(physicalDevice.enumeratePhysicalDevices(instance));
	}

	TEST_F(PhysicalDeviceTests, PhysicalDeviceExtensionsTest)
	{
		const std::vector<std::array<char, VK_MAX_EXTENSION_NAME_SIZE>>& physicalDeviceExtensions = physicalDevice.GetPhysicalDeviceExtensions();

		ASSERT_FALSE(physicalDeviceExtensions.empty());
	}

	TEST_F(PhysicalDeviceTests, CreateTest)
	{
		Context context;
		Instance instance;
		instance.create(context);
		bool result = physicalDevice.create(instance);

		ASSERT_TRUE(result);
	}

}