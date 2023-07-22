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

		static_assert(std::derived_from<Image, VulkanObject<vk::raii::Image>>);
	};

	TEST_F(ImageSimpleTests, CreateCreateInfo)
	{
		Image image;
		std::uint32_t expectedWidth = 0u;
		std::uint32_t expectedHeight = 0u;
		vk::ImageCreateInfo createInfo = image.createCreateInfo(expectedWidth, expectedHeight);

		ASSERT_EQ(createInfo.imageType, vk::ImageType::e2D);
		ASSERT_EQ(createInfo.extent.width, expectedWidth);
		ASSERT_EQ(createInfo.extent.height, expectedHeight);
		ASSERT_EQ(createInfo.extent.depth, 1);
		ASSERT_EQ(createInfo.mipLevels, 1);
		ASSERT_EQ(createInfo.arrayLayers, 1);
		ASSERT_EQ(createInfo.format, vk::Format::eR8G8B8A8Srgb);
		ASSERT_EQ(createInfo.tiling, vk::ImageTiling::eOptimal);
		ASSERT_EQ(createInfo.initialLayout, vk::ImageLayout::eUndefined);
		ASSERT_EQ(createInfo.usage, vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled | vk::ImageUsageFlagBits::eTransferSrc); // TODO (low)
		ASSERT_EQ(createInfo.sharingMode, vk::SharingMode::eExclusive);
		ASSERT_EQ(createInfo.samples, vk::SampleCountFlagBits::e1);
	}

	TEST_F(ImageSimpleTests, CreateVmaAllocationCreateInfo)
	{
		Image image;
		VmaAllocationCreateInfo allocationCreateInfo = image.createAllocationCreateInfo();

		ASSERT_EQ(allocationCreateInfo.usage, VMA_MEMORY_USAGE_AUTO);
		ASSERT_EQ(allocationCreateInfo.flags, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
		ASSERT_EQ(allocationCreateInfo.priority, 1.f);
	}

	TEST_F(ImageSimpleTests, GetMipmapLevels)
	{
		typedef std::uint32_t (Image::* ExpectedFunctionDeclaration)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunctionDeclaration>(&Image::getMipmapLevels));

		Image image;
		std::uint32_t mipmapLevels = image.getMipmapLevels();
		EXPECT_EQ(mipmapLevels, 0u);
	}

	class ImageTests : public ::testing::Test
	{
	protected:

		Renderer renderer;
		Image image;

		void SetUp() override
		{
			renderer.initialize();
		}
	};

	TEST_F(ImageTests, Create)
	{
		RendererContext& rendererContext = renderer.getRendererContext();

		std::uint32_t expectedWidth = 1u;
		std::uint32_t expectedHeight = 1u;
		std::uint32_t mipmapLevels = 1u;
	
		Image::CreateInfo imageCreateInfo { 
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkImageCreateInfo = image.createCreateInfo(expectedWidth, expectedHeight, mipmapLevels),
			.allocationCreateInfo = image.createAllocationCreateInfo()
		};

		image.create(imageCreateInfo);

		ASSERT_TRUE(image.isValid());
		EXPECT_EQ(image.getWidth(), expectedWidth);
		EXPECT_EQ(image.getHeight(), expectedHeight);
		EXPECT_EQ(image.getMipmapLevels(), mipmapLevels);
	}

}
