#pragma once

#include "Zinet/Engine/ZtEngine.h"

#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
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

		Renderer& getRenderer() { return renderer; }
		const Renderer& getRenderer() const { return renderer; }

	protected:

		Renderer renderer;

	};

}