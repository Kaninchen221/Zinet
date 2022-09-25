#include "Zinet/GraphicLayer/ZtGLDescriptorPool.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorSetLayout.h"

namespace zt::gl
{
    vk::DescriptorPoolSize DescriptorPool::createUniformPoolSize()
    {
        vk::DescriptorPoolSize poolSize;
        poolSize.type = vk::DescriptorType::eUniformBuffer;
        poolSize.descriptorCount = 1;

        return poolSize;
    }

    vk::DescriptorPoolSize DescriptorPool::createImageSamplerPoolSize()
    {
        vk::DescriptorPoolSize poolSize;
        poolSize.type = vk::DescriptorType::eCombinedImageSampler;
        poolSize.descriptorCount = 1;

        return poolSize;
    }

    vk::DescriptorPoolCreateInfo DescriptorPool::createCreateInfo(const std::vector<vk::DescriptorPoolSize>& poolSizes) const
    {
        vk::DescriptorPoolCreateInfo createInfo;
        createInfo.poolSizeCount = poolSizes.size();
        createInfo.pPoolSizes = poolSizes.data();
        createInfo.maxSets = 1u;
        createInfo.flags = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet;

        return createInfo;
    }

    vk::DescriptorSetAllocateInfo DescriptorPool::createDescriptorSetAllocateInfo(const std::vector<vk::DescriptorSetLayout>& descriptorSetLayouts) const
    {
        vk::DescriptorSetAllocateInfo allocateInfo;
        allocateInfo.descriptorPool = *getInternal();
        allocateInfo.descriptorSetCount = descriptorSetLayouts.size();
        allocateInfo.pSetLayouts = descriptorSetLayouts.data();

        return allocateInfo;
    }

    void DescriptorPool::create(Device& device, const vk::DescriptorPoolCreateInfo& createInfo)
    {
        internal = std::move(vk::raii::DescriptorPool{ device.getInternal(), createInfo });
    }
}