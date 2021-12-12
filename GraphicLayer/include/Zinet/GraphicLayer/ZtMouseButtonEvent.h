#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtMouseButton.h"
#include "Zinet/GraphicLayer/ZtMouseButtonEventType.h"

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