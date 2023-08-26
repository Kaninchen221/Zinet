#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

namespace zt::gl
{
	class Device;

	class ZINET_GRAPHIC_LAYER_API DescriptorSets : public vk::raii::DescriptorSets
	{

	public:

		struct CreateBufferWriteDescriptorSetInfo
		{
			size_t descriptorSetIndex;
			const vk::DescriptorBufferInfo& descriptorBufferInfo;
			std::uint32_t binding;
			vk::DescriptorType descriptorType;
		};

		DescriptorSets() = default;
		DescriptorSets(const DescriptorSets& other) = default;
		DescriptorSets(DescriptorSets&& other) = default;

		DescriptorSets(Device& device, vk::DescriptorSetAllocateInfo& allocateInfo);

		DescriptorSets& operator = (const DescriptorSets& other) = default;
		DescriptorSets& operator = (DescriptorSets&& other) = default;

		~DescriptorSets() noexcept = default;

		vk::WriteDescriptorSet createBufferWriteDescriptorSet(const CreateBufferWriteDescriptorSetInfo& info);

		vk::WriteDescriptorSet createImageWriteDescriptorSet(size_t descriptorSetIndex, const vk::DescriptorImageInfo& descriptorImageInfo, std::uint32_t binding);

	};

}