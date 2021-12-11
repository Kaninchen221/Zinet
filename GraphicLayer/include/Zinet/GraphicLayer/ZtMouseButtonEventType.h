#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

namespace zt::gl
{

	enum class ZINET_GRAPHIC_LAYER_API MouseButtonEventType
	{
		Pressed = GLFW_PRESS,
		Repeated = GLFW_REPEAT,
		Released = GLFW_RELEASE
	};

}