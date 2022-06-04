#pragma once

#include "Zinet/GraphicLayer/ZtGLUniformBuffer.h"
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

	class UniformBufferTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		UniformBuffer uniformBuffer;

		void SetUp() override
		{
			GLFW::Init();

			window.create();
			instance.createApplicationInfo();
			instance.createInstanceCreateInfo();
			instance.create(context);
			surface.create(instance, window);
			physicalDevice.create(instance);

			vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
			vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice, surface, deviceQueueCreateInfo);
			device.create(physicalDevice, deviceCreateInfo);

			vk::BufferCreateInfo uniformBufferCreateInfo = uniformBuffer.createCreateInfo(1u);
			uniformBuffer.create(device, uniformBufferCreateInfo);
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST(UniformBuffer, DerivedFromBuffer)
	{
		static_assert(std::derived_from<UniformBuffer, Buffer>);
	}

	TEST(UniformBuffer, CreateCreateInfo)
	{
		UniformBuffer uniformBuffer;
		std::uint64_t expectedSize = 1u;
		vk::BufferCreateInfo uniformBufferCreateInfo = uniformBuffer.createCreateInfo(expectedSize);

		ASSERT_EQ(uniformBufferCreateInfo.usage, vk::BufferUsageFlagBits::eUniformBuffer);
		ASSERT_EQ(uniformBufferCreateInfo.size, expectedSize);
		ASSERT_EQ(uniformBufferCreateInfo.sharingMode, vk::SharingMode::eExclusive);
	}

	TEST_F(UniformBufferTests, CreateDescriptorBufferInfo)
	{
		vk::DescriptorBufferInfo info = uniformBuffer.createDescriptorBufferInfo();

		ASSERT_EQ(info.buffer, *uniformBuffer.getInternal());
		ASSERT_EQ(info.offset, 0);
		ASSERT_EQ(info.range, uniformBuffer.getSize());
	}

	TEST_F(UniformBufferTests, CreateTest)
	{
		ASSERT_NE(*uniformBuffer.getInternal(), *vk::raii::Buffer{ std::nullptr_t{} });
	}

}