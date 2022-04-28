#pragma once

#include "Zinet/GraphicLayer/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class VertexBufferTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		VertexBuffer vertexBuffer;

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
		}

		void TearDown() override
		{
			GLFW::DeinitGLFW();
		}
	};

	TEST(VertexBuffer, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<VertexBuffer, VulkanObject<vk::raii::Buffer>>);
	}

	TEST(VertexBuffer, GetVertices)
	{
		VertexBuffer vertexBuffer;
		const std::vector<Vertex>& vertices = vertexBuffer.getVertices();

		ASSERT_EQ(vertices.size(), 0);
	}

	TEST(VertexBuffer, SetVertices)
	{
		VertexBuffer vertexBuffer;
		std::vector<Vertex> expectedVertices{ {} };
		vertexBuffer.setVertices(expectedVertices);
		const std::vector<Vertex>& actualVertices = vertexBuffer.getVertices();

		ASSERT_EQ(expectedVertices, actualVertices);
	}

	TEST(VertexBuffer, CreateVertexBufferCreateInfo)
	{
		VertexBuffer vertexBuffer;
		vk::BufferCreateInfo vertexBufferCreateInfo = vertexBuffer.createVertexBufferCreateInfo();

		ASSERT_NE(vertexBufferCreateInfo, vk::BufferCreateInfo{});
	}

	TEST_F(VertexBufferTests, Create)
	{
		ASSERT_NE(*vertexBuffer.getInternal(), *vk::raii::Buffer{ std::nullptr_t{} });
	}

	TEST_F(VertexBufferTests, GetMemoryRequirements)
	{
		vk::MemoryRequirements memoryRequirements = vertexBuffer->getMemoryRequirements();
	}

	TEST_F(VertexBufferTests, PhysicalDeviceMemoryProperties)
	{
		vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
		vk::MemoryPropertyFlags memoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
		uint32_t memoryType = vertexBuffer.findSuitableMemoryType(physicalDeviceMemoryProperties, memoryPropertyFlags);

		ASSERT_NE(memoryType, UINT32_MAX);
	}

	TEST_F(VertexBufferTests, CreateMemoryAllocateInfo)
	{
		vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
		vk::MemoryPropertyFlags memoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
		vk::MemoryAllocateInfo memoryAllocateInfo = vertexBuffer.createMemoryAllocateInfo(physicalDeviceMemoryProperties, memoryPropertyFlags);

		ASSERT_NE(memoryAllocateInfo, vk::MemoryAllocateInfo{});
	}

	TEST_F(VertexBufferTests, BindMemory)
	{
		vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
		vk::MemoryPropertyFlags memoryPropertyFlags = {};
		vk::MemoryAllocateInfo memoryAllocateInfo = vertexBuffer.createMemoryAllocateInfo(physicalDeviceMemoryProperties, memoryPropertyFlags);
		DeviceMemory deviceMemory;
		deviceMemory.create(device, memoryAllocateInfo);

		vertexBuffer.bindMemory(deviceMemory);
	}
}