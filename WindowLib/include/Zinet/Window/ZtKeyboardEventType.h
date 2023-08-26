#pragma once

#include <GLFW/glfw3.h>

namespace zt::window
{

	enum class KeyboardEventType
	{
		Pressed = GLFW_PRESS,
		Repeated = GLFW_REPEAT,
		Released = GLFW_RELEASE
	};

}