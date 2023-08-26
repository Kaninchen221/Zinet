#pragma once

#include "Zinet/GraphicLayer/ZtGLImageView.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLSwapChain.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"

#include <memory>

#include <gtest/gtest.h>

namespace zt::gl::tests
{
	class ImageViewSimpleTests : public ::testing::Test
	{
	protected:

		ImageView imageView;

		static_assert(std::derived_from<ImageView, VulkanObject<vk::raii::ImageView>>);
	};

	TEST_F(ImageViewSimpleTests, CreateImageViewCreateInfo)
	{
		vk::Image image;
		std::uint32_t mipmapLevels = 1u;
		vk::Format format;
		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(image, mipmapLevels, format);

		ASSERT_NE(imageViewCreateInfo, vk::ImageViewCreateInfo());
	}

	TEST_F(ImageViewSimpleTests, GetMipmapLevels)
	{
		typedef std::uint32_t(ImageView::* ExpectedFunctionDeclaration)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunctionDeclaration>(&ImageView::getMipmapLevels));

		std::uint32_t mipmapLevels = imageView.getMipmapLevels();
		EXPECT_EQ(mipmapLevels, 0u);
	}

	class ImageViewTests : public ::testing::Test
	{
	protected:

		RendererContext rendererContext;
		ImageView imageView;

	};

	TEST_F(ImageViewTests, CreateImageView)
	{
		typedef void(ImageView::* ExpectedFunctionDeclaration)(const Device& device, const vk::ImageViewCreateInfo&);
		static_assert(zt::core::IsFunctionEqual<ExpectedFunctionDeclaration>(&ImageView::create));

		GLFW::Init();

		rendererContext.initialize();

		std::vector<vk::Image> images = rendererContext.getSwapChain().getImages();
		std::uint32_t mipmapLevels = 1u;
		vk::SurfaceFormatKHR surfaceFormat = rendererContext.getSwapChainSupportDetails().pickFormat();
		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(images[0], mipmapLevels, surfaceFormat.format);
		imageView.create(rendererContext.getDevice(), imageViewCreateInfo);
		
		ASSERT_TRUE(imageView.isValid());

		GLFW::Deinit();
	}

}