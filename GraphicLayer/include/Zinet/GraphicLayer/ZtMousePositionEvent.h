#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtMousePositionEvent.h"

#include "glm/vec2.hpp"

namespace zt::gl
{

	struct ZINET_GRAPHIC_LAYER_API MousePositionEvent
	{
		glm::dvec2 Position;
	};

}