#pragma once

#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/ZtGLUniformBuffer.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"

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
		DeviceMemory deviceMemory;

		void SetUp() override
		{
			GLFW::Init();

			window.create();
			vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
			instance.getRequiredExtensions();
			vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
			instance.create(context, instanceCreateInfo);
			surface.create(instance, window);
			physicalDevice.create(instance);

			vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
			vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice, surface, deviceQueueCreateInfo);
			device.create(physicalDevice, deviceCreateInfo);
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST(DeviceMemory, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<DeviceMemory, VulkanObject<vk::raii::DeviceMemory>>);
	}

	TEST_F(DeviceMemoryTests, Create)
	{
		VertexBuffer vertexBuffer;
		vk::BufferCreateInfo vertexBufferCreateInfo = vertexBuffer.createCreateInfo(1u);
		vertexBuffer.create(device, vertexBufferCreateInfo);

		vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
		vk::MemoryPropertyFlags memoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
		vk::MemoryAllocateInfo memoryAllocateInfo = vertexBuffer.createMemoryAllocateInfo(physicalDeviceMemoryProperties, memoryPropertyFlags);
		deviceMemory.create(device, memoryAllocateInfo);

		ASSERT_NE(*deviceMemory.getInternal(), *vk::raii::DeviceMemory{ std::nullptr_t{} });
	}

	TEST_F(DeviceMemoryTests, FillWithDataContainer)
	{
		VertexBuffer vertexBuffer;
		std::vector<Vertex> vertices{ {}, {} };
		vk::BufferCreateInfo vertexBufferCreateInfo = vertexBuffer.createCreateInfo(sizeof(Vertex) * vertices.size());
		vertexBuffer.create(device, vertexBufferCreateInfo);

		vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
		vk::MemoryPropertyFlags memoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
		vk::MemoryAllocateInfo memoryAllocateInfo = vertexBuffer.createMemoryAllocateInfo(physicalDeviceMemoryProperties, memoryPropertyFlags);
		deviceMemory.create(device, memoryAllocateInfo);

		deviceMemory.fillWithSTDContainer<std::vector<Vertex>>(vertices);
		std::size_t expectedSize = sizeof(Vertex) * vertices.size();
		std::pair<void*, std::uint64_t> data = deviceMemory.getData(expectedSize);

		ASSERT_EQ(data.second, expectedSize);

		int result = std::memcmp(data.first, vertices.data(), expectedSize);

		ASSERT_EQ(result, 0);

		std::free(data.first);
	}

	TEST_F(DeviceMemoryTests, FillWithObject)
	{
		struct MVPFake
		{
			int i = 34;
			float f = 456.342f;
		};
		MVPFake object;

		UniformBuffer uniformBuffer;
		vk::BufferCreateInfo uniformBufferCreateInfo = uniformBuffer.createCreateInfo(sizeof(MVPFake));
		uniformBuffer.create(device, uniformBufferCreateInfo);

		vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
		vk::MemoryPropertyFlags memoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
		vk::MemoryAllocateInfo memoryAllocateInfo = uniformBuffer.createMemoryAllocateInfo(physicalDeviceMemoryProperties, memoryPropertyFlags);
		deviceMemory.create(device, memoryAllocateInfo);

		deviceMemory.fillWithObject<MVPFake>(object);
		std::size_t expectedSize = sizeof(MVPFake);
		std::pair<void*, std::uint64_t> data = deviceMemory.getData(expectedSize);
		
		ASSERT_EQ(data.second, expectedSize);
		
		int result = std::memcmp(data.first, &object, expectedSize);
		
		ASSERT_EQ(result, 0);
		
		std::free(data.first);
	}

	TEST_F(DeviceMemoryTests, FillWithCArray)
	{
		char array[4];
		std::size_t size = sizeof(array);

		UniformBuffer uniformBuffer;
		vk::BufferCreateInfo uniformBufferCreateInfo = uniformBuffer.createCreateInfo(size);
		uniformBuffer.create(device, uniformBufferCreateInfo);

		vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
		vk::MemoryPropertyFlags memoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
		vk::MemoryAllocateInfo memoryAllocateInfo = uniformBuffer.createMemoryAllocateInfo(physicalDeviceMemoryProperties, memoryPropertyFlags);
		deviceMemory.create(device, memoryAllocateInfo);
		
		deviceMemory.fillWithArray(array, size);
		std::pair<void*, std::uint64_t> data = deviceMemory.getData(size);
		
		ASSERT_EQ(data.second, size);
		
		int result = std::memcmp(data.first, array, size);
		
		ASSERT_EQ(result, 0);
		
		std::free(data.first);
	}
}
