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

		static_assert(std::is_copy_constructible_v<TileMap>);
		static_assert(std::is_copy_assignable_v<TileMap>);

		static_assert(std::is_move_constructible_v<TileMap>);
		static_assert(std::is_move_assignable_v<TileMap>);

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

			CommandBuffer commandBuffer;
			commandBuffer.allocateCommandBuffer(rendererContext.getDevice(), rendererContext.getCommandPool());
			commandBuffer.begin();
			Texture::CreateInfo createInfo
			{
				rendererContext, commandBuffer, false, vk::Format::eR8G8B8A8Srgb, { 640u, 640u }
			};
			texture.create(createInfo);
			commandBuffer.end();

			vk::SubmitInfo submitInfo{};
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

			rendererContext.getQueue().submit(submitInfo);
			rendererContext.getQueue()->waitIdle();

			tileMap.setTilesTextureRegions({ TextureRegion{} }, Vector2f{ 1.f, 1.f });
			tileMap.createDrawInfo(rendererContext);
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST_F(TileMapTests, CreateDrawInfo)
	{
		DrawInfo drawInfo = tileMap.createDrawInfo(renderer.getRendererContext());

		EXPECT_TRUE(drawInfo.vertexBuffer.isValid());
		EXPECT_TRUE(drawInfo.indexBuffer.isValid());
		EXPECT_FALSE(drawInfo.indices.empty());
		EXPECT_FALSE(drawInfo.uniformBuffers.empty());
		EXPECT_FALSE(drawInfo.storageBuffers.empty());
		EXPECT_NE(drawInfo.MVPBufferIndex, std::numeric_limits<size_t>::max());
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
		EXPECT_EQ(expectedTilesCount, actualTilesCount);

		std::vector<TextureRegion> actualTilesTextureRegions = tileMap.getTilesTextureRegions();
		EXPECT_TRUE(actualTilesTextureRegions.empty());
	}

	TEST_F(TileMapSimpleTests, GetAbsoluteSize)
	{
		typedef Vector2ui(TileMap::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&TileMap::getAbsoluteSize));

		tileMap.setTilesCount(Vector2ui{ 2u, 3u });

		Vector2ui actualAbsoluteSize = tileMap.getAbsoluteSize();
		const Vector2ui& expectedAboluteSize = tileMap.getTilesCount();
		ASSERT_EQ(actualAbsoluteSize, expectedAboluteSize);
	}

	TEST_F(TileMapSimpleTests, GetSetDefaultShaderTextureRegion)
	{
		typedef const TextureRegion& (TileMap::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&TileMap::getDefaultShaderTextureRegion);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		TextureRegion expected = { { 1.23f, 0.f }, { 0.f, 0.4232f } };
		Vector2f textureSize = { 1.f, 1.f };
		tileMap.setDefaultShaderTextureRegion(expected, textureSize);
		const TextureRegion& actual = tileMap.getDefaultShaderTextureRegion();

		ASSERT_EQ(expected.toShaderTextureRegion(textureSize), actual);
	}

	TEST_F(TileMapSimpleTests, GetSetTransform)
	{
		typedef const Transform& (TileMap::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&TileMap::getTransform));

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
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&TileMap::getTilesCount));

		Vector2ui expectedCount = { 4u, 5u };
		tileMap.setTilesCount(expectedCount);
		const Vector2ui& actualCount = tileMap.getTilesCount();

		ASSERT_EQ(expectedCount, actualCount);
	}

	TEST_F(TileMapSimpleTests, GetSetClearTilesTextureRegions)
	{
		typedef const std::vector<TextureRegion>& (TileMap::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&TileMap::getTilesTextureRegions));

		Vector2f textureSize = { 100.f, 100.f };

		std::vector<TextureRegion> expectedTilesTextureRegions = 
		{ 
			TextureRegion{ Vector2f{ 23.f}, Vector2f{ 5.45f } },
			TextureRegion{ Vector2f{ 433.2f}, Vector2f{ 0.45f } },
			TextureRegion{ Vector2f{ 23.21f}, Vector2f{ 5.35f } }
		};
		tileMap.setTilesTextureRegions(expectedTilesTextureRegions, textureSize);

		std::vector<TextureRegion> actualTilesTextureRegions = tileMap.getTilesTextureRegions();
		EXPECT_NE(expectedTilesTextureRegions, actualTilesTextureRegions);

		tileMap.clearTilesTextureRegions();
		actualTilesTextureRegions = tileMap.getTilesTextureRegions();
		EXPECT_TRUE(actualTilesTextureRegions.empty());
	}
}
