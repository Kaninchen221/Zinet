#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGLShaderModule.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorSetLayout.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorSets.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorPool.h"
#include "Zinet/GraphicLayer/ZtGLPipelineLayout.h"
#include "Zinet/GraphicLayer/ZtGLPipeline.h"
#include "Zinet/GraphicLayer/ZtGLDrawInfo.h"

#include "Zinet/Core/ZtLogger.h"

#include <map>

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API RendererPipeline
	{

	public:

		struct ZINET_GRAPHIC_LAYER_API CreateInfo
		{
			const DrawInfo& drawInfo;
			Device& device;
			RenderPass& renderPass;
			const vk::Extent2D& swapExtent;
		};

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("RendererPipeline");

	public:

		RendererPipeline() = default;
		RendererPipeline(const RendererPipeline& other) = default;
		RendererPipeline(RendererPipeline&& other) = default;

		RendererPipeline& operator = (const RendererPipeline& other) = default;
		RendererPipeline& operator = (RendererPipeline&& other) = default;

		~RendererPipeline() noexcept = default;

		const std::vector<ShaderModule>& getShadersModules() const;

		const std::vector<vk::PipelineShaderStageCreateInfo>& getShadersStages() const;

		const std::vector<vk::DescriptorSetLayoutBinding>& getBindings() const;

		const std::vector<DescriptorSetLayout>& getDescriptorSetLayouts() const;

		const std::optional<DescriptorSets>& getDescriptorSets() const;

		const DescriptorPool& getDescriptorPool() const;

		const std::vector<vk::DescriptorBufferInfo>& getDescriptorBufferInfos() const;

		const std::vector<vk::DescriptorImageInfo>& getDescriptorImageInfos() const;

		const std::vector<vk::WriteDescriptorSet>& getWriteDescriptorSets() const;

		const PipelineLayout& getPipelineLayout() const;

		Pipeline& getPipeline();
		const Pipeline& getPipeline() const;

		void create(const CreateInfo& createInfo);

		void updateDescriptorSets(Device& device);

	protected:

		std::vector<ShaderModule> shadersModules;
		std::vector<vk::PipelineShaderStageCreateInfo> shadersStages;
		std::vector<vk::DescriptorSetLayoutBinding> bindings;
		std::vector<DescriptorSetLayout> descriptorSetLayouts;
		std::optional<DescriptorSets> descriptorSets;
		DescriptorPool descriptorPool;
		std::vector<vk::DescriptorBufferInfo> descriptorBufferInfos;
		std::vector<vk::DescriptorImageInfo> descriptorImageInfos;
		std::vector<vk::WriteDescriptorSet> writeDescriptorSets;
		PipelineLayout pipelineLayout;
		Pipeline pipeline;

		void createPipeline(const CreateInfo& createInfo);
		void createShadersModules(const std::span<Shader>& shaders, Device& device);
		void createShadersStages();
		void createDescriptorSetLayouts(const std::span<DrawInfo::Descriptor>& descriptors, Device& device);
		void createPipelineLayout(Device& device, const vk::Extent2D& swapExtent);

		void createDescriptors(const CreateInfo& createInfo);
		void createDescriptorPool(const std::span<DrawInfo::Descriptor>& descriptors, Device& device);
		void createDescriptorSets(Device& device);
		void createWriteDescriptorSets(const DrawInfo& drawInfo);
		void createBufferWriteDescriptorSets(const std::span<UniformBuffer>& uniformBuffers);
		void createImageWriteDescriptorSets(const std::span<DrawInfo::Image>& images);
	};

}