#include "Zinet/GraphicLayer/ZtGLPipelineLayout.h"

#include "Zinet/GraphicLayer/ZtGLShaderModule.h"
#include "Zinet/GraphicLayer/ZtGLShaderType.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

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

	vk::PipelineShaderStageCreateInfo& PipelineLayout::createShaderStageCreateInfo(ShaderModule& shaderModule)
	{
		shaderStageCreateInfo.stage = ShaderTypeToVkShaderStage(shaderModule.getType());
		shaderStageCreateInfo.module = *shaderModule.getInternal();
		shaderStageCreateInfo.pName = "main";

		return shaderStageCreateInfo;
	}

	vk::PipelineVertexInputStateCreateInfo& PipelineLayout::createVertexInputStateCreateInfo()
	{
		vertexInputStateCreateInfo.vertexBindingDescriptionCount = 0;
		vertexInputStateCreateInfo.pVertexBindingDescriptions = nullptr;
		vertexInputStateCreateInfo.vertexAttributeDescriptionCount = 0;
		vertexInputStateCreateInfo.pVertexAttributeDescriptions = nullptr;

		return vertexInputStateCreateInfo;
	}

	vk::PipelineInputAssemblyStateCreateInfo& PipelineLayout::createInputAssemblyStateCreateInfo()
	{
		inputAssemblyStateCreateInfo.topology = vk::PrimitiveTopology::eTriangleList;
		inputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;

		return inputAssemblyStateCreateInfo;
	}

	vk::PipelineViewportStateCreateInfo& PipelineLayout::createViewportStateCreateInfo()
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

	void PipelineLayout::setScissor(const vk::Rect2D& scissor)
	{
		this->scissor = scissor;
	}

	const vk::Rect2D& PipelineLayout::getScissor() const
	{
		return scissor;
	}

	vk::PipelineRasterizationStateCreateInfo& PipelineLayout::createRasterizationStateCreateInfo()
	{
		rasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
		rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
		rasterizationStateCreateInfo.polygonMode = vk::PolygonMode::eFill;
		rasterizationStateCreateInfo.lineWidth = 1.0f;
		rasterizationStateCreateInfo.cullMode = vk::CullModeFlagBits::eBack;
		rasterizationStateCreateInfo.frontFace = vk::FrontFace::eClockwise;
		rasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;
		rasterizationStateCreateInfo.depthBiasConstantFactor = 0.0f;
		rasterizationStateCreateInfo.depthBiasClamp = 0.0f;
		rasterizationStateCreateInfo.depthBiasSlopeFactor = 0.0f;

		return rasterizationStateCreateInfo;
	}

	vk::PipelineMultisampleStateCreateInfo& PipelineLayout::createMultisampleStateCreateInfo()
	{
		multisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
		multisampleStateCreateInfo.rasterizationSamples = vk::SampleCountFlagBits::e1;
		multisampleStateCreateInfo.minSampleShading = 1.0f;
		multisampleStateCreateInfo.pSampleMask = nullptr;
		multisampleStateCreateInfo.alphaToCoverageEnable = VK_FALSE;
		multisampleStateCreateInfo.alphaToOneEnable = VK_FALSE;

		return multisampleStateCreateInfo;
	}

	vk::PipelineColorBlendAttachmentState& PipelineLayout::createColorBlendAttachmentState()
	{
		colorBlendAttachmentState.colorWriteMask =
			vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
		colorBlendAttachmentState.blendEnable = VK_FALSE;
		colorBlendAttachmentState.srcColorBlendFactor = vk::BlendFactor::eOne;
		colorBlendAttachmentState.dstColorBlendFactor = vk::BlendFactor::eZero;
		colorBlendAttachmentState.colorBlendOp = vk::BlendOp::eAdd;
		colorBlendAttachmentState.srcAlphaBlendFactor = vk::BlendFactor::eOne;
		colorBlendAttachmentState.dstAlphaBlendFactor = vk::BlendFactor::eZero;
		colorBlendAttachmentState.alphaBlendOp = vk::BlendOp::eAdd;

		return colorBlendAttachmentState;
	}

	vk::PipelineColorBlendStateCreateInfo& PipelineLayout::createColorBlendStateCreateInfo()
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
		layoutCreateInfo.setLayoutCount = 0;
		layoutCreateInfo.pSetLayouts = nullptr;
		layoutCreateInfo.pushConstantRangeCount = 0;
		layoutCreateInfo.pPushConstantRanges = nullptr;

		return layoutCreateInfo;
	}

	void PipelineLayout::createPipelineLayout(Device& device)
	{
		vk::PipelineLayoutCreateInfo createInfo = createPipelineLayoutCreateInfo();
		internal = std::move(vk::raii::PipelineLayout{ device.getInternal(), createInfo });
	}

}