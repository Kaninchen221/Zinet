#pragma once

#include "Zinet/GraphicLayer/Buffers/ZtGLImageBuffer.h"
#include "Zinet/GraphicLayer/ZtGLSampler.h"
#include "Zinet/GraphicLayer/ZtGLImageView.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class ImageBufferTests : public ::testing::Test
	{
	protected:

		Renderer renderer;
		ImageBuffer imageBuffer;

		void SetUp() override
		{
			renderer.initialize();

			BufferCreateInfo bufferCreateInfo{ .device = renderer.getDevice(), .vma = renderer.getVma() };
			bufferCreateInfo.vkBufferCreateInfo = imageBuffer.createCreateInfo(1u);
			bufferCreateInfo.allocationCreateInfo = imageBuffer.createVmaAllocationCreateInfo(false, true);

			imageBuffer.create(bufferCreateInfo);
		}
	};

	TEST(ImageBuffer, DerivedFromBuffer)
	{
		static_assert(std::derived_from<ImageBuffer, Buffer>);
	}

	TEST_F(ImageBufferTests, CreateDescriptorImageInfo)
	{
		typedef vk::DescriptorImageInfo(ImageBuffer::* ExpectedFunctionDeclaration)(const Sampler&, const ImageView&, vk::ImageLayout) const;
		using FunctionDeclaration = decltype(&ImageBuffer::createDescriptorImageInfo);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		Sampler sampler;
		ImageView imageView;
		vk::ImageLayout imageLayout{};
		vk::DescriptorImageInfo info = imageBuffer.createDescriptorImageInfo(sampler, imageView, imageLayout);

		ASSERT_EQ(info.sampler, *sampler.getInternal());
		ASSERT_EQ(info.imageView, *imageView.getInternal());
		ASSERT_EQ(info.imageLayout, imageLayout);
	}
}