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
			GLFW::InitGLFW();

			window.create();
			instance.createApplicationInfo();
			instance.createInstanceCreateInfo();
			instance.create(context);
			surface.create(instance, window);
			physicalDevice.create(instance);
			device.create(physicalDevice, surface);

			indexBuffer.setSize(1u);
			vk::BufferCreateInfo indexBufferCreateInfo = indexBuffer.createCreateInfo();
			indexBuffer.create(device, indexBufferCreateInfo);
		}

		void TearDown() override
		{
			GLFW::DeinitGLFW();
		}
	};

	TEST(IndexBuffer, DerivedFromBuffer)
	{
		static_assert(std::derived_from<IndexBuffer, Buffer>);
	}

	TEST_F(IndexBufferTests, CreateCreateInfo)
	{
		vk::BufferCreateInfo indexBufferCreateInfo = indexBuffer.createCreateInfo();

		ASSERT_NE(indexBufferCreateInfo.size, 0u);
		ASSERT_EQ(indexBufferCreateInfo.usage, vk::BufferUsageFlagBits::eIndexBuffer | vk::BufferUsageFlagBits::eTransferDst);
		ASSERT_EQ(indexBufferCreateInfo.sharingMode, vk::SharingMode::eExclusive);
	}

	TEST_F(IndexBufferTests, CreateTest)
	{
		ASSERT_NE(*indexBuffer.getInternal(), *vk::raii::Buffer{ std::nullptr_t{} });
	}

}