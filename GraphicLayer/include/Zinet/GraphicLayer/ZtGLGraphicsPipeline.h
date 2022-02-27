#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Pipeline;
	class RenderPass;
	class Device;

	class ZINET_GRAPHIC_LAYER_API GraphicsPipeline
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Graphics Pipeline");

	public:

		GraphicsPipeline();
		GraphicsPipeline(const GraphicsPipeline& other) = default;
		GraphicsPipeline(GraphicsPipeline&& other) = default;

		GraphicsPipeline& operator = (const GraphicsPipeline& other) = default;
		GraphicsPipeline& operator = (GraphicsPipeline&& other) = default;

		~GraphicsPipeline() noexcept = default;

		vk::GraphicsPipelineCreateInfo createGraphicsPipelineCreateInfo(
			Pipeline& pipeline, 
			RenderPass& renderPass, 
			std::vector<vk::PipelineShaderStageCreateInfo>& shaderStages);

		vk::raii::Pipeline& getInternal();

		void create(Device& device, vk::GraphicsPipelineCreateInfo createInfo);

	protected:

		vk::raii::Pipeline internal;

	};

}