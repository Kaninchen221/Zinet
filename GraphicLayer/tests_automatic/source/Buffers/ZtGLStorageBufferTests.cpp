#pragma once

#include "Zinet/GraphicLayer/Buffers/ZtGLStorageBuffer.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class StorageBufferTests : public ::testing::Test
	{
	protected:

		static_assert(std::derived_from<StorageBuffer, Buffer>);

		Renderer renderer;
		StorageBuffer storageBuffer;

		void SetUp() override
		{
			renderer.initialize();
			RendererContext& rendererContext = renderer.getRendererContext();

			Buffer::CreateInfo bufferCreateInfo{ .device = rendererContext.getDevice(), .vma = rendererContext.getVma() };
			bufferCreateInfo.vkBufferCreateInfo = storageBuffer.createCreateInfo(1u);
			bufferCreateInfo.allocationCreateInfo = storageBuffer.createVmaAllocationCreateInfo(false, true);

			storageBuffer.create(bufferCreateInfo);
		}
	};

	TEST_F(StorageBufferTests, CreateDescriptorBufferInfo)
	{
		vk::DescriptorBufferInfo info = storageBuffer.createDescriptorBufferInfo();

		ASSERT_EQ(info.buffer, *storageBuffer.getInternal());
		ASSERT_EQ(info.offset, 0);
		ASSERT_EQ(info.range, storageBuffer.getSize());
	}

	TEST_F(StorageBufferTests, CreateTest)
	{
		ASSERT_TRUE(storageBuffer.isValid());
	}

	class StorageBufferSimpleTests : public ::testing::Test
	{
	protected:

		StorageBuffer storageBuffer;
	};

	TEST_F(StorageBufferSimpleTests, Binding)
	{
		std::uint32_t expectedBinding = 3u;
		storageBuffer.setBinding(expectedBinding);
		std::uint32_t actualBinding = storageBuffer.getBinding();

		ASSERT_EQ(expectedBinding, actualBinding);
	}

	TEST_F(StorageBufferSimpleTests, CreateCreateInfo)
	{
		std::uint64_t expectedSize = 1u;
		vk::BufferCreateInfo storageBufferCreateInfo = storageBuffer.createCreateInfo(expectedSize);

		ASSERT_EQ(storageBufferCreateInfo.usage, vk::BufferUsageFlagBits::eStorageBuffer);
		ASSERT_EQ(storageBufferCreateInfo.size, expectedSize);
		ASSERT_EQ(storageBufferCreateInfo.sharingMode, vk::SharingMode::eExclusive);
	}
}