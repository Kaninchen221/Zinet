#pragma once

#include "Zinet/GraphicLayer/Buffers/ZtGLUniformBuffer.hpp"
#include "Zinet/GraphicLayer/ZtGLRenderer.hpp"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class UniformBufferTests : public ::testing::Test
	{
	protected:

		Renderer renderer;
		UniformBuffer uniformBuffer;

		void SetUp() override
		{
			renderer.initialize();
			RendererContext& rendererContext = renderer.getRendererContext();

			Buffer::CreateInfo bufferCreateInfo{ .device = rendererContext.getDevice(), .vma = rendererContext.getVma() };
			bufferCreateInfo.vkBufferCreateInfo = uniformBuffer.createCreateInfo(1u);
			bufferCreateInfo.allocationCreateInfo = uniformBuffer.createVmaAllocationCreateInfo(false, true);

			uniformBuffer.create(bufferCreateInfo);
		}
	};

	TEST(UniformBuffer, DerivedFromBuffer)
	{
		static_assert(std::derived_from<UniformBuffer, Buffer>);
	}

	TEST(UniformBuffer, CreateCreateInfo)
	{
		UniformBuffer uniformBuffer;
		std::uint64_t expectedSize = 1u;
		vk::BufferCreateInfo uniformBufferCreateInfo = uniformBuffer.createCreateInfo(expectedSize);

		ASSERT_EQ(uniformBufferCreateInfo.usage, vk::BufferUsageFlagBits::eUniformBuffer);
		ASSERT_EQ(uniformBufferCreateInfo.size, expectedSize);
		ASSERT_EQ(uniformBufferCreateInfo.sharingMode, vk::SharingMode::eExclusive);
	}

	TEST_F(UniformBufferTests, CreateDescriptorBufferInfo)
	{
		vk::DescriptorBufferInfo info = uniformBuffer.createDescriptorBufferInfo();

		ASSERT_EQ(info.buffer, *uniformBuffer.getInternal());
		ASSERT_EQ(info.offset, 0);
		ASSERT_EQ(info.range, uniformBuffer.getSize());
	}

	TEST_F(UniformBufferTests, CreateTest)
	{
		ASSERT_NE(*uniformBuffer.getInternal(), *vk::raii::Buffer{ std::nullptr_t{} });
	}

	class UniformBufferSimpleTests : public ::testing::Test
	{
	protected:

		UniformBuffer uniformBuffer;
	};

	TEST_F(UniformBufferSimpleTests, Binding)
	{
		std::uint32_t expectedBinding = 3u;
		uniformBuffer.setBinding(expectedBinding);
		std::uint32_t actualBinding = uniformBuffer.getBinding();

		ASSERT_EQ(expectedBinding, actualBinding);
	}
}