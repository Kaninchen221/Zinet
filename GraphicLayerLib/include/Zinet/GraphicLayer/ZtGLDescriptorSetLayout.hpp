#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"

namespace zt::gl
{
	class Device;

	class ZINET_GRAPHIC_LAYER_API DescriptorSetLayout : public VulkanObject<vk::raii::DescriptorSetLayout>
	{

	public:

		DescriptorSetLayout() = default;
		DescriptorSetLayout(const DescriptorSetLayout& other) = default;
		DescriptorSetLayout(DescriptorSetLayout&& other) = default;

		DescriptorSetLayout& operator = (const DescriptorSetLayout& other) = default;
		DescriptorSetLayout& operator = (DescriptorSetLayout&& other) = default;

		~DescriptorSetLayout() noexcept = default;

		vk::DescriptorSetLayoutBinding createUniformLayoutBinding();

		vk::DescriptorSetLayoutBinding createImageSamplerLayoutBinding();

		vk::DescriptorSetLayoutCreateInfo createDescriptorSetLayoutCreateInfo(const std::vector<vk::DescriptorSetLayoutBinding>& bindings);

		void create(Device& device, const vk::DescriptorSetLayoutCreateInfo& createInfo);

	};

}