#include "Zinet/GraphicLayer/ZtGLRendererPipeline.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

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

	Pipeline& RendererPipeline::getPipeline()
	{
		return pipeline;
	}

	const Pipeline& RendererPipeline::getPipeline() const
	{
		return pipeline;
	}

	void RendererPipeline::updateDescriptorSets(Device& device)
	{
		if (!writeDescriptorSets.empty())
			device->updateDescriptorSets(writeDescriptorSets, {} /* descriptorCopies */);
	}

	void RendererPipeline::createShadersModules(const std::span<Shader>& shaders, Device& device)
	{
		shadersModules.clear();
		shadersModules.reserve(shaders.size());
		for (const Shader& shader : shaders)
		{
			ShaderModule& shaderModule = shadersModules.emplace_back();
			vk::ShaderModuleCreateInfo shaderModuleCreateInfo = shaderModule.createShaderModuleCreateInfo(shader);
			shaderModule.create(device, shader.getType(), shaderModuleCreateInfo);
		}
	}

	void RendererPipeline::createShadersStages()
	{
		shadersStages.clear();
		shadersStages.reserve(shadersModules.size());
		for (ShaderModule& module : shadersModules)
		{
			shadersStages.push_back(pipelineLayout.createShaderStageCreateInfo(module));
		}
	}

	void RendererPipeline::createDescriptorSetLayouts(const std::span<RenderStates::Descriptor>& descriptors, Device& device)
	{
		if (descriptors.empty())
			return;

		bindings.clear();
		bindings.reserve(descriptors.size());
		for (const RenderStates::Descriptor& descriptor : descriptors)
		{
			vk::DescriptorSetLayoutBinding vkBinding = descriptor.toVkDescriptorSetLayoutBinding();
			bindings.push_back(vkBinding);
		}

		descriptorSetLayouts.clear();
		DescriptorSetLayout& descriptorSetLayout = descriptorSetLayouts.emplace_back();
		vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo = descriptorSetLayout.createDescriptorSetLayoutCreateInfo(bindings);
		descriptorSetLayout.create(device, descriptorSetLayoutCreateInfo);
	}

	void RendererPipeline::createPipelineLayout(Device& device, const vk::Extent2D& swapExtent)
	{
		pipelineLayout.setDescriptorSetLayouts(descriptorSetLayouts);

		pipelineLayout.setViewportSize(static_cast<float>(swapExtent.width), static_cast<float>(swapExtent.height));

		vk::Rect2D scissor;
		scissor.offset = vk::Offset2D{ 0, 0 };
		scissor.extent = swapExtent;
		pipelineLayout.setScissor(scissor);

		pipelineLayout.createColorBlendAttachmentState();

		vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo = pipelineLayout.createPipelineLayoutCreateInfo();
		pipelineLayout.create(device, pipelineLayoutCreateInfo);
	}

	void RendererPipeline::createDescriptors(const CreateInfo& createInfo)
	{
		createDescriptorPool(createInfo.renderStates.descriptors, createInfo.device);
		createDescriptorSets(createInfo.device);
		createWriteDescriptorSets(createInfo.renderStates, createInfo.drawInfo);
	}

	void RendererPipeline::createDescriptorPool(const std::span<RenderStates::Descriptor>& descriptors, Device& device)
	{
		if (descriptors.empty())
			return;

		// Create descriptor pool sizes
		std::map<DescriptorType, std::uint32_t> descriptorTypes;
		for (const RenderStates::Descriptor descriptor : descriptors)
		{
			std::uint32_t& poolSize = descriptorTypes[descriptor.descriptorType];
			poolSize++;
		}

		// Create vector of vk::DescriptorPoolSize
		std::vector<vk::DescriptorPoolSize> poolSizes;
		poolSizes.reserve(descriptorTypes.size());
		for (const std::pair<DescriptorType, std::uint32_t>& descriptorType : descriptorTypes)
		{
			vk::DescriptorPoolSize poolSize{
				DescriptorTypeToVkDescriptorType(descriptorType.first),
				descriptorType.second
			};

			poolSizes.emplace_back(poolSize);
		}

		descriptorSets.reset();
		descriptorPool.clear();
		descriptorPool = DescriptorPool{};
		vk::DescriptorPoolCreateInfo descriptorPoolCreateInfo = descriptorPool.createCreateInfo(poolSizes);
		descriptorPool.create(device, descriptorPoolCreateInfo);
	}

	void RendererPipeline::createDescriptorSets(Device& device)
	{
		if (descriptorPool == nullptr)
			return;

		const std::vector<vk::DescriptorSetLayout>& vkDescriptorSetLayouts = pipelineLayout.getVkDescriptorSetLayouts();
		vk::DescriptorSetAllocateInfo descriptorsSetsAllocateInfo = descriptorPool.createDescriptorSetAllocateInfo(vkDescriptorSetLayouts);
		descriptorSets = DescriptorSets{ device, descriptorsSetsAllocateInfo };
	}

	void RendererPipeline::createWriteDescriptorSets(const RenderStates& renderStates, const DrawInfo& drawInfo)
	{
		writeDescriptorSets.clear();
		writeDescriptorSets.reserve(drawInfo.uniformBuffers.size() + renderStates.images.size());
		createBufferWriteDescriptorSets(drawInfo.uniformBuffers);
		createImageWriteDescriptorSets(renderStates.images);
	}

	void RendererPipeline::createBufferWriteDescriptorSets(const std::span<const UniformBuffer> uniformBuffers)
	{
		descriptorBufferInfos.clear();
		writeDescriptorSets.reserve(uniformBuffers.size());
		descriptorBufferInfos.reserve(uniformBuffers.size());
		for (const UniformBuffer& uniformBuffer : uniformBuffers)
		{
			vk::DescriptorBufferInfo& descriptorBufferInfo = descriptorBufferInfos.emplace_back(uniformBuffer.createDescriptorBufferInfo());
			vk::WriteDescriptorSet writeDescriptorSet = descriptorSets->createBufferWriteDescriptorSet(0u, descriptorBufferInfo, uniformBuffer.getBinding());
			writeDescriptorSets.push_back(writeDescriptorSet);
		}
	}

	void RendererPipeline::createImageWriteDescriptorSets(const std::span<RenderStates::Image>& images)
	{
		descriptorImageInfos.clear();
		for (std::size_t index = 0u; index < images.size(); ++index)
		{
			const ImageBuffer& imageBuffer = images[index].buffer;
			const Sampler& sampler = images[index].sampler;
			const ImageView& imageView = images[index].view;
			vk::ImageLayout imageLayout = images[index].layout;
			vk::DescriptorImageInfo& descriptorImageInfo = descriptorImageInfos.emplace_back(imageBuffer.createDescriptorImageInfo(sampler, imageView, imageLayout));
			vk::WriteDescriptorSet writeDescriptorSet = descriptorSets->createImageWriteDescriptorSet(0u, descriptorImageInfo, images[index].binding);
			writeDescriptorSets.push_back(writeDescriptorSet);
		}
	}

	RendererPipeline::~RendererPipeline() noexcept
	{
		shadersModules.clear();
		shadersStages.clear();
		bindings.clear();
		descriptorSetLayouts.clear();
		descriptorSets.reset();
		descriptorPool.clear();
		descriptorBufferInfos.clear();
		descriptorImageInfos.clear();
		writeDescriptorSets.clear();
		pipelineLayout.clear();
		pipeline.clear();
	}

}