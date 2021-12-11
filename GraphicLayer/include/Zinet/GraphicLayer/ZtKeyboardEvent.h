#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtKeyboardEventType.h"
#include "Zinet/GraphicLayer/ZtKeyboardKey.h"

namespace zt::gl
{

	struct ZINET_GRAPHIC_LAYER_API KeyboardEvent
	{
		KeyboardEventType Type;
		KeyboardKey Key;

		bool operator == (const KeyboardEvent& Other) const;
	};

	inline bool KeyboardEvent::operator==(const KeyboardEvent& Other) const
	{
		if (Type == Other.Type && Key == Other.Key)
			return true;
		else
			return false;
	}

}
