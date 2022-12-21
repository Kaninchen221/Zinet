#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLShader.h"
#include "Zinet/GraphicLayer/ZtGLShaderType.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLIndexBuffer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLUniformBuffer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLImageBuffer.h"
#include "Zinet/GraphicLayer/ZtGLSampler.h"
#include "Zinet/GraphicLayer/ZtGLImageView.h"

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

		struct ZINET_GRAPHIC_LAYER_API Image
		{
			ImageBuffer& buffer;
			Sampler& sampler;
			ImageView& view;
			vk::ImageLayout layout;
		};

		std::span<Shader> shaders;
		std::span<Descriptor> descriptors;
		VertexBuffer& vertexBuffer;
		IndexBuffer& indexBuffer;
		std::span<UniformBuffer> uniformBuffers;
		std::span<Image> images;

	};

}