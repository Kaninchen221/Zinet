#include "Zinet/GraphicLayer/ZtGLShaderModule.h"

#include "Zinet/GraphicLayer/ZtGLShader.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{
	ShaderModule::ShaderModule()
		: internal(std::nullptr_t())
	{}

	vk::raii::ShaderModule& ShaderModule::getInternal()
	{
		return internal;
	}

	vk::ShaderModuleCreateInfo ShaderModule::createShaderModuleCreateInfo(const Shader& shader) const
	{
		vk::ShaderModuleCreateInfo createInfo;
		createInfo.codeSize = shader.getCompiled().size() * 4;
		createInfo.pCode = shader.getCompiled().data();

		return createInfo;
	}

	void ShaderModule::create(Device& device, const Shader& shader)
	{
		vk::ShaderModuleCreateInfo createInfo = createShaderModuleCreateInfo(shader);
		shaderType = shader.getType();
		internal = vk::raii::ShaderModule{ device.getInternal(), createInfo, nullptr };
	}

	ShaderType ShaderModule::getType() const
	{
		return shaderType;
	}
}