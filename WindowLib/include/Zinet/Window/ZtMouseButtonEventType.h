#pragma once

#include <GLFW/glfw3.h>

namespace zt::wd
{
	enum class MouseButtonEventType
	{
		Pressed = GLFW_PRESS,
		Repeated = GLFW_REPEAT,
		Released = GLFW_RELEASE
	};

}