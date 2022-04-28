#pragma once

#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class DeviceMemoryTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		VertexBuffer vertexBuffer;
		DeviceMemory deviceMemory;

		void SetUp() override
		{
			GLFW::InitGLFW();

			window.create();
			instance.createApplicationInfo();
			instance.createInstanceCreateInfo();
			instance.create(context);
			surface.create(instance, window);
			physicalDevice.create(instance);
			device.create(physicalDevice, surface);

			vertexBuffer.setVertices({ {} });
			vk::BufferCreateInfo vertexBufferCreateInfo = vertexBuffer.createVertexBufferCreateInfo();
			vertexBuffer.create(device, vertexBufferCreateInfo);

			vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
			vk::MemoryPropertyFlags memoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
			vk::MemoryAllocateInfo memoryAllocateInfo = vertexBuffer.createMemoryAllocateInfo(physicalDeviceMemoryProperties, memoryPropertyFlags);
			deviceMemory.create(device, memoryAllocateInfo);
		}

		void TearDown() override
		{
			GLFW::DeinitGLFW();
		}
	};

	TEST(DeviceMemory, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<DeviceMemory, VulkanObject<vk::raii::DeviceMemory>>);
	}

	TEST_F(DeviceMemoryTests, Create)
	{
		ASSERT_NE(*deviceMemory.getInternal(), *vk::raii::DeviceMemory{ std::nullptr_t{} });
	}

	TEST_F(DeviceMemoryTests, FillWithData)
	{
		deviceMemory.fillWithVertexBuffer(vertexBuffer);
	}
}
