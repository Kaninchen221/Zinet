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

#include <glm/gtc/type_ptr.hpp>

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
		plf::colony<Sprite> sprites;

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

		while (!renderer.getWindow().shouldBeClosed())
		{
			std::call_once(clockOnceFlag, [&clock]() { clock.start(); });

			imgui.update();

			// Imgui
			ImGui::NewFrame();

			ImGui::ShowDemoWindow();
			if(!ImGui::Begin("Main"))
				ImGui::End();

			{
				float index = 1.f;
				for (Sprite& sprite : sprites)
				{
					Transform transform = sprite.getTransform();
					Vector3f position = transform.getTranslation();
					Vector3f rotation = transform.getRotation();
					Vector3f scale = transform.getScale();

					float rawPosition[3];
					Math::FromVector3fToCArray(position, rawPosition);
					std::string positionName = std::string{ "Sprite position " } + std::to_string(static_cast<int>(index));
					ImGui::SliderFloat3(positionName.c_str(), rawPosition, -1.0f, 1.0f);
					
					float rawRotation[3];
					Math::FromVector3fToCArray(rotation, rawRotation);
					std::string rotationName = std::string{ "Sprite rotation " } + std::to_string(static_cast<int>(index));
					ImGui::SliderFloat3(rotationName.c_str(), rawRotation, 0.f, 360.0f);

					float rawScale[3];
					Math::FromVector3fToCArray(scale, rawScale);
					std::string scaleName = std::string{ "Sprite scale " } + std::to_string(static_cast<int>(index));
					ImGui::SliderFloat3(scaleName.c_str(), rawScale, 0.01f, 10.0f);

					ImGui::Spacing();

					position = Math::FromCArrayToVector3f(rawPosition);
					rotation = Math::FromCArrayToVector3f(rawRotation);
					scale = Math::FromCArrayToVector3f(rawScale);
					transform.setTranslation(position);
					transform.setRotation(rotation);
					transform.setScale(scale);
					sprite.setTransform(transform);
					index += 1.f;
				}
			}

			ImGui::End();

			ImGui::EndFrame();
			// End Imgui

			ImGui::Render();

			renderer.preDraw();

			for (Sprite& sprite : sprites)
			{
				renderer.draw(sprite, camera);
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