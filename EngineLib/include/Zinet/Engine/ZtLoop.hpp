#pragma once

#include "Zinet/Engine/ZtEngineConfig.hpp"

#include "Zinet/GraphicLayer/ZtGLRenderer.hpp"
#include "Zinet/GraphicLayer/Imgui/ZtGLImgui.hpp"

#include "Zinet/Core/ZtLogger.hpp"
#include "Zinet/Core/ZtTime.hpp"

namespace zt::core
{
	class Time;
}

namespace zt::engine
{

	class ZINET_ENGINE_API Loop
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

		void step(const core::Time& elapsedTime);

		void tick(const core::Time& elapsedTime);

		bool shouldTick() const;

		void start();

		const core::Time& getLastTickElapsedTime() const { return lastTickElapsedTime; }

		void setRequestTickEnd(bool value) { requestTickEnd = value; }

	protected:

		void windowEvents();

		gl::Renderer renderer;
		gl::Imgui imgui;
		core::Time lastTickElapsedTime;
		bool requestTickEnd = false;
	};

}