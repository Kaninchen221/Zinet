#include "Zinet/GraphicLayer/ZtGLShaderType.hpp"

#include "Zinet/Core/ZtLogger.hpp"

namespace zt::gl
{
	shaderc_shader_kind ShaderTypeToShaderc(ShaderType shaderType)
	{
		switch (shaderType)
		{
			case ShaderType::Vertex: return shaderc_glsl_vertex_shader;
			case ShaderType::Fragment: return shaderc_glsl_fragment_shader;
			case ShaderType::Geometry: return shaderc_glsl_geometry_shader;
			case ShaderType::Compute: return shaderc_compute_shader;
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
			case ShaderType::Geometry: return vk::ShaderStageFlagBits::eGeometry;
			case ShaderType::Compute: return vk::ShaderStageFlagBits::eCompute;
			default:
				zt::core::ConsoleLogger logger = zt::core::ConsoleLogger::Create("ShaderType");
				logger->error("Can't convert ShaderType to vk::ShaderStageFlagBits");
				return static_cast<vk::ShaderStageFlagBits>(ShaderType::Invalid);
		}
	}
}