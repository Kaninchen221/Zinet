#pragma once

#include "Zinet/Core/ZtLogger.h"

namespace zt::wd
{
	class GLFW
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("GLFW");

	public:

		GLFW() { Init(); }
		GLFW(const GLFW& other) = default;
		GLFW(GLFW&& other) = default;

		GLFW& operator = (const GLFW& other) = default;
		GLFW& operator = (GLFW&& other) = default;

		~GLFW() noexcept { Deinit(); };

		static bool Init(bool hideWindow = true);
		static void Deinit();

		static void HideWindow();
		static void UnhideWindow();

	};
}