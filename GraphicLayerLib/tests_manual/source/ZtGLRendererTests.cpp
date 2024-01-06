#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderer.hpp"
#include "Zinet/GraphicLayer/ZtGLVertex.hpp"
#include "Zinet/GraphicLayer/ZtGLImage.hpp"
#include "Zinet/GraphicLayer/ZtGLSTBImage.hpp"
#include "Zinet/GraphicLayer/ZtGLMVP.hpp"
#include "Zinet/GraphicLayer/ZtGLTexture.hpp"
#include "Zinet/GraphicLayer/ZtGLDrawableBase.hpp"
#include "Zinet/GraphicLayer/ZtGLSprite.hpp"
#include "Zinet/GraphicLayer/Imgui/ZtGLImgui.hpp"
#include "Zinet/GraphicLayer/ZtGLTileMap.hpp"
#include "Zinet/GraphicLayer/ZtGLUtilities.hpp"
#include "Zinet/GraphicLayer/ZtGLFlipbook.hpp"
#include "Zinet/GraphicLayer/ZtGLShape2D.hpp"

#include "Zinet/Core/ZtClock.hpp"
#include "Zinet/Core/ZtTypeTraits.hpp"

#include "Zinet/Window/ZtGLFW.hpp"
#include "Zinet/Math/ZtMath.hpp"

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
	public:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("RendererTests");

		const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

		Renderer renderer;

		void createShaders(std::string vertexShaderFileName = "shader.vert", std::string fragmentShaderFileName = "shader.frag");
		void createFlipbookShaders();
		void createInstanceRenderingShaders();
		void createSTBImage();
		void createTexture();
		void createSampler();

		std::vector<Shader> shaders;
		Sampler sampler;
		STBImage stbImage;
		Texture texture;
		Texture mipmapTexture;
		Camera camera;
		Imgui imgui;

		void imguiCamera();
		void imguiDrawable2DBase(Drawable2DBase& drawable2D, size_t index);
		void imguiSprite(Sprite& sprite, size_t index);
		void imguiTileMap(TileMap& tileMap, size_t index);
		void imguiFlipbook(Flipbook& flipbook, size_t index);
		void imguiRecompileShaders(auto callable, auto... args);

		const bool skipShape2D = false;
		const bool skipSprites = false;
		const bool skipInstancedRendering = false;
		const bool skipFlipbook = false;
	};

	TEST_F(RendererTests, Shape2D)
	{
		if (skipShape2D)
			FAIL() << "";

		wd::GLFW::UnhideWindow();

		camera.setPosition({ 0.0f, 0.0f, -4.0f });

		renderer.initialize();

		RendererContext& rendererContext = renderer.getRendererContext();
		imgui.preinit(rendererContext);
		imgui.init(rendererContext);

		createShaders("shape2D.vert", "shape2D.frag");

		Shape2D firstShape2D;
		firstShape2D.setColor(Vector4f{ 1.f, 0.f, 0.f, 0.5f });
		auto firstShapeTransform = firstShape2D.getTransform();
		firstShapeTransform.setTranslation({ -0.5f, 0.5f, 0.f });
		firstShape2D.setTransform(firstShapeTransform);

		Shape2D secondShape2D;
		secondShape2D.setColor(Vector4f{ 0.f, 1.f, 0.f, 0.5f });

		// RenderStates
		std::vector<RenderStates::Descriptor> descriptors = firstShape2D.createRenderStatesDescriptors();

		RenderStates renderStates
		{
			.shaders = shaders,
			.descriptors = descriptors
		};

		while (!rendererContext.getWindow().shouldBeClosed())
		{
			imgui.update();

			// Imgui
			ImGui::NewFrame();

			ImGui::ShowDemoWindow();
			if (!ImGui::Begin("Main"))
				ImGui::End();

			imguiRecompileShaders(std::bind(&RendererTests::createShaders, this, "shape2D.vert", "shape2D.frag"));

			imguiCamera();

			imguiDrawable2DBase(firstShape2D, 0);
			imguiDrawable2DBase(secondShape2D, 1);

			ImGui::End();

			ImGui::EndFrame();
			// End Imgui

			ImGui::Render();

			renderer.preDraw();

			{ // firstShape2D
				auto modelMatrix = firstShape2D.getTransform().toMatrix();
				auto viewMatrix = camera.viewMatrix();
				auto projectionMatrix = camera.projectionMatrix();
				renderStates.mvp = MVP{ modelMatrix, viewMatrix, projectionMatrix };
				renderer.draw<Vertex>(firstShape2D.createDrawInfo(rendererContext), renderStates);
			}

			{ // secondShape2D
				auto modelMatrix = secondShape2D.getTransform().toMatrix();
				auto viewMatrix = camera.viewMatrix();
				auto projectionMatrix = camera.projectionMatrix();
				renderStates.mvp = MVP{ modelMatrix, viewMatrix, projectionMatrix };
				renderer.draw<Vertex>(secondShape2D.createDrawInfo(rendererContext), renderStates);
			}

			glfwPollEvents();

			imgui.draw(renderer.getDrawCommandBuffer());

			renderer.postDraw();
		}

		rendererContext.getQueue()->waitIdle();
		rendererContext.getDevice()->waitIdle();
	}
	
	TEST_F(RendererTests, Sprites)
	{
		if (skipSprites)
			FAIL() << "";

		wd::GLFW::UnhideWindow();

		camera.setPosition({ 0.0f, 0.0f, -4.0f });

		renderer.initialize();

		RendererContext& rendererContext = renderer.getRendererContext();
		imgui.preinit(rendererContext);
		imgui.init(rendererContext);

		createShaders();
		createSTBImage();
		createTexture();
		createSampler();

		int count = 3;
		plf::colony<Sprite> sprites;
		sprites.reserve(count);
		for (size_t i = 0u; i < count; ++i)
		{
			auto sprite = sprites.emplace();
			TextureRegion textureRegion;
			textureRegion.size = mipmapTexture.getSize();
			textureRegion.offset = Vector2f{ 0.f, 0.f };
			sprite->setTextureRegion(textureRegion, texture.getSize());

		}

		// RenderStates
		std::vector<RenderStates::Descriptor> descriptors = sprites.begin()->createRenderStatesDescriptors();

		auto textures = std::vector{ std::cref(mipmapTexture) };
		auto samplers = std::vector{ std::cref(sampler) };
		auto bindings = std::vector<size_t>{ 1u };
		std::vector<RenderStates::Image> images = sprites.begin()->createRenderStatesImages(textures, samplers, bindings);

		RenderStates renderStates
		{
			.shaders = shaders,
			.descriptors = descriptors,
			.images = images
		};

		while (!rendererContext.getWindow().shouldBeClosed())
		{
			imgui.update();

			// Imgui
			ImGui::NewFrame();

			ImGui::ShowDemoWindow();
			if(!ImGui::Begin("Main"))
				ImGui::End();

			imguiRecompileShaders(std::bind(&RendererTests::createShaders, this, "shader.vert", "shader.frag"));

			size_t index = 1u;
			for (Sprite& sprite : sprites)
			{
				imguiSprite(sprite, index);
				index++;
			}

			imguiCamera();

			ImGui::End();

			ImGui::EndFrame();
			// End Imgui

			ImGui::Render();

			renderer.preDraw();

			int counter = 0;
			for (Sprite& sprite : sprites)
			{
				auto modelMatrix = sprite.getTransform().toMatrix();
				auto viewMatrix = camera.viewMatrix();
				auto projectionMatrix = camera.projectionMatrix();
				renderStates.mvp = MVP{ modelMatrix, viewMatrix, projectionMatrix };
				renderer.draw<Vertex>(sprite.createDrawInfo(rendererContext), renderStates);
				counter++;
			}

			glfwPollEvents();

			imgui.draw(renderer.getDrawCommandBuffer());

			renderer.postDraw();
		}

		rendererContext.getQueue()->waitIdle();
		rendererContext.getDevice()->waitIdle();
	}

	TEST_F(RendererTests, InstancedRenderingAkaDrawTilemap)
	{
		if (skipInstancedRendering)
			FAIL() << "";

		wd::GLFW::UnhideWindow();

		camera.setPosition({ 0.0f, 0.0f, -30.0f });
		camera.setFar(1000.f);

		renderer.initialize();

		RendererContext& rendererContext = renderer.getRendererContext();
		imgui.preinit(rendererContext);
		imgui.init(rendererContext);

		createInstanceRenderingShaders();
		createSTBImage();
		createTexture();
		createSampler();

		TileMap tileMap;
		TextureRegion textureRegion;
		textureRegion.size = Vector2f{ 512.f, 512.f };
		textureRegion.offset = Vector2f{ 0.f, 0.f };
		tileMap.setDefaultShaderTextureRegion(textureRegion, texture.getSize());
		tileMap.setTilesTextureRegions({ textureRegion }, texture.getSize());
		tileMap.setTilesCount({ 33u, 7u });

		// RenderStates
		std::vector<RenderStates::Descriptor> descriptors = tileMap.createRenderStatesDescriptors();

		auto textures = std::vector{ std::cref(mipmapTexture) };
		auto samplers = std::vector{ std::cref(sampler) };
		auto bindings = std::vector<size_t>{ 1u };
		std::vector<RenderStates::Image> images = tileMap.createRenderStatesImages(textures, samplers, bindings);

		RenderStates renderStates
		{
			.shaders = shaders,
			.descriptors = descriptors,
			.images = images
		};

		while (!rendererContext.getWindow().shouldBeClosed())
		{
			imgui.update();

			ImGui::NewFrame();

			ImGui::ShowDemoWindow();
			if (!ImGui::Begin("Main"))
				ImGui::End();

			imguiRecompileShaders(std::bind(&RendererTests::createShaders, this, "shader.vert", "shader.frag"));

			imguiTileMap(tileMap, 0u);

			imguiCamera();

			ImGui::End();

			ImGui::EndFrame();

			ImGui::Render();

			renderer.preDraw();

			{ // Draw tileMap
				auto modelMatrix = tileMap.getTransform().toMatrix();
				auto viewMatrix = camera.viewMatrix();
				auto projectionMatrix = camera.projectionMatrix();
				renderStates.mvp = MVP{ modelMatrix, viewMatrix, projectionMatrix };
				renderer.draw<Vertex>(tileMap.createDrawInfo(rendererContext), renderStates);
			}

			glfwPollEvents();

			imgui.draw(renderer.getDrawCommandBuffer());

			renderer.postDraw();
		}

		rendererContext.getQueue()->waitIdle();
		rendererContext.getDevice()->waitIdle();
	}

	TEST_F(RendererTests, DrawFlipbook)
	{
		if (skipFlipbook)
			FAIL() << "";

		wd::GLFW::UnhideWindow();

		camera.setPosition({ 0.0f, 0.0f, -30.0f });
		camera.setFar(1000.f);

		renderer.initialize();

		RendererContext& rendererContext = renderer.getRendererContext();
		imgui.preinit(rendererContext);
		imgui.init(rendererContext);

		createFlipbookShaders();
		createSTBImage();
		createTexture();
		createSampler();

		// Flipbook
		Flipbook flipbook;
		TextureRegion textureRegion;
		textureRegion.size = Vector2f{ 512.f, 512.f };
		textureRegion.offset = Vector2f{ 0.f, 0.f };

		std::vector<Flipbook::Frame> frames;
		for (size_t index = 0u; index < 4u; ++index)
		{
			Flipbook::Frame frame;
			frame.time = zt::core::Time::FromSeconds(index + 1.0f);
			frame.shaderTextureRegion = textureRegion.toShaderTextureRegion(texture.getSize());
			frames.push_back(frame);
			textureRegion.offset.x += 512.f;
		}

		flipbook.setFrames(frames);

		std::vector<RenderStates::Descriptor> descriptors = flipbook.createRenderStatesDescriptors();

		auto textures = std::vector{ std::cref(mipmapTexture) };
		auto samplers = std::vector{ std::cref(sampler) };
		auto bindings = std::vector<size_t>{ 1u };
		std::vector<RenderStates::Image> images = flipbook.createRenderStatesImages(textures, samplers, bindings);

		RenderStates renderStates
		{
			.shaders = shaders,
			.descriptors = descriptors,
			.images = images
		};

		zt::core::Clock clock;
		clock.start();
		flipbook.play();
		flipbook.update(clock.restart());
		while (!rendererContext.getWindow().shouldBeClosed())
		{
			imgui.update();

			ImGui::NewFrame();

			ImGui::ShowDemoWindow();
			if (!ImGui::Begin("Main"))
				ImGui::End();

			imguiRecompileShaders(std::bind(&RendererTests::createFlipbookShaders, this));

			imguiFlipbook(flipbook, 0u);

			imguiCamera();

			ImGui::End();

			ImGui::EndFrame();

			ImGui::Render();

			renderer.preDraw();

			{ // Draw flipbook
				flipbook.update(clock.restart());
				auto modelMatrix = flipbook.getTransform().toMatrix();
				auto viewMatrix = camera.viewMatrix();
				auto projectionMatrix = camera.projectionMatrix();
				renderStates.mvp = MVP{ modelMatrix, viewMatrix, projectionMatrix };
				auto drawInfo = flipbook.createDrawInfo(rendererContext);
				flipbook.updateStorageBuffers(drawInfo.storageBuffers);
				renderer.draw<Vertex>(std::move(drawInfo), renderStates);
			}

			glfwPollEvents();

			imgui.draw(renderer.getDrawCommandBuffer());

			renderer.postDraw();
		}

		rendererContext.getQueue()->waitIdle();
		rendererContext.getDevice()->waitIdle();
	}
	
	void RendererTests::createSTBImage()
	{
		if (!stbImage.load((ContentPath / "test_texture.png").string()))
		//if (!stbImage.load((ContentPath / "texture.jpg").string()))
		{
			FAIL() << "Can't load texture image";
		}
	}

	void RendererTests::createShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName)
	{
		shaders.clear();

		shaders.emplace_back();
		shaders[0].setType(ShaderType::Vertex);
		shaders[0].loadFromFile((ContentPath / vertexShaderFileName).string());
		shaders[0].compile();

		shaders.emplace_back();
		shaders[1].setType(ShaderType::Fragment);
		shaders[1].loadFromFile((ContentPath / fragmentShaderFileName).string());
		shaders[1].compile();
	}

	void RendererTests::createFlipbookShaders()
	{
		shaders.clear();

		shaders.emplace_back();
		shaders[0].setType(ShaderType::Vertex);
		shaders[0].loadFromFile((ContentPath / "flipbookShader.vert").string());
		shaders[0].compile();

		shaders.emplace_back();
		shaders[1].setType(ShaderType::Fragment);
		shaders[1].loadFromFile((ContentPath / "shader.frag").string());
		shaders[1].compile();
	}

	void RendererTests::createInstanceRenderingShaders()
	{
		shaders.clear();

		shaders.emplace_back();
		shaders[0].setType(ShaderType::Vertex);
		shaders[0].loadFromFile((ContentPath / "instancedRenderingShader.vert").string());
		shaders[0].compile();

		shaders.emplace_back();
		shaders[1].setType(ShaderType::Fragment);
		shaders[1].loadFromFile((ContentPath / "instancedRenderingShader.frag").string());
		shaders[1].compile();
	}

	void RendererTests::imguiCamera()
	{
		Vector3f cameraPos = camera.getPosition();
		std::array<float, 3> rawCameraPosition;
		rawCameraPosition = Math::FromVectorToArray(cameraPos);
		std::string posName = std::string{ "Camera pos " };
		ImGui::SliderFloat3(posName.c_str(), rawCameraPosition.data(), -30.00f, 30.0f);
		cameraPos = Math::FromArrayToVector(rawCameraPosition);
		camera.setPosition(cameraPos);

		Vector3f cameraTarget = camera.getTarget();
		std::array<float, 3> rawCameraTarget;
		rawCameraTarget = Math::FromVectorToArray(cameraTarget);
		std::string targetName = std::string{ "Camera target " };
		ImGui::SliderFloat3(targetName.c_str(), rawCameraTarget.data(), -5.00f, 5.0f);
		cameraTarget = Math::FromArrayToVector(rawCameraTarget);
		camera.setTarget(cameraTarget);

		float cameraFar = camera.getFar();
		ImGui::SliderFloat("Camera 'Far'", &cameraFar, 10.f, 1000.f);
		camera.setFar(cameraFar);
	}

	void RendererTests::imguiDrawable2DBase(Drawable2DBase& drawable2D, size_t index)
	{
		Transform transform = drawable2D.getTransform();
		Vector3f position = transform.getTranslation();
		Vector3f rotation = transform.getRotation();
		Vector3f scale = transform.getScale();

		std::array<float, 3> rawPosition;
		rawPosition = Math::FromVectorToArray(position);
		std::string positionName = std::string{ "Position " } + std::to_string(static_cast<int>(index));
		ImGui::SliderFloat3(positionName.c_str(), rawPosition.data(), -10.0f, 10.0f);

		std::array<float, 3> rawRotation;
		rawRotation = Math::FromVectorToArray(rotation);
		std::string rotationName = std::string{ "Rotation " } + std::to_string(static_cast<int>(index));
		ImGui::SliderFloat3(rotationName.c_str(), rawRotation.data(), 0.f, 560.0f);

		std::array<float, 3> rawScale;
		rawScale = Math::FromVectorToArray(scale);
		std::string scaleName = std::string{ "Scale " } + std::to_string(static_cast<int>(index));
		ImGui::SliderFloat3(scaleName.c_str(), rawScale.data(), 0.01f, 10.0f);

		ImGui::Spacing();

		position = Math::FromArrayToVector(rawPosition);
		rotation = Math::FromArrayToVector(rawRotation);
		scale = Math::FromArrayToVector(rawScale);
		transform.setTranslation(position);
		transform.setRotation(rotation);
		transform.setScale(scale);
		drawable2D.setTransform(transform);
	}

	void RendererTests::imguiSprite(Sprite& sprite, size_t index)
	{
		imguiDrawable2DBase(sprite, index);
	}

	void RendererTests::imguiTileMap(TileMap& tileMap, size_t index)
	{
		imguiDrawable2DBase(tileMap, index);

		std::array<int, 2> rawTilesCount = Math::FromVectorToArray(Vector2i{ tileMap.getTilesCount() });
		ImGui::SliderInt2("Tiles Count", rawTilesCount.data(), 1, 1000);
		tileMap.setTilesCount(Math::FromArrayToVector(rawTilesCount));

		std::vector<TextureRegion> tilesTextureRegions;
		tilesTextureRegions.reserve(tileMap.getTilesCount().x * tileMap.getTilesCount().y);
		Vector2ui tileIndex{ 0u, 0u };

		for (tileIndex.y = 0u; tileIndex.y < tileMap.getTilesCount().y; ++tileIndex.y)
		{
			for (tileIndex.x = 0u; tileIndex.x < tileMap.getTilesCount().x; ++tileIndex.x)
			{
				TextureRegion textureRegion;
				textureRegion.offset = { tileIndex.x % 8 * 512.f, tileIndex.y % 8 * 512.f };
				textureRegion.size = { 512.f, 512.f };
				tilesTextureRegions.push_back(textureRegion);
			}
		}
		tileMap.setTilesTextureRegions(tilesTextureRegions, texture.getSize());
	}

	void RendererTests::imguiFlipbook(Flipbook& flipbook, size_t index)
	{
		imguiDrawable2DBase(flipbook, index);
	}

	void RendererTests::createTexture()
	{
		RendererContext& rendererContext = renderer.getRendererContext();
		auto& transferCommandBuffer = rendererContext.getTransferCommandBuffer();

		transferCommandBuffer.begin();
		bool textureUseMipmaps = false;
		texture.create({ rendererContext, transferCommandBuffer, stbImage.getSize(), textureUseMipmaps, vk::Format::eR8G8B8A8Srgb });

		texture.loadFromSTBImage(transferCommandBuffer, stbImage);

		// Create mipmap texture
		mipmapTexture.create({ rendererContext, transferCommandBuffer, stbImage.getSize(), true, vk::Format::eR8G8B8A8Srgb });
		Texture::GenerateMipmapTextureInfo generateMipmapTextureInfo
		{
			texture, transferCommandBuffer, rendererContext
		};
		mipmapTexture.generateMipmapTexture(generateMipmapTextureInfo);
		mipmapTexture.prepareForDraw(transferCommandBuffer);

		transferCommandBuffer.end();

		rendererContext.getQueue().submitWaitIdle(transferCommandBuffer);
	}

	void RendererTests::createSampler()
	{
		RendererContext& rendererContext = renderer.getRendererContext();

		vk::SamplerCreateInfo samplerCreateInfo = sampler.createCreateInfo(mipmapTexture.getImage().getMipmapLevels());
		sampler.create(rendererContext.getDevice(), samplerCreateInfo);
	}

	void RendererTests::imguiRecompileShaders(auto callable, auto... args)
	{
		if (ImGui::Button("Recompile shaders"))
		{
			std::invoke(callable, args...);
		}
	}

}