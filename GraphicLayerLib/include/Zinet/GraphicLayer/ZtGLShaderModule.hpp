#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLShaderType.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"
#include "Zinet/GraphicLayer/ZtGLShader.hpp"
#include "Zinet/GraphicLayer/ZtGLSemaphore.hpp"

#include "Zinet/Core/ZtLogger.hpp"

namespace zt::gl
{
	class Shader;
	class Device;

	class ZINET_GRAPHIC_LAYER_API ShaderModule : public VulkanObject<vk::raii::ShaderModule>
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("ShaderModule");

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