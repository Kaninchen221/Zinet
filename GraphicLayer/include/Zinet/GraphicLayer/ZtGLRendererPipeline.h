#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGLShaderModule.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorSetLayout.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorSets.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorPool.h"
#include "Zinet/GraphicLayer/ZtGLPipelineLayout.h"
#include "Zinet/GraphicLayer/ZtGLPipeline.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API RendererPipeline
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("RendererPipeline");

	public:

		RendererPipeline() = default;
		RendererPipeline(const RendererPipeline& other) = default;
		RendererPipeline(RendererPipeline&& other) = default;

		RendererPipeline& operator = (const RendererPipeline& other) = default;
		RendererPipeline& operator = (RendererPipeline&& other) = default;

		~RendererPipeline() noexcept = default;

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

		const Pipeline& getPipeline() const;

	protected:

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

}