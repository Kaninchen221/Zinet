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
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = renderer.createDeviceQueueCreateInfo();

		ASSERT_NE(deviceQueueCreateInfo, vk::DeviceQueueCreateInfo());
	}

	TEST_F(RendererTests, CreateDeviceCreateInfo)
	{
		vk::DeviceCreateInfo deviceCreateInfo = renderer.createDeviceCreateInfo();

		ASSERT_NE(deviceCreateInfo, vk::DeviceCreateInfo());
	}

	TEST_F(RendererTests, CreateDevice)
	{
		//PhysicalDevice physicalDevice = renderer.instanceHelper.pickPhysicalDevice();
		renderer.createDeviceQueueCreateInfo();
		renderer.createDeviceCreateInfo();
		vk::raii::Device device = renderer.createDevice();

		ASSERT_NE(*device, *vk::raii::Device(std::nullptr_t()));
	}
	
	TEST_F(RendererTests, CreateQueue)
	{
		PhysicalDevice physicalDevice = renderer.instanceHelper.pickPhysicalDevice();
		renderer.createDeviceQueueCreateInfo();

		uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex();
		vk::raii::Device device = renderer.createDevice();
		vk::raii::Queue queue = renderer.createQueue(device, queueFamilyIndex);

		ASSERT_NE(*queue, *vk::raii::Queue(std::nullptr_t()));
	}
}