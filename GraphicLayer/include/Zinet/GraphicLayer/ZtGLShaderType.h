#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include <shaderc/shaderc.hpp>

namespace zt::gl
{
	// TODO (Very Low) Support other types
	enum class ZINET_GRAPHIC_LAYER_API ShaderType
	{
		Invalid,
		Vertex,
		Fragment,
		Compute,
		Geometry
	};

	shaderc_shader_kind ZINET_GRAPHIC_LAYER_API ShaderTypeToShaderc(ShaderType shaderType);

	vk::ShaderStageFlagBits ZINET_GRAPHIC_LAYER_API ShaderTypeToVkShaderStage(ShaderType shaderType);

}