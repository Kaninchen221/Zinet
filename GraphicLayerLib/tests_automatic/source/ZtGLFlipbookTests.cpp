#pragma once

#include "Zinet/GraphicLayer/ZtGLFlipbook.h"
#include "Zinet/GraphicLayer/ZtGLDrawableBase.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"
#include "Zinet/GraphicLayer/ZtGLSampler.h"
#include "Zinet/GraphicLayer/ZtGLShader.h"

#include "Zinet/Window/ZtGLFW.h"

#include "Zinet/Core/ZtTypeTraits.h"
#include "Zinet/Core/ZtTime.h"

#include <gtest/gtest.h>

#include <filesystem>

namespace zt::gl::tests
{

	class FlipbookTests : public ::testing::Test
	{
	protected:

		const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

		Renderer renderer;
		Flipbook flipbook;
		Texture texture;
		Sampler sampler;
		std::vector<Shader> shaders;
		STBImage stbImage;

		static_assert(std::is_base_of_v<Drawable2DBase, Flipbook>);
		static_assert(std::is_default_constructible_v<Flipbook>);

		static_assert(std::is_copy_constructible_v<Flipbook>);
		static_assert(std::is_copy_assignable_v<Flipbook>);

		static_assert(std::is_move_constructible_v<Flipbook>);
		static_assert(std::is_move_assignable_v<Flipbook>);

		void SetUp() override
		{
			wd::GLFW::Init(false);
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
				rendererContext, commandBuffer, Vector2ui{ 640u, 640u }, false, vk::Format::eR8G8B8A8Srgb
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

	TEST_F(FlipbookTests, CreateDrawInfo)
	{
		DrawInfo drawInfo = flipbook.createDrawInfo(renderer.getRendererContext());

		EXPECT_TRUE(drawInfo.vertexBuffer.isValid());
		EXPECT_TRUE(drawInfo.indexBuffer.isValid());
		EXPECT_FALSE(drawInfo.indices.empty());
		EXPECT_FALSE(drawInfo.uniformBuffers.empty());
	}

	TEST_F(FlipbookTests, Update)
	{
		std::vector<Flipbook::Frame> expectedFrames;
		Flipbook::Frame frame;
		frame.time = zt::core::Time::FromSeconds(1.f);
		expectedFrames.push_back(frame);
		expectedFrames.push_back(frame);
		flipbook.setFrames(expectedFrames);

		zt::core::Time elapsedTime = zt::core::Time::FromSeconds(0.f);
		size_t currentFrameIndex = flipbook.getCurrentFrameIndex();
		EXPECT_EQ(currentFrameIndex, 0u);

		// Frame 0
		bool updated = flipbook.update(elapsedTime);
		ASSERT_FALSE(updated);
		currentFrameIndex = flipbook.getCurrentFrameIndex();
		EXPECT_EQ(currentFrameIndex, 0u);

		// Frame 0
		flipbook.play();
		elapsedTime = zt::core::Time::FromSeconds(0.001f);
		updated = flipbook.update(elapsedTime);
		ASSERT_TRUE(updated);
		currentFrameIndex = flipbook.getCurrentFrameIndex();
		EXPECT_EQ(currentFrameIndex, 0u);

		// Frame 1
		elapsedTime = zt::core::Time::FromSeconds(1.001f);
		updated = flipbook.update(elapsedTime);
		ASSERT_TRUE(updated);
		currentFrameIndex = flipbook.getCurrentFrameIndex();
		EXPECT_EQ(currentFrameIndex, 1u);

		// Frame 0
		elapsedTime = zt::core::Time::FromSeconds(2.01f);
		updated = flipbook.update(elapsedTime);
		ASSERT_TRUE(updated);
		currentFrameIndex = flipbook.getCurrentFrameIndex();
		EXPECT_EQ(currentFrameIndex, 0u);
	}

	class FlipbookSimpleTests : public ::testing::Test
	{
	protected:

		Flipbook flipbook;
	};

	TEST_F(FlipbookSimpleTests, GetSetTransform)
	{
		typedef const Transform& (Flipbook::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Flipbook::getTransform));

		Transform expected;
		expected.setTranslation({ 12.4f, 3.f, 1.f });
		expected.setScale({ 112.4f, 3.42f, 11.f });
		expected.setRotation({ 1.41f, 0.412f, 1.212f });
		flipbook.setTransform(expected);

		const Transform& actual = flipbook.getTransform();
		ASSERT_EQ(expected, actual);
	}

	TEST_F(FlipbookSimpleTests, Frame)
	{
		Flipbook::Frame frame;

		static_assert(std::is_same_v<decltype(frame.time), zt::core::Time>);
		static_assert(std::is_same_v<decltype(frame.shaderTextureRegion), TextureRegion>);
	}

	TEST_F(FlipbookSimpleTests, GetSetFrames)
	{
		typedef const std::vector<Flipbook::Frame>& (Flipbook::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Flipbook::getFrames));

		std::vector<Flipbook::Frame> expectedFrames;
		Flipbook::Frame frame;
		frame.time = zt::core::Time{ 232.f };
		expectedFrames.push_back(frame);
		frame.time = zt::core::Time{ 22.42f };
		expectedFrames.push_back(frame);
		flipbook.setFrames(expectedFrames);
		
		const std::vector<Flipbook::Frame>& actualFrames = flipbook.getFrames();
		ASSERT_EQ(expectedFrames, actualFrames);
	}

	TEST_F(FlipbookSimpleTests, GetCurrentFrameIndex)
	{
		size_t currentIndex = flipbook.getCurrentFrameIndex();
		ASSERT_EQ(currentIndex, 0u);
	}

	TEST_F(FlipbookSimpleTests, State)
	{
		Flipbook::State expectedState = Flipbook::State::Pause;
		Flipbook::State actualState = flipbook.getCurrentState();
		ASSERT_EQ(expectedState, actualState);
	}

	TEST_F(FlipbookSimpleTests, Play)
	{
		flipbook.play();

		Flipbook::State expectedState = Flipbook::State::Playing;
		Flipbook::State actualState = flipbook.getCurrentState();
		ASSERT_EQ(expectedState, actualState);
	}

	TEST_F(FlipbookSimpleTests, Pause)
	{
		flipbook.play();
		flipbook.pause();

		Flipbook::State expectedState = Flipbook::State::Pause;
		Flipbook::State actualState = flipbook.getCurrentState();
		ASSERT_EQ(expectedState, actualState);
	}

	TEST_F(FlipbookSimpleTests, CreateRenderStatesDescriptors)
	{
		std::vector<RenderStates::Descriptor> descriptors = flipbook.createRenderStatesDescriptors();
		ASSERT_FALSE(descriptors.empty());
	}
}
