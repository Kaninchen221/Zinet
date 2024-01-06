#pragma once

#include "Zinet/Core/ZtClock.hpp"

#include "Zinet/Engine/ZtLoop.hpp"

#include "Zinet/GraphicLayer/ZtGLRendererContext.hpp"

#include "imgui.h"

namespace zt::engine
{
	void Loop::initialize()
	{
		renderer.initialize();
		auto& rendererContext = renderer.getRendererContext();

		imgui.preinit(rendererContext);
		imgui.init(rendererContext);
	}

	void Loop::deinitialize()
	{
		auto& rendererContext = renderer.getRendererContext();
		rendererContext.getQueue()->waitIdle();
		rendererContext.getDevice()->waitIdle();
	}

	void Loop::step(const core::Time& elapsedTime)
	{
		tick(elapsedTime);
	}

	void Loop::tick(const core::Time& elapsedTime)
	{
		windowEvents();

		ImGui::NewFrame();

		ImGui::EndFrame();

		ImGui::Render();

		renderer.preDraw();

		// Draw calls
		imgui.draw(renderer.getDrawCommandBuffer());

		renderer.postDraw();
	}

	void Loop::windowEvents()
	{
		auto& rendererContext = renderer.getRendererContext();
		auto& window = rendererContext.getWindow();
		auto& event = window.getEvent();

		event.pollEvents();

		imgui.update();
	}

	bool Loop::shouldTick() const
	{
		bool isWindowOpen = renderer.getRendererContext().getWindow().isOpen();
		return isWindowOpen && !requestTickEnd;
	}

	void Loop::start()
	{
		core::Clock clock;
		clock.start();
		while (shouldTick())
		{
			const auto timeElapsed = clock.restart();
			lastTickElapsedTime = timeElapsed;
			step(timeElapsed);
		}
	}

}