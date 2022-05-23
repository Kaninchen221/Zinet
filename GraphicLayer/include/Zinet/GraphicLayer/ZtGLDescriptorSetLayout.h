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

		void createDescriptorSetLayoutBinding();

		const vk::DescriptorSetLayoutBinding& getDescriptorSetLayoutBinding() const;

		vk::DescriptorSetLayoutCreateInfo createDescriptorSetLayoutCreateInfo();

		vk::DescriptorSetAllocateInfo createAllocateInfo(const DescriptorPool& descriptorPool) const; // TODO move it to DescriptorSet or DescriptorSets

		void create(Device& device, const vk::DescriptorSetLayoutCreateInfo& createInfo);

	protected:

		vk::DescriptorSetLayoutBinding descriptorSetLayoutBinding;

	};

}