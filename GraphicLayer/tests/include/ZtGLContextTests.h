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
		const vk::Instance& instance = context.getInstance();

		ASSERT_NE(instance, vk::Instance());
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
		const VkDebugUtilsMessengerEXT& debugMessenger = context.getDebugMessenger();
	}

	TEST_F(GLContextTests, CreateDebugUtilsMessengerCreateInfo)
	{
		context.createDebugUtilsMessengerCreateInfo();
		const VkDebugUtilsMessengerCreateInfoEXT& debugUtilsMessengerCreateInfo = context.getDebugUtilsMessengerCreateInfo();
	}

	TEST_F(GLContextTests, InitVulkan)
	{
		VkResult result = context.initVulkan();
		ASSERT_EQ(result, VkResult::VK_SUCCESS);
	}

	TEST_F(GLContextTests, CreatePhysicalDevicesTest)
	{
		context.initGLFW();
		context.createInstance();
		context.createPhysicalDevices();
		const std::vector<vk::PhysicalDevice>& physicalDevices = context.getPhysicalDevices();

		ASSERT_FALSE(physicalDevices.empty());
	}
}