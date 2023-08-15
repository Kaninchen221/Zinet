#pragma once

#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{
	class ImageSimpleTests : public ::testing::Test
	{
	protected:

		Vector2<std::uint32_t> expectedSize = { 0u, 0u };

		static_assert(std::derived_from<Image, VulkanObject<vk::raii::Image>>);

		Image image;
	};

	TEST_F(ImageSimpleTests, CreateCreateInfo)
	{
		vk::ImageCreateInfo createInfo = image.createCreateInfo(expectedSize);

		ASSERT_EQ(createInfo.imageType, vk::ImageType::e2D);
		ASSERT_EQ(createInfo.extent.width, expectedSize.x);
		ASSERT_EQ(createInfo.extent.height, expectedSize.y);
		ASSERT_EQ(createInfo.extent.depth, 1);
		ASSERT_EQ(createInfo.mipLevels, 1);
		ASSERT_EQ(createInfo.arrayLayers, 1);
		ASSERT_EQ(createInfo.format, vk::Format::eR8G8B8A8Srgb);
		ASSERT_EQ(createInfo.tiling, vk::ImageTiling::eOptimal);
		ASSERT_EQ(createInfo.initialLayout, vk::ImageLayout::eUndefined);
		ASSERT_EQ(createInfo.usage, vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled | vk::ImageUsageFlagBits::eTransferSrc);
		ASSERT_EQ(createInfo.sharingMode, vk::SharingMode::eExclusive);
		ASSERT_EQ(createInfo.samples, vk::SampleCountFlagBits::e1);
	}

	TEST_F(ImageSimpleTests, CreateVmaAllocationCreateInfo)
	{
		VmaAllocationCreateInfo allocationCreateInfo = image.createAllocationCreateInfo();

		ASSERT_EQ(allocationCreateInfo.usage, VMA_MEMORY_USAGE_AUTO);
		ASSERT_EQ(allocationCreateInfo.flags, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
		ASSERT_EQ(allocationCreateInfo.priority, 1.f);
	}

	TEST_F(ImageSimpleTests, GetMipmapLevels)
	{
		typedef std::uint32_t (Image::* ExpectedFunctionDeclaration)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunctionDeclaration>(&Image::getMipmapLevels));

		std::uint32_t mipmapLevels = image.getMipmapLevels();
		EXPECT_EQ(mipmapLevels, 0u);
	}

	TEST_F(ImageSimpleTests, GetLayouts)
	{
		using ExpectedFunction = const std::vector<vk::ImageLayout>& (Image::*)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Image::getImageLayouts));

		const std::vector<vk::ImageLayout>& imageLayouts = image.getImageLayouts();
		ASSERT_TRUE(imageLayouts.empty());
	}

	TEST_F(ImageSimpleTests, GetPipelineStageFlags)
	{
		using ExpectedFunction = const std::vector<vk::ImageLayout>& (Image::*)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Image::getImageLayouts));

		const std::vector<vk::PipelineStageFlags>& pipelineStageFlags = image.getPipelineStageFlags();
		ASSERT_TRUE(pipelineStageFlags.empty());
	}

	class ImageTests : public ::testing::Test
	{
	protected:

		Vector2<std::uint32_t> expectedSize = { 1024u, 1024u };
		std::uint32_t mipmapLevels = 3u;

		Renderer renderer;
		Image image;

		void SetUp() override
		{
			renderer.initialize();
			RendererContext& rendererContext = renderer.getRendererContext();

			Image::CreateInfo imageCreateInfo {
				.device = rendererContext.getDevice(),
				.vma = rendererContext.getVma(),
				.vkImageCreateInfo = image.createCreateInfo(expectedSize, mipmapLevels),
				.allocationCreateInfo = image.createAllocationCreateInfo()
			};

			image.create(imageCreateInfo);
		}
	};

	TEST_F(ImageTests, Create)
	{
		ASSERT_TRUE(image.isValid());
		EXPECT_EQ(image.getSize(), expectedSize);
		EXPECT_EQ(image.getMipmapLevels(), mipmapLevels);

		EXPECT_EQ(image.getImageLayouts().size(), mipmapLevels);
		for (vk::ImageLayout imageLayout : image.getImageLayouts())
		{
			EXPECT_EQ(imageLayout, vk::ImageLayout::eUndefined);
		}

		EXPECT_EQ(image.getPipelineStageFlags().size(), mipmapLevels);
		for (vk::PipelineStageFlags pipelineStageFlags : image.getPipelineStageFlags())
		{
			EXPECT_EQ(pipelineStageFlags, vk::PipelineStageFlagBits::eTopOfPipe);
		}
	}

	TEST_F(ImageTests, ChangeLayout)
	{
		vk::ImageLayout expectedLayout = vk::ImageLayout::eTransferDstOptimal;
		vk::PipelineStageFlags expectedFlags = vk::PipelineStageFlagBits::eTransfer;

		RendererContext& rendererContext = renderer.getRendererContext();

		CommandBuffer commandBuffer;
		commandBuffer.allocateCommandBuffer(rendererContext.getDevice(), rendererContext.getCommandPool());

		commandBuffer.begin();
		image.changeLayout(commandBuffer, expectedLayout, expectedFlags);
		commandBuffer.end();

		for (vk::ImageLayout imageLayout : image.getImageLayouts())
		{
			EXPECT_EQ(imageLayout, expectedLayout);
		}

		for (vk::PipelineStageFlags pipelineStageFlags : image.getPipelineStageFlags())
		{
			EXPECT_EQ(pipelineStageFlags, expectedFlags);
		}

		Queue& queue = rendererContext.getQueue();
		queue.submitWaitIdle(commandBuffer);
	}

	TEST_F(ImageTests, Clear)
	{
		image.clear();

		ASSERT_FALSE(image.isValid());

		RendererContext& rendererContext = renderer.getRendererContext();
		Image::CreateInfo imageCreateInfo {
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkImageCreateInfo = image.createCreateInfo(expectedSize, mipmapLevels),
			.allocationCreateInfo = image.createAllocationCreateInfo()
		};
		image.create(imageCreateInfo);

		ASSERT_TRUE(image.isValid());
	}
}
