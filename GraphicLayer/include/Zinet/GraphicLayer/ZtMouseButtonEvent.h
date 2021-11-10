#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtMouseButton.h"
#include "Zinet/GraphicLayer/ZtMouseButtonEventType.h"

struct ZINET_GRAPHIC_LAYER_API ZtMouseButtonEvent
{
	ZtMouseButtonEventType Type;
	ZtMouseButton Button;

	bool operator == (const ZtMouseButtonEvent& Other) const
	{
		return Type == Other.Type && Button == Other.Button;
	}
};