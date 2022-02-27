#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class ShaderModule;
	class Device;

	class ZINET_GRAPHIC_LAYER_API PipelineLayout
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Pipeline Layout");

	public:

		PipelineLayout();
		PipelineLayout(const PipelineLayout& other) = default;
		PipelineLayout(PipelineLayout&& other) = default;

		PipelineLayout& operator = (const PipelineLayout& other) = default;
		PipelineLayout& operator = (PipelineLayout&& other) = default;

		~PipelineLayout() noexcept = default;

		vk::PipelineShaderStageCreateInfo& createShaderStageCreateInfo(ShaderModule& shaderModule);

		vk::PipelineVertexInputStateCreateInfo& createVertexInputStateCreateInfo();

		vk::PipelineInputAssemblyStateCreateInfo& createInputAssemblyStateCreateInfo();

		vk::PipelineViewportStateCreateInfo& createViewportStateCreateInfo();

		void setViewportSize(float width, float height);

		const vk::Viewport& getViewport() const;

		void setScissor(const vk::Rect2D& scissor);

		const vk::Rect2D& getScissor() const;

		vk::PipelineRasterizationStateCreateInfo& createRasterizationStateCreateInfo();

		vk::PipelineMultisampleStateCreateInfo& createMultisampleStateCreateInfo();

		vk::PipelineColorBlendAttachmentState& createColorBlendAttachmentState();

		vk::PipelineColorBlendStateCreateInfo& createColorBlendStateCreateInfo();

		vk::PipelineLayoutCreateInfo createPipelineLayoutCreateInfo();

		vk::raii::PipelineLayout& getInternal();

		void createPipelineLayout(Device& device);

	protected:

		vk::Viewport viewport;
		vk::Rect2D scissor;

		vk::PipelineShaderStageCreateInfo shaderStageCreateInfo;
		vk::PipelineVertexInputStateCreateInfo vertexInputStateCreateInfo;
		vk::PipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo;
		vk::PipelineViewportStateCreateInfo viewportStateCreateInfo;
		vk::PipelineRasterizationStateCreateInfo rasterizationStateCreateInfo;
		vk::PipelineMultisampleStateCreateInfo multisampleStateCreateInfo;
		vk::PipelineColorBlendAttachmentState colorBlendAttachmentState;
		vk::PipelineColorBlendStateCreateInfo colorBlendStateCreateInfo;

		vk::raii::PipelineLayout internal;
	};

}