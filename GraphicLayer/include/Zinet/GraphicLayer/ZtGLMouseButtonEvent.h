#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLMouseButton.h"
#include "Zinet/GraphicLayer/ZtGLMouseButtonEventType.h"

namespace zt::gl
{

	struct ZINET_GRAPHIC_LAYER_API MouseButtonEvent
	{
		MouseButtonEventType type;
		MouseButton button;

		bool operator == (const MouseButtonEvent& other) const
		{
			return type == other.type && button == other.button;
		}
	};

}