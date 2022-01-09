#pragma once

#include "Zinet/GraphicLayer/ZtGLDebugUtilsMessenger.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class InstanceTests : public ::testing::Test
	{
	protected:

		Instance instance;

	};

	TEST_F(InstanceTests, ApplicationInfoTest)
	{
		instance.createApplicationInfo();
		const vk::ApplicationInfo& applicationInfo = instance.getApplicationInfo();

		ASSERT_NE(applicationInfo, vk::ApplicationInfo());
	}

	TEST_F(InstanceTests, InstanceCreateInfoTest)
	{
		instance.createInstanceCreateInfo();
		const vk::InstanceCreateInfo& instanceCreateInfo = instance.getInstanceCreateInfo();

		ASSERT_NE(instanceCreateInfo, vk::InstanceCreateInfo());
	}

	TEST_F(InstanceTests, CreateInstanceTest)
	{
		vk::raii::Context context;
		instance.createInstance(context);
		const vk::raii::Instance& vkInstance = instance.getInstance();

		ASSERT_NE(*vkInstance, vk::Instance());
	}

	TEST_F(InstanceTests, GetValidationLayersTest)
	{
		const std::vector<const char*>& validationLayers = instance.getValidationLayers();

		ASSERT_FALSE(validationLayers.empty());
	}

	TEST_F(InstanceTests, CheckValidationLayersSupportTest)
	{
		bool result = instance.checkValidationLayerSupport();

		ASSERT_TRUE(result);
	}

	TEST_F(InstanceTests, GetRequiredExtensionsTest)
	{
		std::vector<const char*> requiredExtensions = instance.getRequiredExtensions();

		ASSERT_FALSE(requiredExtensions.empty());
	}

	TEST_F(InstanceTests, EnumeratePhysicalDevices)
	{
		vk::raii::Context context;
		instance.createInstance(context);
		vk::raii::PhysicalDevices physicalDevices = instance.enumeratePhysicalDevices();
	}

	TEST_F(InstanceTests, PickPhysicalDevice)
	{
		vk::raii::Context context;
		instance.createInstance(context);
		vk::raii::PhysicalDevice physicalDevice = instance.pickPhysicalDevice();

		ASSERT_NE(*physicalDevice, *vk::raii::PhysicalDevice(std::nullptr_t()));
	}
}