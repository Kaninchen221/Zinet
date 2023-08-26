#include "Zinet/GraphicLayer/ZtGLDescriptorSets.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{

	DescriptorSets::DescriptorSets(Device& device, vk::DescriptorSetAllocateInfo& allocateInfo)
		: vk::raii::DescriptorSets{ device.getInternal(), allocateInfo }
	{

	}

	vk::WriteDescriptorSet DescriptorSets::createBufferWriteDescriptorSet(const CreateBufferWriteDescriptorSetInfo& info)
	{
		vk::WriteDescriptorSet writeDescriptorSet;
		writeDescriptorSet.dstSet = *operator[](info.descriptorSetIndex);
		writeDescriptorSet.dstBinding = info.binding;
		writeDescriptorSet.dstArrayElement = 0;
		writeDescriptorSet.descriptorType = info.descriptorType;
		writeDescriptorSet.descriptorCount = 1;
		writeDescriptorSet.pBufferInfo = &info.descriptorBufferInfo;
		writeDescriptorSet.pImageInfo = nullptr;
		writeDescriptorSet.pTexelBufferView = nullptr;

		return writeDescriptorSet;
	}

	vk::WriteDescriptorSet DescriptorSets::createImageWriteDescriptorSet(size_t descriptorSetIndex, const vk::DescriptorImageInfo& descriptorImageInfo, std::uint32_t binding)
	{
		vk::WriteDescriptorSet writeDescriptorSet;
		writeDescriptorSet.dstSet = *operator[](descriptorSetIndex);
		writeDescriptorSet.dstBinding = binding;
		writeDescriptorSet.dstArrayElement = 0;
		writeDescriptorSet.descriptorType = vk::DescriptorType::eCombinedImageSampler;
		writeDescriptorSet.descriptorCount = 1;
		writeDescriptorSet.pBufferInfo = nullptr;
		writeDescriptorSet.pImageInfo = &descriptorImageInfo;
		writeDescriptorSet.pTexelBufferView = nullptr;

		return writeDescriptorSet;
	}

}