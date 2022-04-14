#include "Zinet/GraphicLayer/ZtGLPipeline.h"

#include "Zinet/GraphicLayer/ZtGLPipelineLayout.h"
#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{
	Pipeline::Pipeline()
	{

	}

	vk::GraphicsPipelineCreateInfo Pipeline::createGraphicsPipelineCreateInfo(
		PipelineLayout& pipelineLayout,
		RenderPass& renderPass, 
		std::vector<vk::PipelineShaderStageCreateInfo>& shaderStages)
	{
		vk::GraphicsPipelineCreateInfo graphicsPipelineCreateInfo;
		graphicsPipelineCreateInfo.stageCount = 2;
		graphicsPipelineCreateInfo.pStages = shaderStages.data();
		graphicsPipelineCreateInfo.pVertexInputState = &pipelineLayout.createVertexInputStateCreateInfo();
		graphicsPipelineCreateInfo.pInputAssemblyState = &pipelineLayout.createInputAssemblyStateCreateInfo();
		graphicsPipelineCreateInfo.pViewportState = &pipelineLayout.createViewportStateCreateInfo();
		graphicsPipelineCreateInfo.pRasterizationState = &pipelineLayout.createRasterizationStateCreateInfo();
		graphicsPipelineCreateInfo.pMultisampleState = &pipelineLayout.createMultisampleStateCreateInfo();
		graphicsPipelineCreateInfo.pDepthStencilState = nullptr;
		graphicsPipelineCreateInfo.pColorBlendState = &pipelineLayout.createColorBlendStateCreateInfo();
		graphicsPipelineCreateInfo.pDynamicState = nullptr;
		graphicsPipelineCreateInfo.layout = *pipelineLayout.getInternal();
		graphicsPipelineCreateInfo.renderPass = *renderPass.getInternal();
		graphicsPipelineCreateInfo.subpass = 0;
		graphicsPipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
		graphicsPipelineCreateInfo.basePipelineIndex = -1;

		return graphicsPipelineCreateInfo;
	}

	void Pipeline::create(Device& device, vk::GraphicsPipelineCreateInfo createInfo)
	{
		internal = std::move(vk::raii::Pipeline(device.getInternal(), nullptr, createInfo));
	}
}