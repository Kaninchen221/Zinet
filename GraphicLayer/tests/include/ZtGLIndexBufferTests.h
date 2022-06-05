#pragma once

#include "Zinet/GraphicLayer/ZtGLIndexBuffer.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"
#include "Zinet/GraphicLayer/ZtGLBuffer.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class IndexBufferTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		IndexBuffer indexBuffer;

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

			vk::BufferCreateInfo indexBufferCreateInfo = indexBuffer.createCreateInfo(1u);
			indexBuffer.create(device, indexBufferCreateInfo);
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST(IndexBuffer, DerivedFromBuffer)
	{
		static_assert(std::derived_from<IndexBuffer, Buffer>);
	}

	TEST(IndexBuffer, CreateCreateInfo)
	{
		IndexBuffer indexBuffer;
		std::uint64_t expectedSize = 1u;
		vk::BufferCreateInfo indexBufferCreateInfo = indexBuffer.createCreateInfo(expectedSize);

		ASSERT_EQ(indexBufferCreateInfo.size, expectedSize);
		ASSERT_EQ(indexBufferCreateInfo.usage, vk::BufferUsageFlagBits::eIndexBuffer | vk::BufferUsageFlagBits::eTransferDst);
		ASSERT_EQ(indexBufferCreateInfo.sharingMode, vk::SharingMode::eExclusive);
	}

	TEST_F(IndexBufferTests, CreateTest)
	{
		ASSERT_NE(*indexBuffer.getInternal(), *vk::raii::Buffer{ std::nullptr_t{} });
	}

}