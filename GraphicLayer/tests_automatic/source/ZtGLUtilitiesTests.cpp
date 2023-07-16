#pragma once

#include "Zinet/GraphicLayer/ZtGLUtilities.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"

#include <gtest/gtest.h>

#include <filesystem>

namespace zt::gl::tests
{

	class UtilitiesTests : public ::testing::Test
	{
	protected:

		const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

		RendererContext rendererContext;
		Texture texture;
		STBImage stbImage;

		void SetUp() override
		{
			GLFW::Init();

			rendererContext.initialize();
			createSTBImage();
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}

		void createSTBImage();
	};

	TEST_F(UtilitiesTests, GenerateMipmapTexture)
	{
		bool textureUseMipmaps = false;
		CommandBuffer commandBuffer;
		commandBuffer.allocateCommandBuffer(rendererContext.getDevice(), rendererContext.getCommandPool());
		commandBuffer.begin();

		texture.create({ commandBuffer, stbImage, rendererContext, textureUseMipmaps });

		Utilities::GenerateMipmapTextureInfo generateMipmapTextureInfo
		{
			texture, commandBuffer, rendererContext
		};
		Texture result;
		Utilities::GenerateMipmapTexture(generateMipmapTextureInfo, result);

		commandBuffer.end();

		vk::SubmitInfo submitInfo{};
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

		rendererContext.getQueue().submit(submitInfo);
		rendererContext.getQueue()->waitIdle();

		ASSERT_TRUE(result.getImage().isValid());
		ASSERT_TRUE(result.getImageBuffer().isValid());
		ASSERT_TRUE(result.getImageView().isValid());
	}

	void UtilitiesTests::createSTBImage()
	{
		if (!stbImage.load((ContentPath / "test_texture.png").string()))
		{
			FAIL() << "Can't load texture image";
		}
	}
}
