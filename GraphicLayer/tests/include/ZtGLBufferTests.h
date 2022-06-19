#pragma once

#include "gtest/gtest.h"

#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"
#include "Zinet/GraphicLayer/ZtGLBuffer.h"
#include "Zinet/GraphicLayer/ZtGLStagingBuffer.h"

namespace zt::gl::tests
{

	class BufferTests : public ::testing::Test
	{
	protected:

		struct BufferTest : public Buffer
		{

			vk::BufferCreateInfo createCreateInfo(std::uint64_t size) const override
			{ 
				vk::BufferCreateInfo createInfo;
				createInfo.usage = vk::BufferUsageFlagBits::eTransferSrc;
				createInfo.size = 1;
				return createInfo;
			}

		};

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		std::uint64_t expectedSize = 1u;
		vk::BufferCreateInfo createInfo;
		BufferTest bufferTest;

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

			createInfo = bufferTest.createCreateInfo(expectedSize);
			bufferTest.create(device, createInfo);
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST(Buffer, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<Buffer, VulkanObject<vk::raii::Buffer>>);
	}

	TEST(Buffer, IsAbstract)
	{
		static_assert(std::is_abstract<Buffer>::value);
	}

	TEST(Buffer, GetSize)
	{
		StagingBuffer stagingBuffer;
		std::uint64_t actualSize = stagingBuffer.getSize();

		ASSERT_EQ(actualSize, 0u);
	}

	TEST_F(BufferTests, Create)
	{
		ASSERT_NE(*bufferTest.getInternal(), *vk::raii::Buffer{ std::nullptr_t{} });

		std::uint64_t actualSize = bufferTest.getSize();
		ASSERT_EQ(actualSize, expectedSize);
	}

	TEST_F(BufferTests, GetMemoryRequirements)
	{
		vk::MemoryRequirements memoryRequirements = bufferTest->getMemoryRequirements();
	}

	TEST_F(BufferTests, FindSuitableMemoryType)
	{
		vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
		vk::MemoryPropertyFlags memoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
		uint32_t memoryType = bufferTest.findSuitableMemoryType(physicalDeviceMemoryProperties, memoryPropertyFlags);
		// TODO Add MemoryRequirements

		ASSERT_NE(memoryType, UINT32_MAX);
	}

	TEST_F(BufferTests, CreateMemoryAllocateInfo)
	{
		vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
		vk::MemoryPropertyFlags memoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
		vk::MemoryAllocateInfo memoryAllocateInfo = bufferTest.createMemoryAllocateInfo(physicalDeviceMemoryProperties, memoryPropertyFlags);

		ASSERT_NE(memoryAllocateInfo, vk::MemoryAllocateInfo{});
	}

	TEST_F(BufferTests, BindMemory)
	{
		vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
		vk::MemoryPropertyFlags memoryPropertyFlags = {};
		vk::MemoryAllocateInfo memoryAllocateInfo = bufferTest.createMemoryAllocateInfo(physicalDeviceMemoryProperties, memoryPropertyFlags);
		DeviceMemory deviceMemory;
		deviceMemory.create(device, memoryAllocateInfo);

		bufferTest.bindMemory(deviceMemory);
	}

}