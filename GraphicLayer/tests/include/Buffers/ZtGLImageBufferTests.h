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
			vk::BufferCreateInfo bufferCreateInfo = imageBuffer.createCreateInfo(1u);
			VmaAllocationCreateInfo allocationCreateInfo = imageBuffer.createVmaAllocationCreateInfo(false);

			imageBuffer.create(renderer, bufferCreateInfo, allocationCreateInfo);
		}
	};

	TEST(ImageBuffer, DerivedFromBuffer)
	{
		static_assert(std::derived_from<ImageBuffer, Buffer>);
	}

	TEST_F(ImageBufferTests, CreateDescriptorImageInfo)
	{
		Sampler sampler;
		ImageView imageView;
		vk::ImageLayout imageLayout{};
		vk::DescriptorImageInfo info = imageBuffer.createDescriptorImageInfo(sampler, imageView, imageLayout);

		ASSERT_EQ(info.sampler, *sampler.getInternal());
		ASSERT_EQ(info.imageView, *imageView.getInternal());
		ASSERT_EQ(info.imageLayout, imageLayout);
	}
}