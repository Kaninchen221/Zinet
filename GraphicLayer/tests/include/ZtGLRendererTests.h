#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLrenderer.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class RendererTests : public ::testing::Test
	{
	protected:

		Renderer renderer;

	};

	TEST_F(RendererTests, CreateQueueCreateInfo)
	{
		vk::raii::PhysicalDevice physicalDevice = renderer.instanceHelper.pickPhysicalDevice();
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = renderer.createDeviceQueueCreateInfo(physicalDevice);

		ASSERT_NE(deviceQueueCreateInfo, vk::DeviceQueueCreateInfo());
	}

	TEST_F(RendererTests, CreateDeviceCreateInfo)
	{
		vk::DeviceCreateInfo deviceCreateInfo = renderer.createDeviceCreateInfo();

		ASSERT_NE(deviceCreateInfo, vk::DeviceCreateInfo());
	}

	TEST_F(RendererTests, CreateDevice)
	{
		vk::raii::PhysicalDevice physicalDevice = renderer.instanceHelper.pickPhysicalDevice();
		renderer.createDeviceQueueCreateInfo(physicalDevice);
		renderer.createDeviceCreateInfo();
		vk::raii::Device device = renderer.createDevice(physicalDevice);

		ASSERT_NE(*device, *vk::raii::Device(std::nullptr_t()));
	}
	
	TEST_F(RendererTests, CreateQueue)
	{
		vk::raii::PhysicalDevice physicalDevice = renderer.instanceHelper.pickPhysicalDevice();
		renderer.createDeviceQueueCreateInfo(physicalDevice);

		PhysicalDevice physicalDeviceHelper;
		uint32_t queueFamilyIndex = physicalDeviceHelper.pickQueueFamilyIndex(physicalDevice);
		vk::raii::Device device = renderer.createDevice(physicalDevice);
		vk::raii::Queue queue = renderer.createQueue(device, queueFamilyIndex);

		ASSERT_NE(*queue, *vk::raii::Queue(std::nullptr_t()));
	}
}