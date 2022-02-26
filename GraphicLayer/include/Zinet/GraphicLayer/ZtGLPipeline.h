#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class ShaderModule;

	class ZINET_GRAPHIC_LAYER_API Pipeline
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

		vk::PipelineShaderStageCreateInfo createShaderStageCreateInfo(ShaderModule& shaderModule);

		vk::PipelineVertexInputStateCreateInfo createVertexInputStateCreateInfo();

		vk::PipelineInputAssemblyStateCreateInfo createInputAssemblyStateCreateInfo();

		vk::PipelineViewportStateCreateInfo createViewportStateCreateInfo();

		void setViewportSize(float width, float height);

		const vk::Viewport& getViewport() const;

		void setScissor(const vk::Rect2D& scissor);

		const vk::Rect2D& getScissor() const;

		vk::PipelineRasterizationStateCreateInfo createRasterizationStateCreateInfo();

		vk::PipelineMultisampleStateCreateInfo createMultisampleStateCreateInfo();

		vk::PipelineColorBlendAttachmentState createColorBlendAttachmentStateTest();

		vk::PipelineColorBlendStateCreateInfo createColorBlendStateCreateInfo();

		vk::PipelineLayoutCreateInfo createPipelineLayoutCreateInfo();

		vk::raii::PipelineLayout& getPipelineLayout();

		void createPipelineLayout(vk::raii::Device& device);

	protected:

		vk::Viewport viewport;
		vk::Rect2D scissor;

		vk::PipelineColorBlendAttachmentState colorBlendAttachmentState;

		vk::raii::PipelineLayout pipelineLayout;
	};

}