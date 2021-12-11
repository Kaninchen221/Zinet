#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtMouseButton.h"
#include "Zinet/GraphicLayer/ZtMouseButtonEventType.h"

namespace zt::gl
{

	struct ZINET_GRAPHIC_LAYER_API MouseButtonEvent
	{
		MouseButtonEventType Type;
		MouseButton Button;

		bool operator == (const MouseButtonEvent& Other) const
		{
			return Type == Other.Type && Button == Other.Button;
		}
	};

}