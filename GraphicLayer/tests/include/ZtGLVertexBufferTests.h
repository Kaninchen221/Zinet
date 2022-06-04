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
#include "Zinet/GraphicLayer/ZtGLBuffer.h"

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

			vk::BufferCreateInfo vertexBufferCreateInfo = vertexBuffer.createCreateInfo(1u);
			vertexBuffer.create(device, vertexBufferCreateInfo);
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST(VertexBuffer, DerivedFromBuffer)
	{
		static_assert(std::derived_from<VertexBuffer, Buffer>);
	}

	TEST(VertexBuffer, CreateCreateInfo)
	{
		VertexBuffer vertexBuffer;
		std::uint64_t expectedSize = 1u;
		vk::BufferCreateInfo vertexBufferCreateInfo = vertexBuffer.createCreateInfo(expectedSize);

		ASSERT_EQ(vertexBufferCreateInfo.usage, vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eTransferDst);
		ASSERT_EQ(vertexBufferCreateInfo.size, expectedSize);
		ASSERT_EQ(vertexBufferCreateInfo.sharingMode, vk::SharingMode::eExclusive);
	}

	TEST_F(VertexBufferTests, CreateTest)
	{
		ASSERT_NE(*vertexBuffer.getInternal(), *vk::raii::Buffer{ std::nullptr_t{} });
	}

}