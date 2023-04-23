#include "Zinet/GraphicLayer/ZtGLPipelineLayout.h"

#include "Zinet/GraphicLayer/ZtGLShaderModule.h"
#include "Zinet/GraphicLayer/ZtGLShaderType.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"

namespace zt::gl
{
	PipelineLayout::PipelineLayout()
	{
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = 100.f;
		viewport.height = 100.f;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

	}

	const vk::PipelineShaderStageCreateInfo& PipelineLayout::createShaderStageCreateInfo(ShaderModule& shaderModule)
	{
		shaderStageCreateInfo.stage = ShaderTypeToVkShaderStage(shaderModule.getType());
		shaderStageCreateInfo.module = *shaderModule.getInternal();
		shaderStageCreateInfo.pName = "main";

		return shaderStageCreateInfo;
	}

	const vk::PipelineVertexInputStateCreateInfo& PipelineLayout::createVertexInputStateCreateInfo()
	{
		vertexInputBindingDescription = Vertex::CreateInputBindingDescription();

		vertexInputAttributeDescriptions.push_back(Vertex::CreatePositionInputAttributeDescription());
		vertexInputAttributeDescriptions.push_back(Vertex::CreateColorInputAttributeDescription());
		vertexInputAttributeDescriptions.push_back(Vertex::CreateTextureCoordinatesInputAttributeDescription());

		vertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;
		vertexInputStateCreateInfo.pVertexBindingDescriptions = &vertexInputBindingDescription;
		vertexInputStateCreateInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInputAttributeDescriptions.size());
		vertexInputStateCreateInfo.pVertexAttributeDescriptions = vertexInputAttributeDescriptions.data();

		return vertexInputStateCreateInfo;
	}

	const vk::PipelineInputAssemblyStateCreateInfo& PipelineLayout::createInputAssemblyStateCreateInfo()
	{
		inputAssemblyStateCreateInfo.topology = vk::PrimitiveTopology::eTriangleList;
		inputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;

		return inputAssemblyStateCreateInfo;
	}

	const vk::PipelineViewportStateCreateInfo& PipelineLayout::createViewportStateCreateInfo()
	{
		viewportStateCreateInfo.viewportCount = 1;
		viewportStateCreateInfo.pViewports = &viewport;
		viewportStateCreateInfo.scissorCount = 1;
		viewportStateCreateInfo.pScissors = &scissor;

		return viewportStateCreateInfo;
	}

	void PipelineLayout::setViewportSize(float width, float height)
	{
		viewport.width = width;
		viewport.height = height;
	}

	const vk::Viewport& PipelineLayout::getViewport() const
	{
		return viewport;
	}

	void PipelineLayout::setScissor(const vk::Rect2D& newScissor)
	{
		scissor = newScissor;
	}

	const vk::Rect2D& PipelineLayout::getScissor() const
	{
		return scissor;
	}

	const vk::PipelineRasterizationStateCreateInfo& PipelineLayout::createRasterizationStateCreateInfo()
	{
		rasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
		rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
		rasterizationStateCreateInfo.polygonMode = vk::PolygonMode::eFill;
		rasterizationStateCreateInfo.lineWidth = 1.0f;
		rasterizationStateCreateInfo.cullMode = vk::CullModeFlagBits::eBack;
		//rasterizationStateCreateInfo.cullMode = vk::CullModeFlagBits::eNone; // For debug purpose
		rasterizationStateCreateInfo.frontFace = vk::FrontFace::eCounterClockwise;
		rasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;
		rasterizationStateCreateInfo.depthBiasConstantFactor = 0.0f;
		rasterizationStateCreateInfo.depthBiasClamp = 0.0f;
		rasterizationStateCreateInfo.depthBiasSlopeFactor = 0.0f;

		return rasterizationStateCreateInfo;
	}

	const vk::PipelineMultisampleStateCreateInfo& PipelineLayout::createMultisampleStateCreateInfo()
	{
		multisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
		multisampleStateCreateInfo.rasterizationSamples = vk::SampleCountFlagBits::e1;
		multisampleStateCreateInfo.minSampleShading = 1.0f;
		multisampleStateCreateInfo.pSampleMask = nullptr;
		multisampleStateCreateInfo.alphaToCoverageEnable = VK_FALSE;
		multisampleStateCreateInfo.alphaToOneEnable = VK_FALSE;

		return multisampleStateCreateInfo;
	}

	const vk::PipelineColorBlendAttachmentState& PipelineLayout::createColorBlendAttachmentState()
	{
		colorBlendAttachmentState.colorWriteMask =
			vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
		colorBlendAttachmentState.blendEnable = VK_TRUE;
		colorBlendAttachmentState.srcColorBlendFactor = vk::BlendFactor::eSrcAlpha;
		colorBlendAttachmentState.dstColorBlendFactor = vk::BlendFactor::eOneMinusSrcAlpha;
		colorBlendAttachmentState.colorBlendOp = vk::BlendOp::eAdd;
		colorBlendAttachmentState.srcAlphaBlendFactor = vk::BlendFactor::eSrcAlpha;
		colorBlendAttachmentState.dstAlphaBlendFactor = vk::BlendFactor::eOneMinusSrcAlpha;
		colorBlendAttachmentState.alphaBlendOp = vk::BlendOp::eAdd;

		return colorBlendAttachmentState;
	}

	const vk::PipelineColorBlendStateCreateInfo& PipelineLayout::createColorBlendStateCreateInfo()
	{
		colorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
		colorBlendStateCreateInfo.logicOp = vk::LogicOp::eCopy;
		colorBlendStateCreateInfo.attachmentCount = 1;
		colorBlendStateCreateInfo.pAttachments = &colorBlendAttachmentState;
		colorBlendStateCreateInfo.blendConstants[0] = 0.0f;
		colorBlendStateCreateInfo.blendConstants[1] = 0.0f;
		colorBlendStateCreateInfo.blendConstants[2] = 0.0f;
		colorBlendStateCreateInfo.blendConstants[3] = 0.0f;

		return colorBlendStateCreateInfo;
	}

	vk::PipelineLayoutCreateInfo PipelineLayout::createPipelineLayoutCreateInfo()
	{
		vk::PipelineLayoutCreateInfo layoutCreateInfo;
		layoutCreateInfo.setLayoutCount = static_cast<uint32_t>(vkDescriptorSetLayouts.size());
		layoutCreateInfo.pSetLayouts = vkDescriptorSetLayouts.data();
		layoutCreateInfo.pushConstantRangeCount = 0;
		layoutCreateInfo.pPushConstantRanges = nullptr;

		return layoutCreateInfo;
	}

	void PipelineLayout::create(Device& device, const vk::PipelineLayoutCreateInfo& createInfo)
	{
		internal = std::move(vk::raii::PipelineLayout{ device.getInternal(), createInfo });
	}

	const std::vector<vk::DescriptorSetLayout>& PipelineLayout::getVkDescriptorSetLayouts() const
	{
		return vkDescriptorSetLayouts;
	}

	void PipelineLayout::setDescriptorSetLayouts(std::span<DescriptorSetLayout> descriptorSetLayouts)
	{
		vkDescriptorSetLayouts.clear();
		for (DescriptorSetLayout& descriptorSetLayout : descriptorSetLayouts)
		{
			vkDescriptorSetLayouts.push_back(*descriptorSetLayout.getInternal());
		}
	}

}