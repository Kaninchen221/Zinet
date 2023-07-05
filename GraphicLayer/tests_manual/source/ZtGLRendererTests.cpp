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
#include "Zinet/GraphicLayer/ZtGLMath.h"

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

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("RendererTests");

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

		typedef void(Renderer::* ExpectedFunctionDeclaration)(const DrawableObject&, RenderStates&);
		static_assert(zt::core::IsFunctionEqual<ExpectedFunctionDeclaration>(&Renderer::draw));
	};

	TEST_F(RendererTests, Draw)
	{
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
			TextureRegion textureRegion;
			textureRegion.size = Vector2f{ 512.f, 512.f };
			textureRegion.offset = Vector2f{ 512.f * i, 0.f };
			sprite->setTextureRegion(textureRegion, texture.getSize());

		}

		// RenderStates
		std::vector<RenderStates::Descriptor> descriptors;
		RenderStates::Descriptor descriptor;
		// MVP
		descriptor.binding = 0;
		descriptor.descriptorType = vk::DescriptorType::eUniformBuffer;
		descriptor.count = 1;
		descriptor.shaderType = ShaderType::Vertex;
		descriptors.push_back(descriptor);

		// Texture
		descriptor.binding = 1;
		descriptor.descriptorType = vk::DescriptorType::eCombinedImageSampler;
		descriptor.count = 1;
		descriptor.shaderType = ShaderType::Fragment;
		descriptors.push_back(descriptor);

		std::vector<RenderStates::Image> images;
		RenderStates::Image& imageRenderState = images.emplace_back(texture.createImageDrawInfo(sampler));
		imageRenderState.binding = 1;

		RenderStates renderStates
		{
			.shaders = shaders,
			.descriptors = descriptors,
			.images = images,
			.camera = camera,

		};

		TileMap tileMap;
		tileMap.setTilesCount({ 5, 4 });
		TextureRegion textureRegion;
		textureRegion.size = Vector2f{ 512.f, 512.f };
		textureRegion.offset = Vector2f{ 0.f, 0.f };
		tileMap.setTextureRegion(textureRegion, texture.getSize());

		zt::core::Clock clock;
		std::once_flag clockOnceFlag;

		bool drawSprites = true;
		float sliderMin = -30.f;
		float sliderMax = 30.f;
		float cameraFar = 300.f;
		std::string drawSpritesText = "Sprites";
		std::string drawTileMapText = "Tilemap";
		std::string ToggleButtonText = drawSpritesText;

		while (!rendererContext.getWindow().shouldBeClosed())
		{
			std::call_once(clockOnceFlag, [&clock]() { clock.start(); });

			imgui.update();

			// Imgui
			ImGui::NewFrame();

			ImGui::ShowDemoWindow();
			if(!ImGui::Begin("Main"))
				ImGui::End();

			if (ImGui::Button(ToggleButtonText.c_str()))
			{
				drawSprites = !drawSprites;
				if (drawSprites)
					ToggleButtonText = drawSpritesText;
				else
					ToggleButtonText = drawTileMapText;
			}

			if (drawSprites)
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
			}
			else // Tilemap
			{
				ImGui::SliderFloat("Camera 'Far'", &cameraFar, 10.f, 1000.f);
				camera.setFar(cameraFar);

				ImGui::SliderFloat("Min", &sliderMin, -1000.f, 0.f);

				ImGui::SliderFloat("Max", &sliderMax, 0.f, 1000.f);

				Transform transform = tileMap.getTransform();
				Vector3f position = transform.getTranslation();

				float rawPosition[3];
				Math::FromVector3fToCArray(position, rawPosition);
				std::string positionName = "Sprite position ";
				ImGui::SliderFloat3(positionName.c_str(), rawPosition, sliderMin, sliderMax);
				position = Math::FromCArrayToVector3f(rawPosition);
				transform.setTranslation(position);
				tileMap.setTransform(transform);
			}

			// Camera
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

			ImGui::End();

			ImGui::EndFrame();
			// End Imgui

			ImGui::Render();

			renderer.preDraw();

			if (drawSprites)
			{
				int counter = 0;
				for (Sprite& sprite : sprites)
				{
					renderStates.modelMatrix = sprite.getTransform().toMatrix();
					renderer.draw(sprite, renderStates);
					counter++;
				}
			}
			else
			{
				renderer.draw(tileMap, renderStates);
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