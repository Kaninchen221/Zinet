#pragma once

#include "ZtRenderer.h"

enum class ZINET_RENDERER_API ZtVertexBufferUsage : GLenum
{
	Static = GL_STATIC_DRAW,
	Dynamic = GL_DYNAMIC_DRAW
};