#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLShader.h"

#include <span>

namespace zt::gl
{

	struct ZINET_GRAPHIC_LAYER_API RendererDrawInfo
	{
		std::span<Shader> shaders;


	};

}