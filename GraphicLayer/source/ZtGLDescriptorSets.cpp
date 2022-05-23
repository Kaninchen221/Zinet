#include "Zinet/GraphicLayer/ZtGLDescriptorSets.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{

	DescriptorSets::DescriptorSets(Device& device, vk::DescriptorSetAllocateInfo& allocateInfo)
		: vk::raii::DescriptorSets{ device.getInternal(), allocateInfo }
	{

	}

	vk::WriteDescriptorSet DescriptorSets::createWriteDescriptorSet(size_t DescriptorSetIndex, vk::DescriptorBufferInfo& descriptorBufferInfo)
	{
		vk::WriteDescriptorSet writeDescriptorSet;
		writeDescriptorSet.dstSet = *operator[](DescriptorSetIndex);
		writeDescriptorSet.dstBinding = 0;
		writeDescriptorSet.dstArrayElement = 0;
		writeDescriptorSet.descriptorType = vk::DescriptorType::eUniformBuffer;
		writeDescriptorSet.descriptorCount = 1;
		writeDescriptorSet.pBufferInfo = &descriptorBufferInfo;
		writeDescriptorSet.pImageInfo = nullptr;
		writeDescriptorSet.pTexelBufferView = nullptr;

		return writeDescriptorSet;
	}

}