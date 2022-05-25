#include "Zinet/GraphicLayer/ZtGLDescriptorPool.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorSetLayout.h"

namespace zt::gl
{
    vk::DescriptorPoolSize DescriptorPool::createPoolSize()
    {
        vk::DescriptorPoolSize poolSize;
        poolSize.descriptorCount = 1;

        return poolSize;
    }

    vk::DescriptorPoolCreateInfo DescriptorPool::createCreateInfo(const vk::DescriptorPoolSize& poolSize) const
    {
        vk::DescriptorPoolCreateInfo createInfo;
        createInfo.poolSizeCount = 1u;
        createInfo.pPoolSizes = &poolSize;
        createInfo.maxSets = 1u;
        createInfo.flags = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet;

        return createInfo;
    }

    vk::DescriptorSetAllocateInfo DescriptorPool::createDescriptorSetAllocateInfo(const DescriptorSetLayout& descriptorSetLayout) const
    {
        vk::DescriptorSetAllocateInfo allocateInfo;
        allocateInfo.descriptorPool = *getInternal();
        allocateInfo.descriptorSetCount = 1u;
        allocateInfo.pSetLayouts = &*descriptorSetLayout.getInternal();

        return allocateInfo;
    }

    void DescriptorPool::create(Device& device, const vk::DescriptorPoolCreateInfo& createInfo)
    {
        internal = std::move(vk::raii::DescriptorPool{ device.getInternal(), createInfo });
    }
}