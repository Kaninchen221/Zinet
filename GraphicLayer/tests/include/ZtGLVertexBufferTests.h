#pragma once

#include "Zinet/GraphicLayer/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "gtest/gtest.h"

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
			vk::BufferCreateInfo bufferCreateInfo = vertexBuffer.createCreateInfo(1u);
			VmaAllocationCreateInfo allocationCreateInfo = vertexBuffer.createVmaAllocationCreateInfo(false);

			vertexBuffer.create(renderer, bufferCreateInfo, allocationCreateInfo);
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

	TEST_F(VertexBufferTests, Create)
	{
		ASSERT_NE(*vertexBuffer.getInternal(), *vk::raii::Buffer{ std::nullptr_t{} });
	}

}