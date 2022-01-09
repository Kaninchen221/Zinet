#pragma once

#include "Zinet/GraphicLayer/ZtGLDebugUtilsMessenger.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class DebugUtilsMessengerTests : public ::testing::Test
	{
	protected:

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
		//TODO: 
		//vk::raii::Context context;
		//vk::raii::Instance instance(context, {});
		//debugUtilsMessenger.createDebugUtilsMessenger(instance);
	}

}