#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

enum class ZINET_GRAPHIC_LAYER_API ZtKeyboardEventType
{
	Pressed = GLFW_PRESS, 
	Repeated = GLFW_REPEAT,
	Released = GLFW_RELEASE
};