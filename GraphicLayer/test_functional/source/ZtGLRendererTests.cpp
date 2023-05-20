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
#include "Zinet/GraphicLayer/Imgui/ZtGLImgui.h"

#include "Zinet/Core/ZtClock.h"

#include <gtest/gtest.h>

#include <filesystem>
#include <vector>
#include <chrono>

// TODO Remove it after refactor
#include <imgui_impl_vulkan.h>
#include <imgui_impl_glfw.h>

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
		Camera camera;
		Imgui imgui;

	};

	TEST_F(RendererTests, Draw)
	{
		zt::gl::GLFW::UnhideWindow();
		typedef void(Renderer::* ExpectedFunctionDeclaration)(DrawableObject&, const Camera&);
		using FunctionDeclaration = decltype(&Renderer::draw);

		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		camera.setPosition({ 2.0f, 2.0f, 2.0f });

		renderer.initialize();

		imgui.preinit(renderer);
		imgui.init(renderer);

		createShaders();
		createSTBImage();

		// Create Sampler
		vk::SamplerCreateInfo samplerCreateInfo = sampler.createCreateInfo();
		sampler.create(renderer.getDevice(), samplerCreateInfo);

		// Create texture
		texture.create(stbImage, renderer);

		int count = 3;
		plf::colony<Sprite> sprites;
		sprites.reserve(count);
		for (size_t i = 0u; i < count; ++i)
		{
			auto sprite = sprites.emplace();
			sprite->create(renderer);
			TextureRegion textureRegion;
			textureRegion.size = Vector2f{ 512.f, 512.f };
			textureRegion.offset = Vector2f{ 512.f * i, 0.f };
			sprite->setTextureRegion(textureRegion);
			sprite->createDrawInfo(shaders, texture, sampler);

		}

		zt::Clock clock;
		std::once_flag clockOnceFlag;

		float counter = 1.f;
		while (!renderer.getWindow().shouldBeClosed())
		{
			std::call_once(clockOnceFlag, [&clock]() { clock.start(); });

			imgui.update();

			ImGui::NewFrame();

			ImGui::ShowDemoWindow();

			ImGui::EndFrame();

			ImGui::Render();

			renderer.preDraw();

			float index = 1.f;
			float time = static_cast<float>(glfwGetTime());
			for (Sprite& sprite : sprites)
			{
				renderer.draw(sprite, camera);
				Transform transform = sprite.getTransform();
				float rotation = 360.f / sprites.size() * index * time;
				transform.setRotation({ 0.f, 0.f, rotation });
				sprite.setTransform(transform);
				counter += 1.f;
				index += 1.f;
			}

			glfwPollEvents();

			imgui.draw(renderer.getDrawCommandBuffer());

			renderer.postDraw();

			if (clock.getElapsedTime().getAsSeconds() > 40)
			{
				renderer.getWindow().requestCloseWindow();
			}
		}

		renderer.getQueue()->waitIdle();
		renderer.getDevice()->waitIdle();
	}

	void RendererTests::createSTBImage()
	{
		if (!stbImage.load((ContentPath / "test_texture.png").string()))
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