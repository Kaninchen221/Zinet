#pragma once

#include "Zinet/GraphicLayer/Buffers/ZtGLStagingBuffer.hpp"
#include "Zinet/GraphicLayer/ZtGLRenderer.hpp"

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
			RendererContext& rendererContext = renderer.getRendererContext();

			Buffer::CreateInfo bufferCreateInfo{ .device = rendererContext.getDevice(), .vma = rendererContext.getVma() };
			bufferCreateInfo.vkBufferCreateInfo = stagingBuffer.createCreateInfo(1u);
			bufferCreateInfo.allocationCreateInfo = stagingBuffer.createVmaAllocationCreateInfo(false, true);

			stagingBuffer.create(bufferCreateInfo);
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