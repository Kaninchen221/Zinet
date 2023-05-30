#pragma once

#include "Zinet/GraphicLayer/ZtGLTileMap.h"
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

	class TileMapTests : public ::testing::Test
	{
	protected:

		const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

		Renderer renderer;
		TileMap tileMap;
		Texture texture;
		Sampler sampler;
		std::vector<Shader> shaders;
		STBImage stbImage;

		static_assert(std::is_base_of_v<DrawableObject, TileMap>);
		static_assert(std::is_default_constructible_v<TileMap>);
		// TODO (Mid) TileMap must be a copyable and movable

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

			tileMap.create(rendererContext, texture.getSize(), {});
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST_F(TileMapTests, CreateDrawInfo)
	{
		tileMap.createDrawInfo(shaders, texture, sampler);
	}

	TEST_F(TileMapTests, CopyFrom)
	{
		RendererContext& rendererContext = renderer.getRendererContext();
		tileMap.createDrawInfo(shaders, texture, sampler);
		TileMap copy;
		copy.copyFrom(tileMap, rendererContext);

		ASSERT_EQ(tileMap.getTransform(), copy.getTransform());
		ASSERT_EQ(tileMap.getTextureRegion(), copy.getTextureRegion());
	}

	class TileMapSimpleTests : public ::testing::Test
	{
	protected:

		TileMap tileMap;
	};

	TEST_F(TileMapSimpleTests, GetDefaultValues)
	{
		const Vector2ui& actualTilesCount = tileMap.getTilesCount();
		Vector2ui expectedTilesCount = Vector2ui{ 1u, 1u };
		ASSERT_EQ(expectedTilesCount, actualTilesCount);
	}

	TEST_F(TileMapSimpleTests, GetUniformBuffers)
	{
		typedef const std::vector<UniformBuffer>&(TileMap::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&TileMap::getUniformBuffers);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		[[maybe_unused]] const std::vector<UniformBuffer>& uniformBuffers = tileMap.getUniformBuffers();
	}

	TEST_F(TileMapSimpleTests, TextureRegionGetSet)
	{
		typedef const TextureRegion& (TileMap::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&TileMap::getTextureRegion);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		TextureRegion expected = { { 1.23f, 0.f }, { 0.f, 0.4232f } };
		tileMap.setTextureRegion(expected);
		const TextureRegion& actual = tileMap.getTextureRegion();

		ASSERT_EQ(expected, actual);
	}

	TEST_F(TileMapSimpleTests, GetSetTransform)
	{
		typedef const Transform& (TileMap::* ExpectedFunction)() const;
		static_assert(IsFunctionEqual<ExpectedFunction>(&TileMap::getTransform));

		Transform expected;
		expected.setTranslation({ 12.4f, 3.f, 1.f });
		expected.setScale({ 112.4f, 3.42f, 11.f });
		expected.setRotation({ 1.41f, 0.412f, 1.212f });
		tileMap.setTransform(expected);

		const Transform& actual = tileMap.getTransform();
		ASSERT_EQ(expected, actual);
	}

	TEST_F(TileMapSimpleTests, GetSetTilesCount)
	{
		typedef const Vector2ui& (TileMap::* ExpectedFunction)() const;
		static_assert(IsFunctionEqual<ExpectedFunction>(&TileMap::getTilesCount));

		Vector2ui expectedCount = { 4u, 5u };
		tileMap.setTilesCount(expectedCount);
		const Vector2ui& actualCount = tileMap.getTilesCount();

		ASSERT_EQ(expectedCount, actualCount);
	}
}
