
#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLSTBImage.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"
#include "Zinet/GraphicLayer/Imgui/ZtGLImgui.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLSprite.h"
#include "Zinet/GraphicLayer/ZtGLTileMap.h"
#include "Zinet/GraphicLayer/ZtGLMath.h"

#include "Zinet/Core/ZtTypeTraits.h"
#include "Zinet/Core/ZtLogger.h"
#include "Zinet/Core/ZtClock.h"

#include <filesystem>
#include <vector>
#include <chrono>

#include <glm/gtc/type_ptr.hpp>

#include <imgui_impl_vulkan.h>
#include <imgui_impl_glfw.h>

class RendererTest
{
protected:

	inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("RendererTests");

	const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

public:

	void run();

protected:

	zt::gl::Renderer renderer;

	void createShaders();
	void createSTBImage();

	std::vector<zt::gl::Shader> shaders;
	zt::gl::Sampler sampler;
	zt::gl::STBImage stbImage;
	zt::gl::Texture texture;
	zt::gl::Camera camera;
	zt::gl::Imgui imgui;

};

void RendererTest::createShaders()
{
	shaders.emplace_back();
	shaders[0].setType(zt::gl::ShaderType::Vertex);
	shaders[0].loadFromFile((ContentPath / "shader.vert").string());
	shaders[0].compile();

	shaders.emplace_back();
	shaders[1].setType(zt::gl::ShaderType::Fragment);
	shaders[1].loadFromFile((ContentPath / "shader.frag").string());
	shaders[1].compile();
}

void RendererTest::createSTBImage()
{
	if (!stbImage.load((ContentPath / "texture.jpg").string()))
	{
		Logger->error("Can't create image");
	}
}

void RendererTest::run()
{
	zt::gl::GLFW::UnhideWindow();

	camera.setPosition({ 0.0f, 0.0f, -4.0f });

	renderer.initialize();

	zt::gl::RendererContext& rendererContext = renderer.getRendererContext();
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
	plf::colony<zt::gl::Sprite> sprites;
	sprites.reserve(count);
	for (size_t i = 0u; i < count; ++i)
	{
		auto sprite = sprites.emplace();
		zt::gl::TextureRegion textureRegion;
		textureRegion.size = zt::gl::Vector2f{ 512.f, 512.f };
		textureRegion.offset = zt::gl::Vector2f{ 512.f * i, 0.f };
		sprite->setTextureRegion(textureRegion, texture.getSize());

	}

	// RenderStates
	std::vector<zt::gl::RenderStates::Descriptor> descriptors;
	zt::gl::RenderStates::Descriptor descriptor;
	// MVP
	descriptor.binding = 0;
	descriptor.descriptorType = vk::DescriptorType::eUniformBuffer;
	descriptor.count = 1;
	descriptor.shaderType = zt::gl::ShaderType::Vertex;
	descriptors.push_back(descriptor);

	// Texture
	descriptor.binding = 1;
	descriptor.descriptorType = vk::DescriptorType::eCombinedImageSampler;
	descriptor.count = 1;
	descriptor.shaderType = zt::gl::ShaderType::Fragment;
	descriptors.push_back(descriptor);

	std::vector<zt::gl::RenderStates::Image> images;
	zt::gl::RenderStates::Image& imageRenderState = images.emplace_back(texture.createImageDrawInfo(sampler));
	imageRenderState.binding = 1;

	zt::gl::RenderStates renderStates
	{
		.shaders = shaders,
		.descriptors = descriptors,
		.images = images,
		.camera = camera,

	};

	zt::gl::TileMap tileMap;
	tileMap.setTilesCount({ 5, 4 });
	zt::gl::TextureRegion textureRegion;
	textureRegion.size = zt::gl::Vector2f{ 512.f, 512.f };
	textureRegion.offset = zt::gl::Vector2f{ 0.f, 0.f };
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
			for (zt::gl::Sprite& sprite : sprites)
			{
				zt::gl::Transform transform = sprite.getTransform();
				zt::gl::Vector3f position = transform.getTranslation();
				zt::gl::Vector3f rotation = transform.getRotation();
				zt::gl::Vector3f scale = transform.getScale();

				float rawPosition[3];
				zt::gl::Math::FromVector3fToCArray(position, rawPosition);
				std::string positionName = std::string{ "Sprite position " } + std::to_string(static_cast<int>(index));
				ImGui::SliderFloat3(positionName.c_str(), rawPosition, -1.0f, 1.0f);

				float rawRotation[3];
				zt::gl::Math::FromVector3fToCArray(rotation, rawRotation);
				std::string rotationName = std::string{ "Sprite rotation " } + std::to_string(static_cast<int>(index));
				ImGui::SliderFloat3(rotationName.c_str(), rawRotation, 0.f, 560.0f);

				float rawScale[3];
				zt::gl::Math::FromVector3fToCArray(scale, rawScale);
				std::string scaleName = std::string{ "Sprite scale " } + std::to_string(static_cast<int>(index));
				ImGui::SliderFloat3(scaleName.c_str(), rawScale, 0.01f, 10.0f);

				ImGui::Spacing();

				position = zt::gl::Math::FromCArrayToVector3f(rawPosition);
				rotation = zt::gl::Math::FromCArrayToVector3f(rawRotation);
				scale = zt::gl::Math::FromCArrayToVector3f(rawScale);
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

			zt::gl::Transform transform = tileMap.getTransform();
			zt::gl::Vector3f position = transform.getTranslation();

			float rawPosition[3];
			zt::gl::Math::FromVector3fToCArray(position, rawPosition);
			std::string positionName = "Sprite position ";
			ImGui::SliderFloat3(positionName.c_str(), rawPosition, sliderMin, sliderMax);
			position = zt::gl::Math::FromCArrayToVector3f(rawPosition);
			transform.setTranslation(position);
			tileMap.setTransform(transform);
		}

		// Camera
		zt::gl::Vector3f cameraPos = camera.getPosition();
		float rawCameraPos[3];
		zt::gl::Math::FromVector3fToCArray(cameraPos, rawCameraPos);
		std::string posName = std::string{ "Camera pos " };
		ImGui::SliderFloat3(posName.c_str(), rawCameraPos, -10.00f, 10.0f);
		cameraPos = zt::gl::Math::FromCArrayToVector3f(rawCameraPos);
		camera.setPosition(cameraPos);

		zt::gl::Vector3f cameraTarget = camera.getTarget();
		float rawCameraTarget[3];
		zt::gl::Math::FromVector3fToCArray(cameraTarget, rawCameraTarget);
		std::string targetName = std::string{ "Camera target " };
		ImGui::SliderFloat3(targetName.c_str(), rawCameraTarget, -5.00f, 5.0f);
		cameraTarget = zt::gl::Math::FromCArrayToVector3f(rawCameraTarget);
		camera.setTarget(cameraTarget);

		ImGui::EndFrame();
		// End Imgui

		ImGui::Render();

		renderer.preDraw();

		if (drawSprites)
		{
			int counter = 0;
			for (zt::gl::Sprite& sprite : sprites)
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

int main()
{
	RendererTest test;
	test.run();

    return 0;
}