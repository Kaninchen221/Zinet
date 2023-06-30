#include "Zinet/GraphicLayer/ZtGLShaderType.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	shaderc_shader_kind ShaderTypeToShaderc(ShaderType shaderType)
	{
		switch (shaderType)
		{
			case ShaderType::Vertex: return shaderc_glsl_vertex_shader;
			case ShaderType::Fragment: return shaderc_glsl_fragment_shader;
			default:
				zt::core::ConsoleLogger logger = zt::core::ConsoleLogger::Create("ShaderType");
				logger->error("Can't convert ShaderType to shaderc_shader_kind");
				return static_cast<shaderc_shader_kind>(ShaderType::Invalid);
		}
	}

	vk::ShaderStageFlagBits ShaderTypeToVkShaderStage(ShaderType shaderType)
	{
		switch (shaderType)
		{
			case ShaderType::Vertex: return vk::ShaderStageFlagBits::eVertex;
			case ShaderType::Fragment: return vk::ShaderStageFlagBits::eFragment;
			default:
				zt::core::ConsoleLogger logger = zt::core::ConsoleLogger::Create("ShaderType");
				logger->error("Can't convert ShaderType to vk::ShaderStageFlagBits");
				return static_cast<vk::ShaderStageFlagBits>(ShaderType::Invalid);
		}
	}
}