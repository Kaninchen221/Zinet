#pragma once

#include "Zinet/GraphicLayer/ZtGLTexture.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLSTBImage.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"

#include <gtest/gtest.h>

#include <filesystem>

namespace zt::gl::tests
{

	class TextureSimpleTests : public ::testing::Test
	{
	protected:

		Texture texture;

	};

	TEST_F(TextureSimpleTests, GetImage)
	{
		typedef const Image& (Texture::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Texture::getImage);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		const Image& image = texture.getImage();
		ASSERT_FALSE(image.isValid());
	}

	TEST_F(TextureSimpleTests, GetImageBuffer)
	{
		typedef const ImageBuffer& (Texture::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Texture::getImageBuffer);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		const ImageBuffer& imageBuffer = texture.getImageBuffer();
		ASSERT_FALSE(imageBuffer.isValid());
	}

	TEST_F(TextureSimpleTests, GetImageView)
	{
		typedef const ImageView& (Texture::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Texture::getImageView);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		const ImageView& imageView = texture.getImageView();
		ASSERT_FALSE(imageView.isValid());
	}

	TEST_F(TextureSimpleTests, GetImageLayout)
	{
		typedef const vk::ImageLayout& (Texture::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Texture::getVkImageLayout);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);
	}

	TEST_F(TextureSimpleTests, CreateImageDrawInfo)
	{
		typedef RenderStates::Image (Texture::* ExpectedFunctionDeclaration)(const Sampler&) const;
		using FunctionDeclaration = decltype(&Texture::createImageDrawInfo);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		Sampler sampler;
		RenderStates::Image imageDrawInfo = texture.createImageDrawInfo(sampler);
	}

	class TextureTests : public ::testing::Test
	{
	protected:

		const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

		Renderer renderer;
		Texture texture;
		STBImage stbImage;
		Sampler sampler;
	};

	TEST_F(TextureTests, Create)
	{
		GLFW::Init(true);

		renderer.initialize();
		RendererContext& rendererContext = renderer.getRendererContext();

		if (!stbImage.load((ContentPath / "texture.jpg").string()))
		{
			FAIL() << "Can't load texture image";
			return;
		}

		vk::SamplerCreateInfo samplerCreateInfo = sampler.createCreateInfo();
		sampler.create(rendererContext.getDevice(), samplerCreateInfo);

		texture.create(stbImage, rendererContext);

		const Image& image = texture.getImage();
		ASSERT_TRUE(image.isValid());

		const ImageBuffer& imageBuffer = texture.getImageBuffer();
		ASSERT_TRUE(imageBuffer.isValid());

		const ImageView& imageView = texture.getImageView();
		ASSERT_TRUE(imageView.isValid());

		vk::ImageLayout vkImageLayout = texture.getVkImageLayout();
		ASSERT_EQ(vkImageLayout, vk::ImageLayout::eShaderReadOnlyOptimal);

		RenderStates::Image imageDrawInfo = texture.createImageDrawInfo(sampler);
		ASSERT_EQ(imageDrawInfo.buffer, imageBuffer);
		ASSERT_EQ(imageDrawInfo.sampler, sampler);
		ASSERT_EQ(imageDrawInfo.view, imageView);
		ASSERT_EQ(imageDrawInfo.layout, vkImageLayout);
	}
}
