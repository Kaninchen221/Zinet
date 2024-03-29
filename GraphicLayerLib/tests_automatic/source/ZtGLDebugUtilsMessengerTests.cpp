#pragma once

#include "Zinet/GraphicLayer/ZtGLDebugUtilsMessenger.hpp"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class DebugUtilsMessengerTests : public ::testing::Test
	{
	protected:

		Instance instance;
		DebugUtilsMessenger debugUtilsMessenger;

	};

	TEST(DebugUtilsMessenger, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<DebugUtilsMessenger, VulkanObject<vk::raii::DebugUtilsMessengerEXT>>);
	}

	TEST_F(DebugUtilsMessengerTests, DebugCallbackTest)
	{
		VkDebugUtilsMessengerCallbackDataEXT callbackDataExt;

		bool result = DebugUtilsMessenger::DebugCallback(
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT,
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT,
			&callbackDataExt,
			nullptr
		);

		ASSERT_TRUE(result);
	}

	TEST_F(DebugUtilsMessengerTests, GetDebugDebugMessengerTest)
	{
		[[maybe_unused]] const vk::raii::DebugUtilsMessengerEXT& internal = debugUtilsMessenger.getInternal();
	}

	TEST_F(DebugUtilsMessengerTests, Create)
	{
		Context context;
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		instance.populateRequiredExtensions();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);
		if (!instance.isValid())
			FAIL() << "Failed to create instance";

		debugUtilsMessenger.create(instance);
	}

}