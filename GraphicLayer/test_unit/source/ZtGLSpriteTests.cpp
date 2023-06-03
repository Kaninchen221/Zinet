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

		// TODO (Low) Sprite test copy and move

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
		// TODO (Mid) Test it
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
		static_assert(IsFunctionEqual<ExpectedFunction>(&Sprite::getTransform));

		Transform expected;
		expected.setTranslation({ 12.4f, 3.f, 1.f });
		expected.setScale({ 112.4f, 3.42f, 11.f });
		expected.setRotation({ 1.41f, 0.412f, 1.212f });
		sprite.setTransform(expected);

		const Transform& actual = sprite.getTransform();
		ASSERT_EQ(expected, actual);
	}
}
