#pragma once

#include "Zinet/GraphicLayer/Buffers/ZtGLStagingBuffer.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class StagingBufferTests : public ::testing::Test
	{
	protected:

		Renderer renderer;
		StagingBuffer stagingBuffer;

		void SetUp() override
		{
			renderer.initialize();
			vk::BufferCreateInfo bufferCreateInfo = stagingBuffer.createCreateInfo(1u);
			VmaAllocationCreateInfo allocationCreateInfo = stagingBuffer.createVmaAllocationCreateInfo(false);

			stagingBuffer.create(renderer, bufferCreateInfo, allocationCreateInfo);
		}
	};

	TEST(StagingBuffer, DerivedFromBuffer)
	{
		static_assert(std::derived_from<StagingBuffer, Buffer>);
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