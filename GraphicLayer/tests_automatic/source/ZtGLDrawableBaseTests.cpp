#pragma once

#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLDrawableBase.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"
#include "Zinet/GraphicLayer/ZtGLSampler.h"

#include <gtest/gtest.h>

#include <filesystem>

namespace zt::gl
{
	class Texture;
}

namespace zt::gl::tests
{
	class TestDrawableObjectClass : public DrawableBase
	{
		DrawInfo createDrawInfo(RendererContext& rendererContext) const override { return {}; }

		const Transform& getTransform() const override { return transform; }

		void setTransform(const Transform& newTransform) override { transform = newTransform; }

		Vector2ui getAbsoluteSize() const override { return Vector2ui{ 1.f, 1.f }; }

		std::vector<RenderStates::Descriptor> createRenderStatesDescriptors() const override { return {}; }

		void updateUniformBuffers(std::span<UniformBuffer> uniformBuffers) const override {}
		void updateStorageBuffers(std::span<StorageBuffer> storageBuffers) const override {}

	private:

		Transform transform;

	};

	class DrawableObjectSimpleTests : public ::testing::Test
	{
	protected:

		static_assert(!std::is_default_constructible_v<DrawableBase>);


		TestDrawableObjectClass testObject;
	};

	TEST_F(DrawableObjectSimpleTests, Pass)
	{}

	class DrawableObjectTests : public ::testing::Test
	{
	protected:

		const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

		RendererContext rendererContext;
		CommandBuffer commandBuffer;
		TestDrawableObjectClass testObject;

		void SetUp() override
		{
			GLFW::Init();
			rendererContext.initialize();
			commandBuffer.allocateCommandBuffer(rendererContext.getDevice(), rendererContext.getCommandPool());
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST_F(DrawableObjectTests, CreateRenderStatesImages)
	{
		// Texture
		STBImage stbImage;
		auto texturePath = ContentPath / "texture.jpg";
		if (!stbImage.load(texturePath.string()))
			FAIL() << "Load image failed";

		Texture texture;
		std::vector<std::reference_wrapper<const Texture>> textures{ texture };

		commandBuffer.begin();

		bool mipmaps = false;
		vk::Format format = vk::Format::eR8G8B8A8Srgb;
		Vector2ui size = { 640u, 640u };
		Texture::CreateInfo createInfo
		{
			rendererContext, commandBuffer, mipmaps, format, size
		};
		texture.create(createInfo);

		texture.loadFromSTBImage(commandBuffer, stbImage);

		commandBuffer.end();

		Sampler sampler;
		std::vector<std::reference_wrapper<const Sampler>> samplers{ sampler };

		std::vector<size_t> bindings{ 4u };

		const auto renderStatesImages = testObject.createRenderStatesImages(textures, samplers, bindings);
		ASSERT_FALSE(renderStatesImages.empty());

		const auto& renderStatesImage = renderStatesImages.front();
		EXPECT_EQ(renderStatesImage.buffer, texture.getImageBuffer());
		EXPECT_EQ(renderStatesImage.view, texture.getImageView());
		EXPECT_EQ(renderStatesImage.layout, texture.getImage().getImageLayouts().front());
		EXPECT_EQ(renderStatesImage.sampler, sampler);
		EXPECT_EQ(renderStatesImage.binding, bindings.front());
	}
}
