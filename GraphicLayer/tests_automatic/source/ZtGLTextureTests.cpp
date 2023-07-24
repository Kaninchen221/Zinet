#pragma once

#include "Zinet/GraphicLayer/ZtGLTexture.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLSTBImage.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"

#include "Zinet/Core/ZtTypeTraits.h"

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

	TEST_F(TextureSimpleTests, CreateImageDrawInfo)
	{
		typedef RenderStates::Image (Texture::* ExpectedFunctionDeclaration)(const Sampler&) const;
		using FunctionDeclaration = decltype(&Texture::createImageDrawInfo);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		Sampler sampler;
		RenderStates::Image imageDrawInfo = texture.createImageDrawInfo(sampler);
	}

	TEST_F(TextureSimpleTests, CreateInfoDefaultValues)
	{
		CommandBuffer commandBuffer;
		STBImage stbImage;
		RendererContext rendererContext;

		Texture::CreateInfo createInfo
		{
			commandBuffer, stbImage, rendererContext
		};
		EXPECT_FALSE(createInfo.mipmaps);
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

		CommandBuffer commandBuffer;
		commandBuffer.allocateCommandBuffer(rendererContext.getDevice(), rendererContext.getCommandPool());
		commandBuffer.begin();
		Texture::CreateInfo createInfo
		{
			commandBuffer, stbImage, rendererContext
		};
		texture.create(createInfo);
		commandBuffer.end();

		vk::SubmitInfo submitInfo{};
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

		rendererContext.getQueue().submit(submitInfo);
		rendererContext.getQueue()->waitIdle();

		const Image& image = texture.getImage();
		ASSERT_TRUE(image.isValid());

		Vector2f imageSize = image.getSize();
		Vector2f textureSize = texture.getSize();
		EXPECT_EQ(textureSize, imageSize);

		const ImageBuffer& imageBuffer = texture.getImageBuffer();
		ASSERT_TRUE(imageBuffer.isValid());

		const ImageView& imageView = texture.getImageView();
		ASSERT_TRUE(imageView.isValid());

// 		vk::ImageLayout vkImageLayout = texture.getVkImageLayout();
// 		ASSERT_EQ(vkImageLayout, vk::ImageLayout::eShaderReadOnlyOptimal); // TODO (mid)

		RenderStates::Image imageDrawInfo = texture.createImageDrawInfo(sampler);
		ASSERT_EQ(imageDrawInfo.buffer, imageBuffer);
		ASSERT_EQ(imageDrawInfo.sampler, sampler);
		ASSERT_EQ(imageDrawInfo.view, imageView);
//		ASSERT_EQ(imageDrawInfo.layout, vkImageLayout);

		GLFW::Deinit();
	}
}
