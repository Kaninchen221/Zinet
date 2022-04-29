#pragma once

#include "gtest/gtest.h"

#include "Zinet/GraphicLayer/ZtGLBuffer.h"

namespace zt::gl::tests
{

	class BufferTests : public ::testing::Test
	{
	protected:

		struct BufferTest : public Buffer
		{

			vk::BufferCreateInfo createCreateInfo() const override 
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
		BufferTest bufferTest;

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

			vk::BufferCreateInfo createInfo = bufferTest.createCreateInfo();
			bufferTest.create(device, createInfo);
		}

		void TearDown() override
		{
			GLFW::DeinitGLFW();
		}
	};

	TEST(Buffer, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<Buffer, VulkanObject<vk::raii::Buffer>>);
	}

	TEST(Buffer, CanNotBeConstructed)
	{
		static_assert(std::is_abstract<Buffer>::value);
	}

	TEST_F(BufferTests, Create)
	{
		ASSERT_NE(*bufferTest.getInternal(), *vk::raii::Buffer{ std::nullptr_t{} });
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