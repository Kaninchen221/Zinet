#pragma once

#include "Zinet/GraphicLayer/Buffers/ZtGLVertexBuffer.hpp"
#include "Zinet/GraphicLayer/ZtGLVertex.hpp"
#include "Zinet/GraphicLayer/ZtGLRenderer.hpp"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class VertexBufferTests : public ::testing::Test
	{
	protected:

		Renderer renderer;
		VertexBuffer vertexBuffer;

		static_assert(std::derived_from<VertexBuffer, Buffer>);

		void SetUp() override
		{
			renderer.initialize();
			RendererContext& rendererContext = renderer.getRendererContext();

			Buffer::CreateInfo vertexBufferCreateInfo{ .device = rendererContext.getDevice(), .vma = rendererContext.getVma() };
			vertexBufferCreateInfo.vkBufferCreateInfo = vertexBuffer.createCreateInfo(1u);
			vertexBufferCreateInfo.allocationCreateInfo = vertexBuffer.createVmaAllocationCreateInfo(false, true);

			vertexBuffer.create(vertexBufferCreateInfo);
		}
	};

	TEST(VertexBuffer, CreateCreateInfo)
	{
		VertexBuffer vertexBuffer;
		std::uint64_t expectedSize = 1u;
		vk::BufferCreateInfo vertexBufferCreateInfo = vertexBuffer.createCreateInfo(expectedSize);

		ASSERT_TRUE(vertexBufferCreateInfo.usage & vk::BufferUsageFlagBits::eVertexBuffer);
		ASSERT_TRUE(vertexBufferCreateInfo.usage & vk::BufferUsageFlagBits::eTransferDst);
		ASSERT_EQ(vertexBufferCreateInfo.size, expectedSize);
		ASSERT_EQ(vertexBufferCreateInfo.sharingMode, vk::SharingMode::eExclusive);
	}

	TEST_F(VertexBufferTests, Create)
	{
		ASSERT_NE(*vertexBuffer.getInternal(), *vk::raii::Buffer{ std::nullptr_t{} });
	}

}