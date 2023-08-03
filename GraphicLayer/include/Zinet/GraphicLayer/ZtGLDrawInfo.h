#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLShader.h"
#include "Zinet/GraphicLayer/ZtGLShaderType.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLIndexBuffer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLUniformBuffer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLImageBuffer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLStorageBuffer.h"
#include "Zinet/GraphicLayer/ZtGLSampler.h"
#include "Zinet/GraphicLayer/ZtGLImageView.h"
#include "Zinet/GraphicLayer/ZtGLVecTypes.h"

#include <span>
#include <vector>

namespace zt::gl
{
	class Camera;

	using DescriptorType = vk::DescriptorType;

	inline vk::DescriptorType DescriptorTypeToVkDescriptorType(DescriptorType descriptorType) { return descriptorType; }

	struct ZINET_GRAPHIC_LAYER_API RenderStates
	{
		struct ZINET_GRAPHIC_LAYER_API Image
		{
			const ImageBuffer& buffer;
			const Sampler& sampler;
			const ImageView& view;
			vk::ImageLayout layout;
			std::uint32_t binding;
		};

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
		std::span<Descriptor> descriptors;
		std::span<Image> images;
		const Camera& camera;
		Matrix4f modelMatrix;
	};

	struct ZINET_GRAPHIC_LAYER_API DrawInfo
	{
		DrawInfo() = default;
		DrawInfo(const DrawInfo& other) = delete;
		DrawInfo(DrawInfo&& other) = default;

		DrawInfo& operator = (const DrawInfo& other) = delete;
		DrawInfo& operator = (DrawInfo&& other) = default;

		virtual ~DrawInfo() noexcept = default;

		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
		std::vector<std::uint16_t> indices;
		std::vector<UniformBuffer> uniformBuffers;
		std::vector<StorageBuffer> storageBuffers;
		size_t MVPBufferIndex = std::numeric_limits<size_t>::max();
		std::uint32_t instanceCount = 1u;
	};

}