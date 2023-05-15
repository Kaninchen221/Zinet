#pragma once

#include "Zinet/GraphicLayer/ZtGLSprite.h"
#include "Zinet/GraphicLayer/ZtGLDrawableObject.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"
#include "Zinet/GraphicLayer/ZtGLSampler.h"
#include "Zinet/GraphicLayer/ZtGLShader.h"

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
		// TODO Sprite must be a copyable and movable

		void SetUp() override
		{
			GLFW::Init(false);
			renderer.initialize();
			GLFW::Deinit();
		}
	};

	TEST_F(SpriteTests, CreateDrawInfo)
	{
		shaders.emplace_back();
		shaders[0].setType(ShaderType::Vertex);
		shaders[0].loadFromFile((ContentPath / "shader.vert").string());
		shaders[0].compile();

		shaders.emplace_back();
		shaders[1].setType(ShaderType::Fragment);
		shaders[1].loadFromFile((ContentPath / "shader.frag").string());
		shaders[1].compile();

		vk::SamplerCreateInfo samplerCreateInfo = sampler.createCreateInfo();
		sampler.create(renderer.getDevice(), samplerCreateInfo);

		if (!stbImage.load((ContentPath / "texture.jpg").string()))
		{
			FAIL() << "Can't load texture image";
		}

		texture.create(stbImage, renderer);

		sprite.create(renderer);
		sprite.createDrawInfo(shaders, texture, sampler);
	}

	class SpriteSimpleTests : public ::testing::Test
	{
	protected:

		Sprite sprite;
	};

	TEST_F(SpriteSimpleTests, GetUniformBuffers)
	{
		// TODO: It's temporary (or not) and should be replaced with Transform class
		typedef std::vector<UniformBuffer>&(Sprite::* ExpectedFunctionDeclaration)();
		using FunctionDeclaration = decltype(&Sprite::getUniformBuffers);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		[[maybe_unused]] std::vector<UniformBuffer>& uniformBuffers = sprite.getUniformBuffers();
	}

	TEST_F(SpriteSimpleTests, TextureRegionGetSet)
	{
		typedef const TextureRegion& (Sprite::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Sprite::getTextureRegion);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		TextureRegion expected = { { 1.23f, 0.f }, { 0.f, 0.4232f } };
		sprite.setTextureRegion(expected);
		const TextureRegion& actual = sprite.getTextureRegion();

		ASSERT_EQ(expected, actual);
	}
}
