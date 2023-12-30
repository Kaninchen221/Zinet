#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGLShaderModule.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorSetLayout.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorSets.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorPool.h"
#include "Zinet/GraphicLayer/ZtGLPipelineLayout.h"
#include "Zinet/GraphicLayer/ZtGLPipeline.h"
#include "Zinet/GraphicLayer/ZtGLDrawInfo.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"

#include "Zinet/Core/ZtLogger.h"

#include <map>

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API RendererPipeline
	{

	public:

		struct ZINET_GRAPHIC_LAYER_API CreateInfo
		{
			const RenderStates& renderStates;
			const DrawInfo& drawInfo;
			Device& device;
			RenderPass& renderPass;
			CommandPool& commandPool;
			const vk::Extent2D& swapExtent;
		};

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("RendererPipeline");

	public:

		RendererPipeline() = default;
		RendererPipeline(const RendererPipeline& other) = default;
		RendererPipeline(RendererPipeline&& other) = default;

		RendererPipeline& operator = (const RendererPipeline& other) = default;
		RendererPipeline& operator = (RendererPipeline&& other) = default;

		~RendererPipeline() noexcept;

		const std::vector<ShaderModule>& getShadersModules() const;

		const std::vector<vk::PipelineShaderStageCreateInfo>& getShadersStages() const;

		const std::vector<vk::DescriptorSetLayoutBinding>& getBindings() const;

		const std::vector<DescriptorSetLayout>& getDescriptorSetLayouts() const;

		const std::optional<DescriptorSets>& getDescriptorSets() const;

		const DescriptorPool& getDescriptorPool() const;

		const std::vector<vk::DescriptorBufferInfo>& getDescriptorBufferInfos() const;

		const std::vector<vk::DescriptorImageInfo>& getDescriptorImageInfos() const;

		const std::vector<vk::WriteDescriptorSet>& getWriteDescriptorSets() const;

		const PipelineLayout& getPipelineLayout() const;

		Pipeline& getPipeline();
		const Pipeline& getPipeline() const;

		template<class VertexType>
		void create(const CreateInfo& createInfo);

		void updateDescriptorSets(Device& device);

	protected:

		template<class VertexType>
		void createPipeline(const CreateInfo& createInfo);
		void createShadersModules(const std::vector<Shader>& shaders, Device& device);
		void createShadersStages();
		void createDescriptorSetLayouts(const std::vector<RenderStates::Descriptor>& descriptors, Device& device);
		void createPipelineLayout(Device& device, const vk::Extent2D& swapExtent);

		void createDescriptors(const CreateInfo& createInfo);
		void createDescriptorPool(const std::vector<RenderStates::Descriptor>& descriptors, Device& device);
		void createDescriptorSets(Device& device);
		void createWriteDescriptorSets(const RenderStates& renderStates, const DrawInfo& drawInfo);
		void createImageWriteDescriptorSets(const std::vector<RenderStates::Image>& images);

		template<class BufferType>
		void createBufferWriteDescriptorSets(const std::span<const BufferType> buffers, vk::DescriptorType descriptorType);

		std::vector<ShaderModule> shadersModules;
		std::vector<vk::PipelineShaderStageCreateInfo> shadersStages;
		std::vector<vk::DescriptorSetLayoutBinding> bindings;
		std::vector<DescriptorSetLayout> descriptorSetLayouts;
		std::optional<DescriptorSets> descriptorSets;
		DescriptorPool descriptorPool;
		std::vector<vk::DescriptorBufferInfo> descriptorBufferInfos;
		std::vector<vk::DescriptorImageInfo> descriptorImageInfos;
		std::vector<vk::WriteDescriptorSet> writeDescriptorSets;
		PipelineLayout pipelineLayout;
		Pipeline pipeline;
	};

	template<class VertexType>
	void RendererPipeline::create(const CreateInfo& createInfo)
	{
		createPipeline<VertexType>(createInfo);
		createDescriptors(createInfo);
	}

	template<class VertexType>
	void RendererPipeline::createPipeline(const CreateInfo& createInfo)
	{
		createShadersModules(createInfo.renderStates.shaders, createInfo.device);
		createShadersStages();
		createDescriptorSetLayouts(createInfo.renderStates.descriptors, createInfo.device);
		createPipelineLayout(createInfo.device, createInfo.swapExtent);

		vk::GraphicsPipelineCreateInfo graphicsPipelineCreateInfo = pipeline.createGraphicsPipelineCreateInfo<VertexType>(pipelineLayout, createInfo.renderPass, shadersStages);
		pipeline.create(createInfo.device, graphicsPipelineCreateInfo);
	}

	template<class BufferType>
	void zt::gl::RendererPipeline::createBufferWriteDescriptorSets(const std::span<const BufferType> buffers, vk::DescriptorType descriptorType)
	{
		size_t index = 0u;
		for (const BufferType& buffer : buffers)
		{
			vk::DescriptorBufferInfo& descriptorBufferInfo = descriptorBufferInfos.emplace_back(buffer.createDescriptorBufferInfo());

			DescriptorSets::CreateBufferWriteDescriptorSetInfo createBufferWriteDescriptorSetInfo
			{
				0u, descriptorBufferInfo, buffer.getBinding(), descriptorType
			};
			vk::WriteDescriptorSet writeDescriptorSet = descriptorSets->createBufferWriteDescriptorSet(createBufferWriteDescriptorSetInfo);
			writeDescriptorSets.push_back(writeDescriptorSet);

			++index;
		}
	}
}