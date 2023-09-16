#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"

#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/Imgui/ZtGLImgui.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::engine
{

	class ZINET_ENGINE_LAYER_API Loop
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Loop");

	public:

		Loop() = default;
		Loop(const Loop& other) = default;
		Loop(Loop&& other) = default;

		Loop& operator = (const Loop& other) = default;
		Loop& operator = (Loop&& other) = default;

		~Loop() noexcept = default;

		gl::Renderer& getRenderer() { return renderer; }
		const gl::Renderer& getRenderer() const { return renderer; }

		gl::Imgui& getImgui() { return imgui; }
		const gl::Imgui& getImgui() const { return imgui; }

		void initialize();

		void deinitialize();

		void tick();

	protected:

		void windowEvents();

		gl::Renderer renderer;
		gl::Imgui imgui;

	};

}