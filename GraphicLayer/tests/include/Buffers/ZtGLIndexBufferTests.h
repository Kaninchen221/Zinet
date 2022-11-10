#pragma once

#include "Zinet/GraphicLayer/Buffers/ZtGLIndexBuffer.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class IndexBufferTests : public ::testing::Test
	{
	protected:

		Renderer renderer;
		IndexBuffer indexBuffer;

		void SetUp() override
		{
			renderer.initialize();
			vk::BufferCreateInfo bufferCreateInfo = indexBuffer.createCreateInfo(1u);
			VmaAllocationCreateInfo allocationCreateInfo = indexBuffer.createVmaAllocationCreateInfo(false);

			indexBuffer.create(renderer, bufferCreateInfo, allocationCreateInfo);
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