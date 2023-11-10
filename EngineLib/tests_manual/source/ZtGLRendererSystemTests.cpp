#pragma once

#include "Zinet/Core/ZtLogger.h"
#include "Zinet/Core/ZtClock.h"

#include <gtest/gtest.h>

#include "Zinet/Engine/Systems/ZtRendererSystem.h"
#include "Zinet/Engine/ECS/ZtEntity.h"

#include "Zinet/Window/ZtGLFW.h"

#include "Zinet/GraphicLayer/ZtGLCamera.h"

namespace zt::engine::tests
{

	class RendererSystemTests : public ::testing::Test
	{
	public:

		inline static core::ConsoleLogger Logger = core::ConsoleLogger::Create("RendererSystemTests");

		RendererSystem rendererSystem;
		engine::ecs::Entity entity{ core::UniqueID{ 3u } };
		gl::Camera camera;

		void SetUp() override
		{
			camera.setPosition(Vector3f{ 0.f, 0.f, -5.f });
			camera.setFar(1000.f);
		}

		void prepareTwoDrawableObjectsTest();
	};

	TEST_F(RendererSystemTests, TwoDrawableObjects)
	{
		wd::GLFW::UnhideWindow();
		rendererSystem.initialize();

		prepareTwoDrawableObjectsTest();

		core::Clock clock;
		while (rendererSystem.getRenderer().getRendererContext().getWindow().isOpen())
		{
			auto& renderer = rendererSystem.getRenderer();
			auto& rendererContext = renderer.getRendererContext();
			auto& window = rendererContext.getWindow();
			auto& event = window.getEvent();

			event.pollEvents();

			auto timeElapsed = clock.restart();
			rendererSystem.preUpdate(timeElapsed);
			rendererSystem.update(timeElapsed);
			rendererSystem.postUpdate(timeElapsed);
		}
	}

	void RendererSystemTests::prepareTwoDrawableObjectsTest()
	{
		auto character = rendererSystem.addComponent(entity);
		if (character.isValid())
		{

		}
		else
		{
			Logger->error("Failed create character sprite");
		}
	}
}