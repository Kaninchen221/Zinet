#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtKeyboardEventType.h"
#include "Zinet/GraphicLayer/ZtKeyboardKey.h"

struct ZINET_GRAPHIC_LAYER_API ZtKeyboardEvent
{
	ZtKeyboardEventType Type;
	ZtKeyboardKey Key;

	bool operator == (const ZtKeyboardEvent& Other) const;
};

inline bool ZtKeyboardEvent::operator==(const ZtKeyboardEvent& Other) const
{
	if (Type == Other.Type && Key == Other.Key)
		return true;
	else
		return false;
}