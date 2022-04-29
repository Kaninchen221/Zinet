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
			GLFW::InitGLFW();

			window.create();
			instance.createApplicationInfo();
			instance.createInstanceCreateInfo();
			instance.create(context);
			surface.create(instance, window);
			physicalDevice.create(instance);
			device.create(physicalDevice, surface);

			vertexBuffer.setVertices({ {} });
			vk::BufferCreateInfo vertexBufferCreateInfo = vertexBuffer.createCreateInfo();
			vertexBuffer.create(device, vertexBufferCreateInfo);
		}

		void TearDown() override
		{
			GLFW::DeinitGLFW();
		}
	};

	TEST(VertexBuffer, DerivedFromBuffer)
	{
		static_assert(std::derived_from<VertexBuffer, Buffer>);
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
		vk::BufferCreateInfo vertexBufferCreateInfo = vertexBuffer.createCreateInfo();

		ASSERT_EQ(vertexBufferCreateInfo.usage, vk::BufferUsageFlagBits::eVertexBuffer);
	}

}