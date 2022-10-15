#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class RendererTests : public ::testing::Test
	{
	protected:

		Renderer renderer;

	};

	TEST_F(RendererTests, Initialize)
	{
		renderer.initialize();

		const Instance& instance = renderer.getInstance();
		ASSERT_NE(instance, vk::raii::Instance(std::nullptr_t{}));

		const DebugUtilsMessenger& debugUtilsMessenger = renderer.getDebugUtilsMessenger();
		ASSERT_NE(debugUtilsMessenger, vk::raii::DebugUtilsMessengerEXT(std::nullptr_t{}));

		const Window& window = renderer.getWindow();
		const GLFWwindow* internalWindow = window.getInternal();
		ASSERT_NE(internalWindow, nullptr);

		const Surface& surface = renderer.getSurface();
		ASSERT_NE(surface, nullptr);

		const PhysicalDevice& physicalDevice = renderer.getPhysicalDevice();
		ASSERT_NE(physicalDevice, nullptr);
	}

	TEST_F(RendererTests, GetContext)
	{
		const Context& context = renderer.getContext();
	}

	TEST_F(RendererTests, GetInstance)
	{
		const Instance& instance = renderer.getInstance();
		ASSERT_EQ(instance, vk::raii::Instance(std::nullptr_t{}));
	}

	TEST_F(RendererTests, GetDebugUtilsMessenger)
	{
		const DebugUtilsMessenger& debugUtilsMessenger = renderer.getDebugUtilsMessenger();
		ASSERT_EQ(debugUtilsMessenger, vk::raii::DebugUtilsMessengerEXT(std::nullptr_t{}));
	}

	TEST_F(RendererTests, GetWindow)
	{
		const Window& window = renderer.getWindow();
		const GLFWwindow* internalWindow = window.getInternal();

		ASSERT_EQ(internalWindow, nullptr);
	}

	TEST_F(RendererTests, GetSurface)
	{
		const Surface& surface = renderer.getSurface();
		ASSERT_EQ(surface, nullptr);
	}

	TEST_F(RendererTests, GetPhysicalDevice)
	{
		const PhysicalDevice& physicalDevice = renderer.getPhysicalDevice();
		ASSERT_EQ(physicalDevice, nullptr);
	}

}
