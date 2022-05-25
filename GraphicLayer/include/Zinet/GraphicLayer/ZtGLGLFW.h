#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API GLFW
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("GLFW");

	public:

		GLFW() = default;
		GLFW(const GLFW& other) = default;
		GLFW(GLFW&& other) = default;

		GLFW& operator = (const GLFW& other) = default;
		GLFW& operator = (GLFW&& other) = default;

		~GLFW() noexcept = default;

		// TODO Rename to Init
		static bool InitGLFW();

		// TODO Rename to Deinit
		static void DeinitGLFW();

	};

}