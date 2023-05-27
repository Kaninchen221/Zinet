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
#include "Zinet/GraphicLayer/ZtGLTileMap.h"

#include "Zinet/Core/ZtClock.h"
#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

#include <filesystem>
#include <vector>
#include <chrono>

#include <glm/gtc/type_ptr.hpp>

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

	
	TEST_F(RendererTests, DrawSprite)
	{
		typedef void(Renderer::* ExpectedFunctionDeclaration)(DrawableObject&, const Camera&);
		IsFunctionEqual<ExpectedFunctionDeclaration>(&Renderer::draw);

		zt::gl::GLFW::UnhideWindow();

		camera.setPosition({ 0.0f, 0.0f, -4.0f });

		renderer.initialize();

		RendererContext& rendererContext = renderer.getRendererContext();
		imgui.preinit(rendererContext);
		imgui.init(rendererContext);

		createShaders();
		createSTBImage();

		// Create Sampler
		vk::SamplerCreateInfo samplerCreateInfo = sampler.createCreateInfo();
		sampler.create(rendererContext.getDevice(), samplerCreateInfo);

		// Create texture
		texture.create(stbImage, rendererContext);

		int count = 3;
		plf::colony<Sprite> sprites;
		sprites.reserve(count);
		for (size_t i = 0u; i < count; ++i)
		{
			auto sprite = sprites.emplace();
			sprite->create(rendererContext);
			TextureRegion textureRegion;
			textureRegion.size = Vector2f{ 512.f, 512.f };
			textureRegion.offset = Vector2f{ 512.f * i, 0.f };
			sprite->setTextureRegion(textureRegion);
			sprite->createDrawInfo(shaders, texture, sampler);

		}

		zt::Clock clock;
		std::once_flag clockOnceFlag;

		while (!rendererContext.getWindow().shouldBeClosed())
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
					ImGui::SliderFloat3(rotationName.c_str(), rawRotation, 0.f, 560.0f);

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

				Vector3f cameraPos = camera.getPosition();
				float rawCameraPos[3];
				Math::FromVector3fToCArray(cameraPos, rawCameraPos);
				std::string posName = std::string{ "Camera pos " };
				ImGui::SliderFloat3(posName.c_str(), rawCameraPos, -10.00f, 10.0f);
				cameraPos = Math::FromCArrayToVector3f(rawCameraPos);
				camera.setPosition(cameraPos);

				Vector3f cameraTarget = camera.getTarget();
				float rawCameraTarget[3];
				Math::FromVector3fToCArray(cameraTarget, rawCameraTarget);
				std::string targetName = std::string{ "Camera target " };
				ImGui::SliderFloat3(targetName.c_str(), rawCameraTarget, -5.00f, 5.0f);
				cameraTarget = Math::FromCArrayToVector3f(rawCameraTarget);
				camera.setTarget(cameraTarget);

				//cameraTarget = cameraPos;
				//cameraTarget.z = 0;
				//camera.setTarget(cameraTarget);
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

			if (clock.getElapsedTime().getAsSeconds() > 10000)
			{
				rendererContext.getWindow().requestCloseWindow();
			}
		}

		rendererContext.getQueue()->waitIdle();
		rendererContext.getDevice()->waitIdle();
	}

	TEST_F(RendererTests, DrawTileMap)
	{
		zt::gl::GLFW::UnhideWindow();

		camera.setPosition({ 0.0f, 0.0f, -5.0f });

		renderer.initialize();

		RendererContext& rendererContext = renderer.getRendererContext();

		createShaders();
		createSTBImage();

		// Create Sampler
		vk::SamplerCreateInfo samplerCreateInfo = sampler.createCreateInfo();
		sampler.create(rendererContext.getDevice(), samplerCreateInfo);

		// Create texture
		texture.create(stbImage, rendererContext);

		TileMap tileMap;
		tileMap.create(rendererContext);
		TextureRegion textureRegion;
		textureRegion.size = Vector2f{ 512.f, 512.f };
		textureRegion.offset = Vector2f{ 0.f, 0.f };
		tileMap.setTextureRegion(textureRegion);
		tileMap.createDrawInfo(shaders, texture, sampler);

		Transform transform = tileMap.getTransform();
		camera.setTarget(transform.getTranslation());

		zt::Clock clock;
		std::once_flag clockOnceFlag;

		while (!rendererContext.getWindow().shouldBeClosed())
		{
			std::call_once(clockOnceFlag, [&clock]() { clock.start(); });

			renderer.preDraw();

			//Transform transform = tileMap.getTransform();
			//Vector3f position = transform.getTranslation();
			//Vector3f rotation = transform.getRotation();
			//Vector3f scale = transform.getScale();
			//
			//transform.setTranslation(position);
			//transform.setRotation(rotation);
			//transform.setScale(scale);
			//tileMap.setTransform(transform);

			renderer.draw(tileMap, camera);

			glfwPollEvents();

			renderer.postDraw();

			if (clock.getElapsedTime().getAsSeconds() > 4000)
			{
				rendererContext.getWindow().requestCloseWindow();
			}
		}

		rendererContext.getQueue()->waitIdle();
		rendererContext.getDevice()->waitIdle();
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