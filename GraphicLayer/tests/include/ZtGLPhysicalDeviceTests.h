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

	TEST(PhysicalDevice, GetFeaturesTest)
	{
		PhysicalDevice physicalDevice;
		const vk::PhysicalDeviceFeatures& physicalDeviceFeatures = physicalDevice.getFeatures();
	}

	TEST(PhysicalDevice, PhysicalDeviceExtensions)
	{
		PhysicalDevice physicalDevice;
		const std::vector<const char*>& physicalDeviceExtensions = physicalDevice.getPhysicalDeviceExtensions();

		ASSERT_FALSE(physicalDeviceExtensions.empty());
	}

	TEST_F(PhysicalDeviceTests, PickQueueFamilyIndexTest)
	{
		GLFW::Init();

		Window window;
		window.create();

		Context context;

		Instance instance;
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		instance.getRequiredExtensions();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);

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
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		instance.getRequiredExtensions();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);
		bool result = physicalDevice.create(instance);

		ASSERT_TRUE(result);
	}

	TEST_F(PhysicalDeviceTests, GetSwaptChainSupportDetailsTest)
    {
		GLFW::Init();

		Window window;
		window.create();

		Context context;
		Instance instance;
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		instance.getRequiredExtensions();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);

		Surface surface;
		surface.create(instance, window);

		physicalDevice.create(instance);

		SwapChainSupportDetails swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);

		ASSERT_NE(swapChainSupportDetails.surfaceCapabilities, vk::SurfaceCapabilitiesKHR());
		ASSERT_FALSE(swapChainSupportDetails.surfaceFormats.empty());
		ASSERT_FALSE(swapChainSupportDetails.presentModes.empty());

		GLFW::Deinit();
    }
}