#pragma once

#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLUniformBuffer.h"
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
		// TODO Use new way to create buffers
		//VertexBuffer vertexBuffer;
		//vk::BufferCreateInfo vertexBufferCreateInfo = vertexBuffer.createCreateInfo(1u);
		//vertexBuffer.create(device, vertexBufferCreateInfo);
		//
		//vk::MemoryRequirements vertexBufferMemoryRequirements = vertexBuffer->getMemoryRequirements();
		//vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
		//vk::MemoryPropertyFlags memoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
		//vk::MemoryAllocateInfo memoryAllocateInfo = vertexBuffer.createMemoryAllocateInfo(
		//															vertexBufferMemoryRequirements, 
		//															physicalDeviceMemoryProperties, 
		//															memoryPropertyFlags);
		//deviceMemory.create(device, memoryAllocateInfo);
		//
		//ASSERT_NE(*deviceMemory.getInternal(), *vk::raii::DeviceMemory{ std::nullptr_t{} });
	}

	TEST_F(DeviceMemoryTests, FillWithCArray)
	{
		// TODO Fix this after integrating VMA
		//char array[4];
		//std::size_t size = sizeof(array);
		//
		//UniformBuffer uniformBuffer;
		//vk::BufferCreateInfo uniformBufferCreateInfo = uniformBuffer.createCreateInfo(size);
		//uniformBuffer.create(device, uniformBufferCreateInfo);
		//
		//vk::MemoryRequirements uniformBufferMemoryRequirements = uniformBuffer->getMemoryRequirements();
		//vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
		//vk::MemoryPropertyFlags memoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
		//vk::MemoryAllocateInfo memoryAllocateInfo = uniformBuffer.createMemoryAllocateInfo(
		//															uniformBufferMemoryRequirements, 
		//															physicalDeviceMemoryProperties, 
		//															memoryPropertyFlags);
		//deviceMemory.create(device, memoryAllocateInfo);
		//
		//deviceMemory.fillWithArray(array, size);
		//std::pair<void*, std::uint64_t> data = deviceMemory.getData(size);
		//
		//ASSERT_EQ(data.second, size);
		//
		//int result = std::memcmp(data.first, array, size);
		//
		//ASSERT_EQ(result, 0);
		//
		//std::free(data.first);
	}
}
