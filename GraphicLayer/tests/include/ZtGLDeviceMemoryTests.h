#pragma once

#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"

#include "gtest/gtest.h"

#include <vector>

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
		std::vector<Vertex> vertices{ {}, {} };

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

			vertexBuffer.setSize(sizeof(Vertex) * vertices.size());
			vk::BufferCreateInfo vertexBufferCreateInfo = vertexBuffer.createCreateInfo();
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
		deviceMemory.fillWithData<std::vector<Vertex>>(vertices);
		std::size_t expectedSize = sizeof(Vertex) * vertices.size();
		std::pair<void*, std::uint64_t> data = deviceMemory.getData(expectedSize);

		ASSERT_EQ(data.second, expectedSize);

		int result = std::memcmp(data.first, vertices.data(), expectedSize);

		ASSERT_EQ(result, 0);

		std::free(data.first);
	}
}
