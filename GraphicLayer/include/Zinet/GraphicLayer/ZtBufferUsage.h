#pragma once

#include "ZtGraphicLayer.h"

enum class ZINET_GRAPHIC_LAYER_API ZtBufferUsage : GLenum
{
	Static = GL_STATIC_DRAW,
	Dynamic = GL_DYNAMIC_DRAW
};