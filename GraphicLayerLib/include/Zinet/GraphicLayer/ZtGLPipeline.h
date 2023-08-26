#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLPipelineLayout.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Device;

	class ZINET_GRAPHIC_LAYER_API Pipeline : public VulkanObject<vk::raii::Pipeline>
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Pipeline");

	public:

		Pipeline() = default;
		Pipeline(const Pipeline& other) = default;
		Pipeline(Pipeline&& other) = default;

		Pipeline& operator = (const Pipeline& other) = default;
		Pipeline& operator = (Pipeline&& other) = default;

		~Pipeline() noexcept = default;

		template<class VertexType>
		vk::GraphicsPipelineCreateInfo createGraphicsPipelineCreateInfo(
			PipelineLayout& pipelineLayout,
			RenderPass& renderPass, 
			std::vector<vk::PipelineShaderStageCreateInfo>& shaderStages);

		void create(Device& device, vk::GraphicsPipelineCreateInfo createInfo);

	};

	template<class VertexType>
	vk::GraphicsPipelineCreateInfo Pipeline::createGraphicsPipelineCreateInfo(PipelineLayout& pipelineLayout, RenderPass& renderPass, std::vector<vk::PipelineShaderStageCreateInfo>& shaderStages)
	{
		vk::GraphicsPipelineCreateInfo graphicsPipelineCreateInfo;
		graphicsPipelineCreateInfo.stageCount = 2;
		graphicsPipelineCreateInfo.pStages = shaderStages.data();
		graphicsPipelineCreateInfo.pVertexInputState = &pipelineLayout.createVertexInputStateCreateInfo<VertexType>();
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
		graphicsPipelineCreateInfo.pDepthStencilState = &pipelineLayout.createDepthStencilStateCreateInfo();

		return graphicsPipelineCreateInfo;
	}

}