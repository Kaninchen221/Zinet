#pragma once

#include "Zinet/GraphicLayer/ZtGLTexture.hpp"
#include "Zinet/GraphicLayer/ZtGLRenderer.hpp"
#include "Zinet/GraphicLayer/ZtGLSTBImage.hpp"

#include "Zinet/Window/ZtGLFW.hpp"

#include "Zinet/Core/ZtTypeTraits.hpp"

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
		bool result = zt::core::TestGetters<Image, Texture>(&Texture::getImage, &Texture::getImage, texture);
		ASSERT_TRUE(result);
	}

	TEST_F(TextureSimpleTests, GetImageBuffer)
	{
		bool result = zt::core::TestGetters<ImageBuffer, Texture>(&Texture::getImageBuffer, &Texture::getImageBuffer, texture);
		ASSERT_TRUE(result);
	}

	TEST_F(TextureSimpleTests, GetImageView)
	{
		bool result = zt::core::TestGetters<ImageView, Texture>(&Texture::getImageView, &Texture::getImageView, texture);
		ASSERT_TRUE(result);
	}

	TEST_F(TextureSimpleTests, CreateInfoDefaultValues)
	{
		CommandBuffer commandBuffer;
		STBImage stbImage;
		RendererContext rendererContext;

		Texture::CreateInfo createInfo
		{
			rendererContext, commandBuffer
		};
		EXPECT_FALSE(createInfo.mipmaps);
		EXPECT_EQ(createInfo.format, vk::Format::eR8G8B8A8Srgb);
		EXPECT_EQ(createInfo.size, Vector2ui{});
	}

	class TextureTests : public ::testing::Test
	{
	protected:

		const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

		RendererContext rendererContext;
		Texture texture;
		CommandBuffer commandBuffer;

		void SetUp() override
		{
			wd::GLFW::Init(true);

			rendererContext.initialize();

			commandBuffer.allocateCommandBuffer(rendererContext.getDevice(), rendererContext.getCommandPool());
			commandBuffer.begin();

			bool mipmaps = false;
			vk::Format format = vk::Format::eR8G8B8A8Srgb;
			Vector2ui size = { 640u, 640u };
			Texture::CreateInfo createInfo
			{
				rendererContext, commandBuffer, size, mipmaps, format
			};
			texture.create(createInfo);
			commandBuffer.end();

			rendererContext.getQueue().submitWaitIdle(commandBuffer);
		}

		void TearDown() override
		{
			wd::GLFW::Deinit();
		}
	};

	TEST_F(TextureTests, Create)
	{
		const Image& image = texture.getImage();
		ASSERT_TRUE(image.isValid());

		Vector2f imageSize = image.getSize();
		Vector2f textureSize = texture.getSize();
		EXPECT_EQ(textureSize, imageSize);

		const ImageBuffer& imageBuffer = texture.getImageBuffer();
		ASSERT_TRUE(imageBuffer.isValid());

		const ImageView& imageView = texture.getImageView();
		ASSERT_TRUE(imageView.isValid());
	}

	TEST_F(TextureTests, LoadFromSTBImage)
	{
		STBImage stbImage;
		if (!stbImage.load((ContentPath / "texture.jpg").string()))
		{
			FAIL() << "Can't load texture image";
			return;
		}

		commandBuffer.begin();
		texture.loadFromSTBImage(commandBuffer, stbImage);
		commandBuffer.end();

		rendererContext.getQueue().submitWaitIdle(commandBuffer);
	}

	TEST_F(TextureTests, Clear)
	{
		texture.clear();

		const Image& image = texture.getImage();
		ASSERT_FALSE(image.isValid());

		const ImageBuffer& imageBuffer = texture.getImageBuffer();
		ASSERT_FALSE(imageBuffer.isValid());

		const ImageView& imageView = texture.getImageView();
		ASSERT_FALSE(imageView.isValid());
	}

	TEST_F(TextureTests, PrepareForDraw)
	{
		commandBuffer.begin();
		texture.prepareForDraw(commandBuffer);
		commandBuffer.end();
		rendererContext.getQueue().submitWaitIdle(commandBuffer);
	}
}
