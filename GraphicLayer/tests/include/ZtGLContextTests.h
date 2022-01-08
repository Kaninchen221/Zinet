#pragma once

#include "Zinet/GraphicLayer/ZtGLContext.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class GLContextTests : public ::testing::Test
	{
	protected:

		Context context;

	};

	TEST_F(GLContextTests, InitGLFWTest)
	{
		bool result = context.initGLFW();

		ASSERT_TRUE(result);
	}

	TEST_F(GLContextTests, DeinitGLFWTest)
	{
		context.initGLFW();
		context.deinitGLFW();
	}

	TEST_F(GLContextTests, ApplicationInfoTest)
	{
		context.initGLFW();
		context.createApplicationInfo();
		const vk::ApplicationInfo& applicationInfo = context.getApplicationInfo();

		ASSERT_NE(applicationInfo, vk::ApplicationInfo());
	}

	TEST_F(GLContextTests, InstanceCreateInfoTest)
	{
		context.initGLFW();
		context.createInstanceCreateInfo();
		const vk::InstanceCreateInfo& instanceCreateInfo = context.getInstanceCreateInfo();

		ASSERT_NE(instanceCreateInfo, vk::InstanceCreateInfo());
	}

	TEST_F(GLContextTests, CreateInstanceTest)
	{
		context.initGLFW();
		context.createInstance();
		const vk::raii::Instance& instance = context.getInstance();

		ASSERT_NE(*instance, vk::Instance());
	}

	TEST_F(GLContextTests, GetValidationLayersTest)
	{
		const std::vector<const char*>& validationLayers = context.getValidationLayers();

		ASSERT_FALSE(validationLayers.empty());
	}

	TEST_F(GLContextTests, CheckValidationLayersSupportTest)
	{
		bool result = context.checkValidationLayerSupport();

		ASSERT_TRUE(result);
	}

	TEST_F(GLContextTests, GetRequiredExtensionsTest)
	{
		std::vector<const char*> requiredExtensions = context.getRequiredExtensions();

		ASSERT_FALSE(requiredExtensions.empty());
	}

	TEST_F(GLContextTests, DebugCallbackTest)
	{
		VkDebugUtilsMessengerCallbackDataEXT callbackDataExt;

		bool result = Context::DebugCallback(
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT,
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT,
			&callbackDataExt,
			nullptr
		);

		ASSERT_TRUE(result);
	}

	TEST_F(GLContextTests, GetDebugDebugMessengerTest)
	{
		const vk::raii::DebugUtilsMessengerEXT& debugMessenger = context.getDebugMessenger();
	}

	TEST_F(GLContextTests, CreateDebugUtilsMessenger)
	{
		context.initGLFW();
		context.createApplicationInfo();
		context.createInstanceCreateInfo();
		context.createInstance();
		context.createDebugUtilsMessenger();
	}

	TEST_F(GLContextTests, EnumeratePhysicalDevices)
	{
		context.initGLFW();
		context.createInstance();
		vk::raii::PhysicalDevices physicalDevices = context.enumeratePhysicalDevices();
	}

	TEST_F(GLContextTests, PickPhysicalDevice)
	{
		context.initGLFW();
		context.createInstance();
		vk::raii::PhysicalDevice physicalDevice = context.pickPhysicalDevice();

		ASSERT_NE(*physicalDevice, *vk::raii::PhysicalDevice(std::nullptr_t()));

		// TODO: pickPhysicalDevice should pick gpu with needed extensions etc.
	}

	TEST_F(GLContextTests, PickQueueFamilyIndex)
	{
		context.initGLFW();
		context.createInstance();
		vk::raii::PhysicalDevice physicalDevice = context.pickPhysicalDevice();
		uint32_t queueFamilyIndex = context.pickQueueFamilyIndex(physicalDevice);
		uint32_t notExpectedIndex = std::numeric_limits<uint32_t>::max();

		ASSERT_NE(queueFamilyIndex, notExpectedIndex);
	}

	TEST_F(GLContextTests, CreateQueueCreateInfo)
	{
		context.initGLFW();
		context.createInstance();
		vk::raii::PhysicalDevice physicalDevice = context.pickPhysicalDevice();
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = context.createDeviceQueueCreateInfo(physicalDevice);

		ASSERT_NE(deviceQueueCreateInfo, vk::DeviceQueueCreateInfo());
	}

	TEST_F(GLContextTests, CreatePhysicalDeviceFeatures)
	{
		vk::PhysicalDeviceFeatures physicalDeviceFeatures = context.createPhysicalDeviceFeatures();
	}

	TEST_F(GLContextTests, CreateDeviceCreateInfo)
	{
		vk::DeviceCreateInfo deviceCreateInfo = context.createDeviceCreateInfo();

		ASSERT_NE(deviceCreateInfo, vk::DeviceCreateInfo());
	}

	TEST_F(GLContextTests, CreateDevice)
	{
		context.createInstance();
		vk::raii::PhysicalDevice physicalDevice = context.pickPhysicalDevice();
		vk::raii::Device device = context.createDevice(physicalDevice);

		ASSERT_NE(*device, *vk::raii::Device(std::nullptr_t()));
	}
	
	TEST_F(GLContextTests, CreateQueue)
	{
		context.createInstance();
		vk::raii::PhysicalDevice physicalDevice = context.pickPhysicalDevice();
		context.createDeviceQueueCreateInfo(physicalDevice);
		uint32_t queueFamilyIndex = context.pickQueueFamilyIndex(physicalDevice);
		vk::raii::Device device = context.createDevice(physicalDevice);
		vk::raii::Queue queue = context.createQueue(device, queueFamilyIndex);

		ASSERT_NE(*queue, *vk::raii::Queue(std::nullptr_t()));
	}
}