#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "glslang/Public/ShaderLang.h"

namespace zt::gl
{
	enum class ZINET_GRAPHIC_LAYER_API ShaderType
	{
		Vertex = EShLanguage::EShLangVertex,
		Fragment = EShLanguage::EShLangFragment
	};

}