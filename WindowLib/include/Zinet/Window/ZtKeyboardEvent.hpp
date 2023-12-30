#pragma once

#include "Zinet/Window/ZtWindowConfig.h"
#include "Zinet/Window/ZtKeyboardEventType.h"
#include "Zinet/Window/ZtKeyboardKey.h"

namespace zt::wd
{

	struct ZINET_WINDOW_LAYER_API KeyboardEvent
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
