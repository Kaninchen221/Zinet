#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorSetLayout.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"

#include "Zinet/Core/ZtLogger.h"
#include "Zinet/Core/ZtTypeTraits.h"

namespace zt::gl
{
	class ShaderModule;
	class Device;

	template <typename T>
	concept VertexConcept =
		zt::core::IsFunctionEqual<std::vector<vk::VertexInputBindingDescription>(*)()>(&T::GetInputBindingDescriptions) &&
		zt::core::IsFunctionEqual<std::vector<vk::VertexInputAttributeDescription>(*)()>(&T::GetInputAttributeDescriptions);

	class ZINET_GRAPHIC_LAYER_API PipelineLayout : public VulkanObject<vk::raii::PipelineLayout>
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Pipeline Layout");

	public:

		PipelineLayout();
		PipelineLayout(const PipelineLayout& other) = default;
		PipelineLayout(PipelineLayout&& other) = default;

		PipelineLayout& operator = (const PipelineLayout& other) = default;
		PipelineLayout& operator = (PipelineLayout&& other) = default;

		~PipelineLayout() noexcept = default;

		const vk::PipelineShaderStageCreateInfo& createShaderStageCreateInfo(ShaderModule& shaderModule);

		template<VertexConcept VertexType>
		const vk::PipelineVertexInputStateCreateInfo& createVertexInputStateCreateInfo();

		const vk::PipelineInputAssemblyStateCreateInfo& createInputAssemblyStateCreateInfo();

		const vk::PipelineViewportStateCreateInfo& createViewportStateCreateInfo();

		void setViewportSize(float width, float height);

		const vk::Viewport& getViewport() const;

		void setScissor(const vk::Rect2D& newScissor);

		const vk::Rect2D& getScissor() const;

		const vk::PipelineRasterizationStateCreateInfo& createRasterizationStateCreateInfo();

		const vk::PipelineMultisampleStateCreateInfo& createMultisampleStateCreateInfo();

		const vk::PipelineColorBlendAttachmentState& createColorBlendAttachmentState();

		const vk::PipelineColorBlendStateCreateInfo& createColorBlendStateCreateInfo();

		const vk::PipelineDepthStencilStateCreateInfo& createDepthStencilStateCreateInfo();

		vk::PipelineLayoutCreateInfo createPipelineLayoutCreateInfo();

		void create(Device& device, const vk::PipelineLayoutCreateInfo& createInfo);

		const std::vector<vk::DescriptorSetLayout>& getVkDescriptorSetLayouts() const;

		void setDescriptorSetLayouts(std::span<DescriptorSetLayout> descriptorSetLayouts);

	protected:

		vk::Viewport viewport;
		vk::Rect2D scissor;

		vk::PipelineShaderStageCreateInfo shaderStageCreateInfo;
		std::vector < vk::VertexInputBindingDescription> vertexInputBindingDescriptions;
		std::vector<vk::VertexInputAttributeDescription> vertexInputAttributeDescriptions;
		vk::PipelineVertexInputStateCreateInfo vertexInputStateCreateInfo;
		vk::PipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo;
		vk::PipelineViewportStateCreateInfo viewportStateCreateInfo;
		vk::PipelineRasterizationStateCreateInfo rasterizationStateCreateInfo;
		vk::PipelineMultisampleStateCreateInfo multisampleStateCreateInfo;
		vk::PipelineColorBlendAttachmentState colorBlendAttachmentState;
		vk::PipelineColorBlendStateCreateInfo colorBlendStateCreateInfo;
		vk::PipelineDepthStencilStateCreateInfo depthStencilStateCreateInfo;

		std::vector<vk::DescriptorSetLayout> vkDescriptorSetLayouts;
	};

	template<VertexConcept VertexType>
	const vk::PipelineVertexInputStateCreateInfo& PipelineLayout::createVertexInputStateCreateInfo()
	{
		vertexInputBindingDescriptions = Vertex::GetInputBindingDescriptions();
		vertexInputAttributeDescriptions = Vertex::GetInputAttributeDescriptions();
	
		vertexInputStateCreateInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(vertexInputBindingDescriptions.size());
		vertexInputStateCreateInfo.pVertexBindingDescriptions = vertexInputBindingDescriptions.data();
		vertexInputStateCreateInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInputAttributeDescriptions.size());
		vertexInputStateCreateInfo.pVertexAttributeDescriptions = vertexInputAttributeDescriptions.data();
	
		return vertexInputStateCreateInfo;
	}

}