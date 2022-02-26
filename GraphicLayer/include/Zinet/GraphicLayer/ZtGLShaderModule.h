#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLShaderType.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Shader;
	class Device;

	class ZINET_GRAPHIC_LAYER_API ShaderModule
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("ShaderModule");

	public:

		ShaderModule();
		ShaderModule(const ShaderModule& other) = default;
		ShaderModule(ShaderModule&& other) = default;

		ShaderModule& operator = (const ShaderModule& other) = default;
		ShaderModule& operator = (ShaderModule&& other) = default;

		~ShaderModule() noexcept = default;

		vk::raii::ShaderModule& getInternal();

		vk::ShaderModuleCreateInfo createShaderModuleCreateInfo(const Shader& shader) const;

		void create(Device& device, const Shader& shader);

		ShaderType getType() const;

	protected:

		vk::raii::ShaderModule internal;
		ShaderType shaderType = ShaderType::Invalid;

	};

}