#include "Zinet/GraphicLayer/ZtGLDescriptorSetLayout.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorPool.h"

namespace zt::gl
{
    vk::DescriptorSetLayoutBinding DescriptorSetLayout::createDescriptorSetLayoutBinding()
    {
        vk::DescriptorSetLayoutBinding descriptorSetLayoutBinding;
        descriptorSetLayoutBinding.binding = 0;
        descriptorSetLayoutBinding.descriptorType = vk::DescriptorType::eUniformBuffer;
        descriptorSetLayoutBinding.descriptorCount = 1;
        descriptorSetLayoutBinding.stageFlags = vk::ShaderStageFlagBits::eVertex;
        descriptorSetLayoutBinding.pImmutableSamplers = nullptr;

        return descriptorSetLayoutBinding;
    }

    vk::DescriptorSetLayoutCreateInfo DescriptorSetLayout::createDescriptorSetLayoutCreateInfo(const vk::DescriptorSetLayoutBinding& descriptorSetLayoutBinding)
    {
        vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo;
        descriptorSetLayoutCreateInfo.bindingCount = 1;
        descriptorSetLayoutCreateInfo.pBindings = &descriptorSetLayoutBinding;

        return descriptorSetLayoutCreateInfo;
    }

    void DescriptorSetLayout::create(Device& device, const vk::DescriptorSetLayoutCreateInfo& createInfo)
    {
        internal = std::move(vk::raii::DescriptorSetLayout{ device.getInternal(), createInfo });
    }
}