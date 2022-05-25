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

		// TODO Remove the definition and mark as default
		ShaderModule();
		ShaderModule(const ShaderModule& other) = default;
		ShaderModule(ShaderModule&& other) = default;

		ShaderModule& operator = (const ShaderModule& other) = default;
		ShaderModule& operator = (ShaderModule&& other) = default;

		~ShaderModule() noexcept = default;

		// TODO Move it to Shader class
		vk::ShaderModuleCreateInfo createShaderModuleCreateInfo(const Shader& shader) const;

		// TODO Replace the shader param with ShaderModuleCreateInfo
		void create(Device& device, const Shader& shader);

		ShaderType getType() const;

	protected:

		ShaderType shaderType = ShaderType::Invalid;

	};

}