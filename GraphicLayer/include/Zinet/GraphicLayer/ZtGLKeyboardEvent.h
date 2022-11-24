#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLKeyboardEventType.h"
#include "Zinet/GraphicLayer/ZtGLKeyboardKey.h"

namespace zt::gl
{

	struct ZINET_GRAPHIC_LAYER_API KeyboardEvent
	{
		KeyboardEventType type;
		KeyboardKey key;

		bool operator == (const KeyboardEvent& other) const;
	};

	inline bool KeyboardEvent::operator==(const KeyboardEvent& other) const
	{
		if (type == other.type && key == other.key)
			return true;
		else
			return false;
	}

}
