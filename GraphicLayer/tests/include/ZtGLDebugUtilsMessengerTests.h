#pragma once

#include "Zinet/GraphicLayer/ZtGLDebugUtilsMessenger.h"

#include "gtest/gtest.h"

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
		const vk::raii::DebugUtilsMessengerEXT& internal = debugUtilsMessenger.getInternal();
	}

	TEST_F(DebugUtilsMessengerTests, Create)
	{
		Context context;
		instance.createInstanceCreateInfo();
		instance.create(context);
		debugUtilsMessenger.create(instance);
	}

}