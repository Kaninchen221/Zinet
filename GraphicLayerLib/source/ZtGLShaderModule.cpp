#include "Zinet/GraphicLayer/ZtGLShaderModule.hpp"

#include "Zinet/GraphicLayer/ZtGLShader.hpp"
#include "Zinet/GraphicLayer/ZtGLDevice.hpp"

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