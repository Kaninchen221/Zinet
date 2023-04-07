#include "Zinet/GraphicLayer/ZtGLRendererPipeline.h"

namespace zt::gl
{

	const std::vector<ShaderModule>& RendererPipeline::getShadersModules() const
	{
		return shadersModules;
	}

	const std::vector<vk::PipelineShaderStageCreateInfo>& RendererPipeline::getShadersStages() const
	{
		return shadersStages;
	}

	const std::vector<vk::DescriptorSetLayoutBinding>& RendererPipeline::getBindings() const
	{
		return bindings;
	}

	const std::vector<DescriptorSetLayout>& RendererPipeline::getDescriptorSetLayouts() const
	{
		return descriptorSetLayouts;
	}

	const std::optional<DescriptorSets>& RendererPipeline::getDescriptorSets() const
	{
		return descriptorSets;
	}

	const DescriptorPool& RendererPipeline::getDescriptorPool() const
	{
		return descriptorPool;
	}

	const std::vector<vk::DescriptorBufferInfo>& RendererPipeline::getDescriptorBufferInfos() const
	{
		return descriptorBufferInfos;
	}

	const std::vector<vk::DescriptorImageInfo>& RendererPipeline::getDescriptorImageInfos() const
	{
		return descriptorImageInfos;
	}

	const std::vector<vk::WriteDescriptorSet>& RendererPipeline::getWriteDescriptorSets() const
	{
		return writeDescriptorSets;
	}

	const PipelineLayout& RendererPipeline::getPipelineLayout() const
	{
		return pipelineLayout;
	}

	const zt::gl::Pipeline& RendererPipeline::getPipeline() const
	{
		return pipeline;
	}

}