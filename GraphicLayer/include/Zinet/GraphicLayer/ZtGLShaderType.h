#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "shaderc/shaderc.hpp"

namespace zt::gl
{
	enum class ZINET_GRAPHIC_LAYER_API ShaderType
	{
		Invalid,
		Vertex,
		Fragment
	};

	shaderc_shader_kind ZINET_GRAPHIC_LAYER_API ShaderTypeToShaderc(ShaderType shaderType);

	vk::ShaderStageFlagBits ZINET_GRAPHIC_LAYER_API ShaderTypeToVkShaderStage(ShaderType shaderType);

}