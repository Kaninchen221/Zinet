#pragma once

#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

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

	TEST(Image, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<Image, VulkanObject<vk::raii::Image>>);
	}

	TEST(Image, CreateCreateInfo)
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
		ASSERT_EQ(createInfo.usage, vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled);
		ASSERT_EQ(createInfo.sharingMode, vk::SharingMode::eExclusive);
		ASSERT_EQ(createInfo.samples, vk::SampleCountFlagBits::e1);
	}

	TEST(Image, CreateVmaAllocationCreateInfo)
	{
		Image image;
		VmaAllocationCreateInfo allocationCreateInfo = image.createAllocationCreateInfo();

		ASSERT_EQ(allocationCreateInfo.usage, VMA_MEMORY_USAGE_AUTO);
		ASSERT_EQ(allocationCreateInfo.flags, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
		ASSERT_EQ(allocationCreateInfo.priority, 1.f);
	}

	TEST_F(ImageTests, Create)
	{
		std::uint32_t expectedWidth = 1u;
		std::uint32_t expectedHeight = 1u;
	
		ImageCreateInfo imageCreateInfo { 
			.device = renderer.getDevice(), 
			.vma = renderer.getVma(),
			.vkImageCreateInfo = image.createCreateInfo(expectedWidth, expectedHeight),
			.allocationCreateInfo = image.createAllocationCreateInfo()
		};

		image.create(imageCreateInfo);

		ASSERT_NE(*image.getInternal(), *vk::raii::Image{ std::nullptr_t{} });
	}

}
