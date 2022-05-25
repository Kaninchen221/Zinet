#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

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

		vk::DescriptorPoolSize createPoolSize();

		vk::DescriptorPoolCreateInfo createCreateInfo(const vk::DescriptorPoolSize& poolSize) const;

		vk::DescriptorSetAllocateInfo createDescriptorSetAllocateInfo(const DescriptorSetLayout& descriptorSetLayout) const;

		void create(Device& device, const vk::DescriptorPoolCreateInfo& createInfo);

	};

}