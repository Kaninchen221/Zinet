#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

namespace zt::gl
{
	class Device;

	class ZINET_GRAPHIC_LAYER_API DescriptorSets : public vk::raii::DescriptorSets
	{

	public:

		DescriptorSets() = default;
		DescriptorSets(const DescriptorSets& other) = default;
		DescriptorSets(DescriptorSets&& other) = default;

		DescriptorSets(Device& device, vk::DescriptorSetAllocateInfo& allocateInfo);

		DescriptorSets& operator = (const DescriptorSets& other) = default;
		DescriptorSets& operator = (DescriptorSets&& other) = default;

		~DescriptorSets() noexcept = default;

		vk::WriteDescriptorSet createWriteDescriptorSet(size_t DescriptorSetIndex, vk::DescriptorBufferInfo& descriptorBufferInfo);
	};

}