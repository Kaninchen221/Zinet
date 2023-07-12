#pragma once

#include "Zinet/GraphicLayer/ZtGLSprite.h"
#include "Zinet/GraphicLayer/ZtGLDrawableObject.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"
#include "Zinet/GraphicLayer/ZtGLSampler.h"
#include "Zinet/GraphicLayer/ZtGLShader.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

#include <filesystem>

namespace zt::gl::tests
{

	class SpriteTests : public ::testing::Test
	{
	protected:

		const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

		Renderer renderer;
		Sprite sprite;
		Texture texture;
		Sampler sampler;
		std::vector<Shader> shaders;
		STBImage stbImage;

		static_assert(std::is_base_of_v<DrawableObject, Sprite>);
		static_assert(std::is_default_constructible_v<Sprite>);

		static_assert(std::is_copy_constructible_v<Sprite>);
		static_assert(std::is_copy_assignable_v<Sprite>);

		static_assert(std::is_move_constructible_v<Sprite>);
		static_assert(std::is_move_assignable_v<Sprite>);

		void SetUp() override
		{
			GLFW::Init(false);
			renderer.initialize();
			RendererContext& rendererContext = renderer.getRendererContext();

			shaders.emplace_back();
			shaders[0].setType(ShaderType::Vertex);
			shaders[0].loadFromFile((ContentPath / "shader.vert").string());
			shaders[0].compile();

			shaders.emplace_back();
			shaders[1].setType(ShaderType::Fragment);
			shaders[1].loadFromFile((ContentPath / "shader.frag").string());
			shaders[1].compile();

			vk::SamplerCreateInfo samplerCreateInfo = sampler.createCreateInfo();
			sampler.create(rendererContext.getDevice(), samplerCreateInfo);

			if (!stbImage.load((ContentPath / "texture.jpg").string()))
			{
				FAIL() << "Can't load texture image";
			}

			texture.create(stbImage, rendererContext);

			sprite.createDrawInfo(rendererContext);
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST_F(SpriteTests, CreateDrawInfo)
	{
		DrawInfo drawInfo = sprite.createDrawInfo(renderer.getRendererContext());

		EXPECT_TRUE(drawInfo.vertexBuffer.isValid());
		EXPECT_TRUE(drawInfo.indexBuffer.isValid());
		EXPECT_FALSE(drawInfo.indices.empty());
		EXPECT_FALSE(drawInfo.uniformBuffers.empty());
	}

	class SpriteSimpleTests : public ::testing::Test
	{
	protected:

		Sprite sprite;
	};

	TEST_F(SpriteSimpleTests, TextureRegionGetSet)
	{
		typedef const TextureRegion& (Sprite::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Sprite::getTextureRegion);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		TextureRegion expected = { { 1.23f, 0.f }, { 0.f, 0.4232f } };
		Vector2f textureSize = { 1.f, 1.f };
		sprite.setTextureRegion(expected, textureSize);
		const TextureRegion& actual = sprite.getTextureRegion();

		ASSERT_EQ(expected.toShaderTextureRegion(textureSize), actual);
	}

	TEST_F(SpriteSimpleTests, GetSetTransform)
	{
		typedef const Transform& (Sprite::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Sprite::getTransform));

		Transform expected;
		expected.setTranslation({ 12.4f, 3.f, 1.f });
		expected.setScale({ 112.4f, 3.42f, 11.f });
		expected.setRotation({ 1.41f, 0.412f, 1.212f });
		sprite.setTransform(expected);

		const Transform& actual = sprite.getTransform();
		ASSERT_EQ(expected, actual);
	}

	TEST_F(SpriteSimpleTests, GetAbsoluteSize)
	{
		typedef Vector2ui (Sprite::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Sprite::getAbsoluteSize));

		Vector2ui actualAbsoluteSize = sprite.getAbsoluteSize();
		Vector2ui expectedAboluteSize = Vector2ui{ 1u, 1u };
		ASSERT_EQ(actualAbsoluteSize, expectedAboluteSize);
	}

	TEST_F(SpriteSimpleTests, Copy)
	{
		TextureRegion textureRegion;
		textureRegion.offset = { 233.f, 12.f };
		textureRegion.size = { 55.f, 16.f };

		Vector2f textureSize;
		textureSize.x = 10.f;
		textureSize.y = 20.f;

		sprite.setTextureRegion(textureRegion, textureSize);

		Transform transform;
		transform.setRotation({ 2.f, 1.f, 5.f });
		transform.setScale({ 1.f, 7.f, 2.f });
		transform.setTranslation({ 4.f, 6.f, 6.f });

		sprite.setTransform(transform);

		Sprite secondSprite;
		secondSprite = sprite;

		EXPECT_EQ(sprite.getTextureRegion(), secondSprite.getTextureRegion());
		EXPECT_EQ(sprite.getTransform(), secondSprite.getTransform());

		Sprite thirdSprite{ sprite };

		EXPECT_EQ(sprite.getTextureRegion(), thirdSprite.getTextureRegion());
		EXPECT_EQ(sprite.getTransform(), thirdSprite.getTransform());
	}
}
