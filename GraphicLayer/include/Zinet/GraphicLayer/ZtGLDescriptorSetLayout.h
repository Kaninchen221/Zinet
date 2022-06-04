#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

namespace zt::gl
{
	class Device;
	class DescriptorPool;

	class ZINET_GRAPHIC_LAYER_API DescriptorSetLayout : public VulkanObject<vk::raii::DescriptorSetLayout>
	{

	public:

		DescriptorSetLayout() = default;
		DescriptorSetLayout(const DescriptorSetLayout& other) = default;
		DescriptorSetLayout(DescriptorSetLayout&& other) = default;

		DescriptorSetLayout& operator = (const DescriptorSetLayout& other) = default;
		DescriptorSetLayout& operator = (DescriptorSetLayout&& other) = default;

		~DescriptorSetLayout() noexcept = default;

		vk::DescriptorSetLayoutBinding createDescriptorSetLayoutBinding();

		vk::DescriptorSetLayoutCreateInfo createDescriptorSetLayoutCreateInfo(const vk::DescriptorSetLayoutBinding& descriptorSetLayoutBinding);

		void create(Device& device, const vk::DescriptorSetLayoutCreateInfo& createInfo);

	};

}