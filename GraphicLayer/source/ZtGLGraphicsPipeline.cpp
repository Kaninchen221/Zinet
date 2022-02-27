#include "Zinet/GraphicLayer/ZtGLGraphicsPipeline.h"

#include "Zinet/GraphicLayer/ZtGLPipeline.h"
#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{
	GraphicsPipeline::GraphicsPipeline()
		: internal(std::nullptr_t{})
	{

	}

	vk::GraphicsPipelineCreateInfo GraphicsPipeline::createGraphicsPipelineCreateInfo(
		Pipeline& pipeline, 
		RenderPass& renderPass, 
		std::vector<vk::PipelineShaderStageCreateInfo>& shaderStages)
	{
		vk::GraphicsPipelineCreateInfo graphicsPipelineCreateInfo;
		graphicsPipelineCreateInfo.stageCount = 2;
		graphicsPipelineCreateInfo.pStages = shaderStages.data();
		graphicsPipelineCreateInfo.pVertexInputState = &pipeline.createVertexInputStateCreateInfo();
		graphicsPipelineCreateInfo.pInputAssemblyState = &pipeline.createInputAssemblyStateCreateInfo();
		graphicsPipelineCreateInfo.pViewportState = &pipeline.createViewportStateCreateInfo();
		graphicsPipelineCreateInfo.pRasterizationState = &pipeline.createRasterizationStateCreateInfo();
		graphicsPipelineCreateInfo.pMultisampleState = &pipeline.createMultisampleStateCreateInfo();
		graphicsPipelineCreateInfo.pDepthStencilState = nullptr;
		graphicsPipelineCreateInfo.pColorBlendState = &pipeline.createColorBlendStateCreateInfo();
		graphicsPipelineCreateInfo.pDynamicState = nullptr;
		graphicsPipelineCreateInfo.layout = *pipeline.getInternal();
		graphicsPipelineCreateInfo.renderPass = *renderPass.getInternal();
		graphicsPipelineCreateInfo.subpass = 0;
		graphicsPipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
		graphicsPipelineCreateInfo.basePipelineIndex = -1;

		return graphicsPipelineCreateInfo;
	}

	vk::raii::Pipeline& GraphicsPipeline::getInternal()
	{
		return internal;
	}

	void GraphicsPipeline::create(Device& device, vk::GraphicsPipelineCreateInfo createInfo)
	{
		internal = std::move(vk::raii::Pipeline(device.getInternal(), nullptr, createInfo));
	}
}