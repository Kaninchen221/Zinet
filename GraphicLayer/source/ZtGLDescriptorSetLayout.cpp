#include "Zinet/GraphicLayer/ZtGLDescriptorSetLayout.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorPool.h"

namespace zt::gl
{
    void DescriptorSetLayout::createDescriptorSetLayoutBinding()
    {
        descriptorSetLayoutBinding.binding = 0;
        descriptorSetLayoutBinding.descriptorType = vk::DescriptorType::eUniformBuffer;
        descriptorSetLayoutBinding.descriptorCount = 1;
        descriptorSetLayoutBinding.stageFlags = vk::ShaderStageFlagBits::eVertex;
        descriptorSetLayoutBinding.pImmutableSamplers = nullptr;
    }

    const vk::DescriptorSetLayoutBinding& DescriptorSetLayout::getDescriptorSetLayoutBinding() const
    {
        return descriptorSetLayoutBinding;
    }

    vk::DescriptorSetLayoutCreateInfo DescriptorSetLayout::createDescriptorSetLayoutCreateInfo()
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