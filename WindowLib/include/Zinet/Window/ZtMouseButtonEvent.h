#pragma once

#include "Zinet/Window/ZtWindowConfig.h"
#include "Zinet/Window/ZtMouseButton.h"
#include "Zinet/Window/ZtMouseButtonEventType.h"

namespace zt::wd
{
	struct ZINET_WINDOW_LAYER_API MouseButtonEvent
	{
		MouseButtonEventType type;
		MouseButton button;

		bool operator == (const MouseButtonEvent& other) const
		{
			return type == other.type && button == other.button;
		}
	};

}