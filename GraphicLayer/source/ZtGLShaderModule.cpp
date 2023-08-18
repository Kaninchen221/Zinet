#include "Zinet/GraphicLayer/ZtGLShaderModule.h"

#include "Zinet/GraphicLayer/ZtGLShader.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{
	vk::ShaderModuleCreateInfo ShaderModule::createShaderModuleCreateInfo(const Shader& shader) const
	{
		vk::ShaderModuleCreateInfo createInfo;
		createInfo.codeSize = shader.getCompiled().size() * 4;
		createInfo.pCode = shader.getCompiled().data();

		return createInfo;
	}

	void ShaderModule::create(Device& device, ShaderType newShaderType, const vk::ShaderModuleCreateInfo& createInfo)
	{
		shaderType = newShaderType;
		vk::raii::ShaderModule tempShaderModule{ device.getInternal(), createInfo, nullptr };
		internal.swap(tempShaderModule);
		tempShaderModule.release();
	}

	ShaderType ShaderModule::getType() const
	{
		return shaderType;
	}
}