#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLSTBImage.h"
#include "Zinet/GraphicLayer/ZtGLMVP.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"
#include "Zinet/GraphicLayer/ZtGLDrawableObject.h"
#include "Zinet/GraphicLayer/ZtGLSprite.h"

#include "Zinet/Core/ZtClock.h"

#include <gtest/gtest.h>

#include <filesystem>
#include <vector>
#include <chrono>

namespace zt::gl::tests
{

	class RendererTests : public ::testing::Test
	{
	protected:

		inline static ConsoleLogger Logger = ConsoleLogger::Create("RendererTests");

		const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

		Renderer renderer;

		void createShaders();
		void createSTBImage();

		std::vector<Shader> shaders;
		Sampler sampler;
		STBImage stbImage;
		Texture texture;
	};

	TEST_F(RendererTests, Draw)
	{
		zt::gl::GLFW::UnhideWindow();
		typedef void(Renderer::* ExpectedFunctionDeclaration)(const DrawInfo&);
		using FunctionDeclaration = decltype(&Renderer::draw);

		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		renderer.initialize();

		createShaders();
		createSTBImage();

		// Create Sampler
		vk::SamplerCreateInfo samplerCreateInfo = sampler.createCreateInfo();
		sampler.create(renderer.getDevice(), samplerCreateInfo);

		// Create texture
		texture.create(stbImage, renderer);

		int count = 2;
		plf::colony<Sprite> sprites;
		sprites.reserve(count);
		for (size_t i = 0u; i < count; ++i)
		{
			auto sprite = sprites.emplace();
			sprite->create(renderer);
			sprite->createDrawInfo(shaders, texture, sampler);
		}

		zt::Clock clock;
		clock.start();

		while (!renderer.getWindow().shouldBeClosed())
		{
			//Logger->info("preDraw");
			renderer.preDraw();

			//Logger->info("Draw 0");
			auto sprite = sprites.begin();
			sprite->rotate();
			renderer.draw(sprite->getDrawInfo());

			//Logger->info("Draw 1");
			sprite = sprites.begin();
			sprite++;
			sprite->rotate2();
			renderer.draw(sprite->getDrawInfo());

			glfwPollEvents();

			//Logger->info("postDraw");
			renderer.postDraw();

			if (clock.getElapsedTime().getAsSeconds() > 4)
			{
				renderer.getWindow().requestCloseWindow();
			}
		}

		renderer.getQueue()->waitIdle();
		renderer.getDevice()->waitIdle();
	}

	void RendererTests::createSTBImage()
	{
		if (!stbImage.load((ContentPath / "texture.png").string()))
		{
			FAIL() << "Can't load texture image";
		}
	}

	void RendererTests::createShaders()
	{
		shaders.emplace_back();
		shaders[0].setType(ShaderType::Vertex);
		shaders[0].loadFromFile((ContentPath / "shader.vert").string());
		shaders[0].compile();

		shaders.emplace_back();
		shaders[1].setType(ShaderType::Fragment);
		shaders[1].loadFromFile((ContentPath / "shader.frag").string());
		shaders[1].compile();
	}

}