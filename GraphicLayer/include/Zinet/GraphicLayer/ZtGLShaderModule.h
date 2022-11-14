#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLShaderType.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Shader;
	class Device;

	class ZINET_GRAPHIC_LAYER_API ShaderModule : public VulkanObject<vk::raii::ShaderModule>
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("ShaderModule");

	public:

		ShaderModule() = default;
		ShaderModule(const ShaderModule& other) = default;
		ShaderModule(ShaderModule&& other) = default;

		ShaderModule& operator = (const ShaderModule& other) = default;
		ShaderModule& operator = (ShaderModule&& other) = default;

		~ShaderModule() noexcept = default;

		vk::ShaderModuleCreateInfo createShaderModuleCreateInfo(const Shader& shader) const;

		void create(Device& device, ShaderType newShaderType, const vk::ShaderModuleCreateInfo& createInfo);

		ShaderType getType() const;

	protected:

		ShaderType shaderType = ShaderType::Invalid;

	};

}