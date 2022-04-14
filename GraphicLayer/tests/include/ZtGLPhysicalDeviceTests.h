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

	TEST(PhysicalDevice, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<PhysicalDevice, VulkanObject<vk::raii::PhysicalDevice>>);
	}

	TEST(PhysicalDevice, CreateFeaturesTest)
	{
		PhysicalDevice physicalDevice;
		physicalDevice.createFeatures();
	}

	TEST(PhysicalDevice, GetFeaturesTest)
	{
		PhysicalDevice physicalDevice;
		physicalDevice.createFeatures();
		const vk::PhysicalDeviceFeatures& physicalDeviceFeatures = physicalDevice.getFeatures();
	}

	TEST(PhysicalDevice, PhysicalDeviceExtensions)
	{
		PhysicalDevice physicalDevice;
		const std::vector<const char*>& physicalDeviceExtensions = physicalDevice.GetPhysicalDeviceExtensions();

		ASSERT_FALSE(physicalDeviceExtensions.empty());
	}

	TEST_F(PhysicalDeviceTests, PickQueueFamilyIndexTest)
	{
		GLFW::InitGLFW();

		Window window;
		window.create();

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
	}

	TEST_F(PhysicalDeviceTests, Create)
	{
		Context context;
		Instance instance;
		instance.create(context);
		bool result = physicalDevice.create(instance);

		ASSERT_TRUE(result);
	}

	TEST_F(PhysicalDeviceTests, GetSwaptChainSupportDetailsTest)
	{
		GLFW::InitGLFW();

		Window window;
		window.create();

		Context context;
		Instance instance;
		instance.createInstanceCreateInfo();
		instance.create(context);

		Surface surface;
		surface.create(instance, window);

		physicalDevice.create(instance);

		SwapChainSupportDetails swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);

		ASSERT_NE(swapChainSupportDetails.surfaceCapabilities, vk::SurfaceCapabilitiesKHR());
		ASSERT_FALSE(swapChainSupportDetails.surfaceFormats.empty());
		ASSERT_FALSE(swapChainSupportDetails.presentModes.empty());

		GLFW::DeinitGLFW();
	}

}