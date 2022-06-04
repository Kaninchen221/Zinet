#pragma once

#include "Zinet/GraphicLayer/ZtGLStagingBuffer.h"
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

	class StagingBufferTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		StagingBuffer stagingBuffer;

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

			vk::BufferCreateInfo createInfo = stagingBuffer.createCreateInfo(8u);
			stagingBuffer.create(device, createInfo);
		}

		void TearDown() override
		{
			GLFW::DeinitGLFW();
		}
	};

	TEST(StagingBuffer, DerivedFromBuffer)
	{
		static_assert(std::derived_from<VertexBuffer, Buffer>);
	}

	TEST(StagingBuffer, CreateCreateInfo)
	{
		StagingBuffer stagingBuffer;
		std::uint64_t expectedSize = 60u;
		vk::BufferCreateInfo stagingBufferCreateInfo = stagingBuffer.createCreateInfo(expectedSize);

		ASSERT_EQ(stagingBufferCreateInfo.usage, vk::BufferUsageFlagBits::eTransferSrc);
		ASSERT_EQ(stagingBufferCreateInfo.sharingMode, vk::SharingMode::eExclusive);
		ASSERT_EQ(stagingBufferCreateInfo.size, expectedSize);
	}

	TEST_F(StagingBufferTests, Create)
	{
		ASSERT_NE(*stagingBuffer.getInternal(), *vk::raii::Buffer{ std::nullptr_t{} });
	}
}