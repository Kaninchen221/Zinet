#pragma once

#include "Zinet/GraphicLayer/Buffers/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class VertexBufferTests : public ::testing::Test
	{
	protected:

		Renderer renderer;
		VertexBuffer vertexBuffer;

		void SetUp() override
		{
			renderer.initialize();

			BufferCreateInfo vertexBufferCreateInfo{ .device = renderer.getDevice(), .vma = renderer.getVma() };
			vertexBufferCreateInfo.vkBufferCreateInfo = vertexBuffer.createCreateInfo(1u);
			vertexBufferCreateInfo.allocationCreateInfo = vertexBuffer.createVmaAllocationCreateInfo(false);

			vertexBuffer.create(vertexBufferCreateInfo);
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

		ASSERT_EQ(vertexBufferCreateInfo.usage, vk::BufferUsageFlagBits::eVertexBuffer);
		ASSERT_EQ(vertexBufferCreateInfo.size, expectedSize);
		ASSERT_EQ(vertexBufferCreateInfo.sharingMode, vk::SharingMode::eExclusive);
	}

	TEST_F(VertexBufferTests, Create)
	{
		ASSERT_NE(*vertexBuffer.getInternal(), *vk::raii::Buffer{ std::nullptr_t{} });
	}

}