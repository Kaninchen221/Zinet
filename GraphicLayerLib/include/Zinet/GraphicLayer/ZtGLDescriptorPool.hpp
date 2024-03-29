#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"

namespace zt::gl
{
	class Device;
	class DescriptorSetLayout;

	class ZINET_GRAPHIC_LAYER_API DescriptorPool : public VulkanObject<vk::raii::DescriptorPool>
	{

	public:

		DescriptorPool() = default;
		DescriptorPool(const DescriptorPool& other) = default;
		DescriptorPool(DescriptorPool&& other) = default;

		DescriptorPool& operator = (const DescriptorPool& other) = default;
		DescriptorPool& operator = (DescriptorPool&& other) = default;

		~DescriptorPool() noexcept = default;

		vk::DescriptorPoolSize createUniformPoolSize();

		vk::DescriptorPoolSize createImageSamplerPoolSize();

		vk::DescriptorPoolCreateInfo createCreateInfo(const std::vector<vk::DescriptorPoolSize>& poolSizes) const;

		vk::DescriptorSetAllocateInfo createDescriptorSetAllocateInfo(const std::vector<vk::DescriptorSetLayout>& descriptorSetLayouts) const;

		void create(Device& device, const vk::DescriptorPoolCreateInfo& createInfo);

	};

}