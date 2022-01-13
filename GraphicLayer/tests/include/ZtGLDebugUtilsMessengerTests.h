#pragma once

#include "Zinet/GraphicLayer/ZtGLDebugUtilsMessenger.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class DebugUtilsMessengerTests : public ::testing::Test
	{
	protected:

		// Declare instance here then it will be destroyed after debugUtilsMessenger
		Instance instance;

		DebugUtilsMessenger debugUtilsMessenger;

	};

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
		const vk::raii::DebugUtilsMessengerEXT& debugMessenger = debugUtilsMessenger.getDebugMessenger();
	}

	TEST_F(DebugUtilsMessengerTests, CreateDebugUtilsMessenger)
	{
		Context context;
		instance.createInstanceCreateInfo();
		instance.createInstance(context);
		debugUtilsMessenger.createDebugUtilsMessenger(instance);
	}

}