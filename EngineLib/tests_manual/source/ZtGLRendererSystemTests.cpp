#pragma once

#include "Zinet/Core/ZtLogger.h"
#include "Zinet/Core/ZtClock.h"

#include <gtest/gtest.h>

#include "Zinet/Engine/Systems/ZtRendererSystem.h"
#include "Zinet/Engine/ECS/ZtEntity.h"

#include "Zinet/Window/ZtGLFW.h"

#include "Zinet/GraphicLayer/ZtGLCamera.h"
#include "Zinet/GraphicLayer/ZtGLShape2D.h"

#include <filesystem>

namespace zt::engine::tests
{

	class RendererSystemTests : public ::testing::Test
	{
	public:

		inline static core::ConsoleLogger Logger = core::ConsoleLogger::Create("RendererSystemTests");
		const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

		RendererSystem rendererSystem;
		engine::ecs::Entity entity{ core::UniqueID{ 3u } };
		gl::Camera camera;
		std::vector<gl::Shader> shaders;

		void SetUp() override
		{
			camera.setPosition({ 0.0f, 0.0f, -4.0f });
			camera.setFar(1000.f);
		}

		void prepareTwoDrawableObjectsTest();
		void createShaders();
	};

	TEST_F(RendererSystemTests, TwoDrawableObjects)
	{
		wd::GLFW::UnhideWindow();
		rendererSystem.initialize();

		prepareTwoDrawableObjectsTest();

		core::Clock clock;
		float direction = 1.f;
		while (rendererSystem.getRenderer().getRendererContext().getWindow().isOpen())
		{
			auto& renderer = rendererSystem.getRenderer();
			auto& rendererContext = renderer.getRendererContext();
			auto& window = rendererContext.getWindow();
			auto& event = window.getEvent();

			event.pollEvents();

			auto weakRef = rendererSystem.getComponents()[1].createWeakRef();
			if (weakRef.isValid())
			{
				auto* component = weakRef.get();
				auto* drawable = component->getDrawable();
				auto transform = drawable->getTransform();
				auto translation = transform.getTranslation();

				if (translation.z >= 1.f || translation.z <= -1)
					direction *= -1.f;

				translation.z += 0.01f * direction;
				transform.setTranslation(translation);
				drawable->setTransform(transform);
			}

			auto timeElapsed = clock.restart();
			rendererSystem.preUpdate(timeElapsed);
			rendererSystem.update(timeElapsed);
			rendererSystem.postUpdate(timeElapsed);
		}
	}

	void RendererSystemTests::prepareTwoDrawableObjectsTest()
	{
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

	void RendererSystemTests::createShaders()
	{
		shaders.clear();

		shaders.emplace_back();
		shaders[0].setType(gl::ShaderType::Vertex);
		shaders[0].loadFromFile((ContentPath / "shape2D.vert").string());
		shaders[0].compile();

		shaders.emplace_back();
		shaders[1].setType(gl::ShaderType::Fragment);
		shaders[1].loadFromFile((ContentPath / "shape2D.frag").string());
		shaders[1].compile();
	}

}