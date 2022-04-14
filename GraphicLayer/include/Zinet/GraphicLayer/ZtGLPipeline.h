#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class PipelineLayout;
	class RenderPass;
	class Device;

	class ZINET_GRAPHIC_LAYER_API Pipeline : public VulkanObject<vk::raii::Pipeline>
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Pipeline");

	public:

		Pipeline();
		Pipeline(const Pipeline& other) = default;
		Pipeline(Pipeline&& other) = default;

		Pipeline& operator = (const Pipeline& other) = default;
		Pipeline& operator = (Pipeline&& other) = default;

		~Pipeline() noexcept = default;

		vk::GraphicsPipelineCreateInfo createGraphicsPipelineCreateInfo(
			PipelineLayout& pipelineLayout,
			RenderPass& renderPass, 
			std::vector<vk::PipelineShaderStageCreateInfo>& shaderStages);

		void create(Device& device, vk::GraphicsPipelineCreateInfo createInfo);

	};

}