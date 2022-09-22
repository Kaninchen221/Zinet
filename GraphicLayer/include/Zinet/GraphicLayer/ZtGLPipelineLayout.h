#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorSetLayout.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class ShaderModule;
	class Device;

	class ZINET_GRAPHIC_LAYER_API PipelineLayout : public VulkanObject<vk::raii::PipelineLayout>
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

		const vk::PipelineShaderStageCreateInfo& createShaderStageCreateInfo(ShaderModule& shaderModule);

		const vk::PipelineVertexInputStateCreateInfo& createVertexInputStateCreateInfo();

		const vk::PipelineInputAssemblyStateCreateInfo& createInputAssemblyStateCreateInfo();

		const vk::PipelineViewportStateCreateInfo& createViewportStateCreateInfo();

		void setViewportSize(float width, float height);

		const vk::Viewport& getViewport() const;

		void setScissor(const vk::Rect2D& scissor);

		const vk::Rect2D& getScissor() const;

		const vk::PipelineRasterizationStateCreateInfo& createRasterizationStateCreateInfo();

		const vk::PipelineMultisampleStateCreateInfo& createMultisampleStateCreateInfo();

		const vk::PipelineColorBlendAttachmentState& createColorBlendAttachmentState();

		const vk::PipelineColorBlendStateCreateInfo& createColorBlendStateCreateInfo();

		const vk::PipelineLayoutCreateInfo createPipelineLayoutCreateInfo();

		void create(Device& device);

		const std::vector<vk::DescriptorSetLayout>& getDescriptorSetLayouts() const;

	protected:

		vk::Viewport viewport;
		vk::Rect2D scissor;

		vk::PipelineShaderStageCreateInfo shaderStageCreateInfo;
		vk::VertexInputBindingDescription vertexInputBindingDescription;
		std::vector<vk::VertexInputAttributeDescription> vertexInputAttributeDescriptions;
		vk::PipelineVertexInputStateCreateInfo vertexInputStateCreateInfo;
		vk::PipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo;
		vk::PipelineViewportStateCreateInfo viewportStateCreateInfo;
		vk::PipelineRasterizationStateCreateInfo rasterizationStateCreateInfo;
		vk::PipelineMultisampleStateCreateInfo multisampleStateCreateInfo;
		vk::PipelineColorBlendAttachmentState colorBlendAttachmentState;
		vk::PipelineColorBlendStateCreateInfo colorBlendStateCreateInfo;
		
		DescriptorSetLayout descriptorSetLayout;
		std::vector<vk::DescriptorSetLayout> descriptorSetLayouts;
	};

}