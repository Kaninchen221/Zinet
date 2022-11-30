#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLShader.h"
#include "Zinet/GraphicLayer/ZtGLShaderType.h"

#include <span>
#include <vector>

namespace zt::gl
{
	// TODO: Write own DescriptorType enum
	using DescriptorType = vk::DescriptorType;

	inline vk::DescriptorType DescriptorTypeToVkDescriptorType(DescriptorType descriptorType) { return descriptorType; }

	struct ZINET_GRAPHIC_LAYER_API DrawInfo
	{
		struct ZINET_GRAPHIC_LAYER_API Descriptor
		{
			std::uint32_t binding = 0u;
			DescriptorType descriptorType;
			std::uint32_t count = 0u;
			ShaderType shaderType;

			vk::DescriptorSetLayoutBinding toVkDescriptorSetLayoutBinding() const
			{
				vk::DescriptorSetLayoutBinding descriptorSetLayoutBinding{};
				descriptorSetLayoutBinding.binding = binding;
				descriptorSetLayoutBinding.descriptorType = DescriptorTypeToVkDescriptorType(descriptorType);
				descriptorSetLayoutBinding.descriptorCount = count;
				descriptorSetLayoutBinding.stageFlags = ShaderTypeToVkShaderStage(shaderType);
				descriptorSetLayoutBinding.pImmutableSamplers = nullptr;

				return descriptorSetLayoutBinding;
			}
		};

		std::span<Shader> shaders;
		std::vector<Descriptor> descriptors;
	};

}