#include "Zinet/GraphicLayer/ZtGLPipeline.h"

#include "Zinet/GraphicLayer/ZtGLShaderModule.h"
#include "Zinet/GraphicLayer/ZtGLShaderType.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{
	Pipeline::Pipeline()
		: pipelineLayout(std::nullptr_t{})
	{
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = 100.f;
		viewport.height = 100.f;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

	}

	vk::PipelineShaderStageCreateInfo Pipeline::createShaderStageCreateInfo(ShaderModule& shaderModule)
	{
		vk::PipelineShaderStageCreateInfo createInfo{};
		createInfo.stage = ShaderTypeToVkShaderStage(shaderModule.getType());
		createInfo.module = *shaderModule.getInternal();
		createInfo.pName = "main";

		return createInfo;
	}

	vk::PipelineVertexInputStateCreateInfo Pipeline::createVertexInputStateCreateInfo()
	{
		vk::PipelineVertexInputStateCreateInfo createInfo{};
		createInfo.vertexBindingDescriptionCount = 0;
		createInfo.pVertexBindingDescriptions = nullptr;
		createInfo.vertexAttributeDescriptionCount = 0;
		createInfo.pVertexAttributeDescriptions = nullptr;

		return createInfo;
	}

	vk::PipelineInputAssemblyStateCreateInfo Pipeline::createInputAssemblyStateCreateInfo()
	{
		vk::PipelineInputAssemblyStateCreateInfo createInfo{};
		createInfo.topology = vk::PrimitiveTopology::eTriangleList;
		createInfo.primitiveRestartEnable = VK_FALSE;

		return createInfo;
	}

	vk::PipelineViewportStateCreateInfo Pipeline::createViewportStateCreateInfo()
	{
		vk::PipelineViewportStateCreateInfo createInfo{};
		createInfo.viewportCount = 1;
		createInfo.pViewports = &viewport;
		createInfo.scissorCount = 1;
		createInfo.pScissors = &scissor;

		return createInfo;
	}

	void Pipeline::setViewportSize(float width, float height)
	{
		viewport.width = width;
		viewport.height = height;
	}

	const vk::Viewport& Pipeline::getViewport() const
	{
		return viewport;
	}

	void Pipeline::setScissor(const vk::Rect2D& scissor)
	{
		this->scissor = scissor;
	}

	const vk::Rect2D& Pipeline::getScissor() const
	{
		return scissor;
	}

	vk::PipelineRasterizationStateCreateInfo Pipeline::createRasterizationStateCreateInfo()
	{
		vk::PipelineRasterizationStateCreateInfo createInfo{};
		createInfo.depthClampEnable = VK_FALSE;
		createInfo.rasterizerDiscardEnable = VK_FALSE;
		createInfo.polygonMode = vk::PolygonMode::eFill;
		createInfo.lineWidth = 1.0f;
		createInfo.cullMode = vk::CullModeFlagBits::eFront;
		createInfo.frontFace = vk::FrontFace::eClockwise; 
		createInfo.depthBiasEnable = VK_FALSE;
		createInfo.depthBiasConstantFactor = 0.0f;
		createInfo.depthBiasClamp = 0.0f;
		createInfo.depthBiasSlopeFactor = 0.0f;

		return createInfo;
	}

	vk::PipelineMultisampleStateCreateInfo Pipeline::createMultisampleStateCreateInfo()
	{
		vk::PipelineMultisampleStateCreateInfo createInfo{};
		createInfo.sampleShadingEnable = VK_FALSE;
		createInfo.rasterizationSamples = vk::SampleCountFlagBits::e1;
		createInfo.minSampleShading = 1.0f;
		createInfo.pSampleMask = nullptr;
		createInfo.alphaToCoverageEnable = VK_FALSE;
		createInfo.alphaToOneEnable = VK_FALSE;

		return createInfo;
	}

	vk::PipelineColorBlendAttachmentState Pipeline::createColorBlendAttachmentStateTest()
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

	vk::PipelineColorBlendStateCreateInfo Pipeline::createColorBlendStateCreateInfo()
	{
		vk::PipelineColorBlendStateCreateInfo createInfo{};
		createInfo.logicOpEnable = VK_FALSE;
		createInfo.logicOp = vk::LogicOp::eCopy;
		createInfo.attachmentCount = 1;
		createInfo.pAttachments = &colorBlendAttachmentState;
		createInfo.blendConstants[0] = 0.0f;
		createInfo.blendConstants[1] = 0.0f;
		createInfo.blendConstants[2] = 0.0f;
		createInfo.blendConstants[3] = 0.0f;

		return createInfo;
	}

	vk::PipelineLayoutCreateInfo Pipeline::createPipelineLayoutCreateInfo()
	{
		vk::PipelineLayoutCreateInfo createInfo{};
		createInfo.setLayoutCount = 0;
		createInfo.pSetLayouts = nullptr;
		createInfo.pushConstantRangeCount = 0;
		createInfo.pPushConstantRanges = nullptr;

		return createInfo;
	}

	vk::raii::PipelineLayout& Pipeline::getPipelineLayout()
	{
		return pipelineLayout;
	}

	void Pipeline::createPipelineLayout(Device& device)
	{
		vk::PipelineLayoutCreateInfo createInfo = createPipelineLayoutCreateInfo();
		pipelineLayout = std::move(vk::raii::PipelineLayout{ device.getInternal(), createInfo });
	}

}