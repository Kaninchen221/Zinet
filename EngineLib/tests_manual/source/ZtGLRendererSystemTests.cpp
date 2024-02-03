#pragma once

#include "Zinet/Core/ZtLogger.hpp"
#include "Zinet/Core/ZtClock.hpp"

#include <gtest/gtest.h>

#include "Zinet/Engine/Systems/ZtRendererSystem.hpp"
#include "Zinet/Engine/Assets/ZtAssetsManager.hpp"
#include "Zinet/Engine/ZtTileMap.hpp"
#include "Zinet/Engine/ECS/ZtEntity.hpp"

#include "Zinet/Window/ZtGLFW.hpp"

#include "Zinet/GraphicLayer/ZtGLCamera.hpp"
#include "Zinet/GraphicLayer/ZtGLShape2D.hpp"

#include <filesystem>
#include <type_traits>

namespace zt::engine::tests
{

	class RendererSystemTests : public ::testing::Test
	{
	public:

		inline static core::ConsoleLogger Logger = core::ConsoleLogger::Create("RendererSystemTests");
		const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

		RendererSystem rendererSystem;
		AssetsManager assetsManager;
		engine::ecs::Entity entity{ core::UniqueID{ 3u } };
		gl::Camera camera;
		std::vector<gl::Shader> shaders;

		void SetUp() override
		{
			camera.setPosition({ 0.0f, 0.0f, -4.0f });
			camera.setFar(1000.f);
		}

		void prepareTwoDrawableObjectsTest();
		void twoDrawableObjectsTick();
		float direction = 1.f;
		void createShaders(std::string vertexShaderFileName = "shape2D.vert", std::string fragmentShaderFileName = "shape2D.frag");

		void prepareTileMap();

		void loop(auto callablePrepare, auto callableTick);

		bool skipTwoDrawableObjectsTest = false;
		bool skipTileMapTest = false;
	};

	TEST_F(RendererSystemTests, TwoDrawableObjects)
	{
		if (skipTwoDrawableObjectsTest)
			FAIL() << "";

		loop(&RendererSystemTests::prepareTwoDrawableObjectsTest, &RendererSystemTests::twoDrawableObjectsTick);
	}

	TEST_F(RendererSystemTests, TileMapTest)
	{
		if (skipTileMapTest)
			FAIL() << "";

		//loop(&RendererSystemTests::prepareTileMap, [](auto* thisPointer) {});
	}

	void RendererSystemTests::prepareTwoDrawableObjectsTest()
	{
		// Assets
		const std::string textureContentPath = "/Content/TileMapTexture.meta";
		AssetTexture assetTexture;
		assetsManager.addAsset(textureContentPath, assetTexture);

		rendererSystem.setCamera(camera);

		createShaders();

		auto createComponent = [&](Vector3f position, Vector4f color)
		{
			auto weakRef = rendererSystem.addComponent(entity);
			if (weakRef.isValid())
			{
				weakRef->create<gl::Shape2D>();
				DrawableComponent* component = weakRef.get();
				component->setShaders(shaders);
				gl::DrawableBase* drawable = component->getDrawable();
				if (drawable)
				{
					gl::Shape2D* shape = dynamic_cast<gl::Shape2D*>(drawable);
					shape->setColor(color);
				}

				auto firstShapeTransform = drawable->getTransform();
				firstShapeTransform.setTranslation(position);
				drawable->setTransform(firstShapeTransform);
			}
			else
			{
				Logger->error("Failed create first component");
			}

		};

		createComponent({ -0.5f, 0.5f, 0.f }, { 1.0f, 0.0f, 0.0f, 0.5f });
		createComponent({ 0.0f, 0.0f, 0.f }, { 0.0f, 1.0f, 0.0f, 0.5f });
	}

	void RendererSystemTests::createShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName)
	{
		shaders.clear();

		shaders.emplace_back();
		shaders[0].setType(gl::ShaderType::Vertex);
		shaders[0].loadFromFile((ContentPath / vertexShaderFileName).string());
		shaders[0].compile();

		shaders.emplace_back();
		shaders[1].setType(gl::ShaderType::Fragment);
		shaders[1].loadFromFile((ContentPath / fragmentShaderFileName).string());
		shaders[1].compile();
	}

	void RendererSystemTests::prepareTileMap()
	{
		rendererSystem.setCamera(camera);

		createShaders("tileMap.vert", "tileMap.frag");

		auto weakRef = rendererSystem.addComponent(entity);
		if (weakRef.isValid())
		{
			weakRef->create<TileMap>();
			DrawableComponent* component = weakRef.get();
			component->setShaders(shaders);
			gl::DrawableBase* drawable = component->getDrawable();
			if (drawable)
			{
				TileMap* tileMap = dynamic_cast<TileMap*>(drawable);
				tileMap->setTilesCount(Vector2ui{ 1u, 1u });
				tileMap->setTilesTextureRegions({ gl::TextureRegion{} }, Vector2f{ 1.f, 1.f });
			}
		}
		else
		{
			Logger->error("Failed create tile map");
		}
	}

	void RendererSystemTests::twoDrawableObjectsTick()
	{
		auto weakRef = rendererSystem.getComponents()[1].createWeakRef();
		if (weakRef.isValid())
		{
			auto* component = weakRef.get();
			auto* drawable = component->getDrawable();
			auto transform = drawable->getTransform();
			auto translation = transform.getTranslation();

			if (translation.z >= 1.f || translation.z <= -1.f)
				direction *= -1.f;

			translation.z += 0.001f * direction;
			transform.setTranslation(translation);
			drawable->setTransform(transform);
		}
	}

	void RendererSystemTests::loop(auto callablePrepare, auto callableTick)
	{
		wd::GLFW::UnhideWindow();
		rendererSystem.initialize();

		std::invoke(callablePrepare, this);

		core::Clock clock;
		while (rendererSystem.getRenderer().getRendererContext().getWindow().isOpen())
		{
			auto& renderer = rendererSystem.getRenderer();
			auto& rendererContext = renderer.getRendererContext();
			auto& window = rendererContext.getWindow();
			auto& event = window.getEvent();

			event.pollEvents();

			std::invoke(callableTick, this);

			const auto timeElapsed = clock.restart();
			rendererSystem.preUpdate(timeElapsed);
			rendererSystem.update(timeElapsed);
			rendererSystem.postUpdate(timeElapsed);
		}
	}

}