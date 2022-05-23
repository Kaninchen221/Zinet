#include "Zinet/GraphicLayer/ZtGLDescriptorPool.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{
    const vk::DescriptorPoolSize& DescriptorPool::createPoolSize()
    {
        poolSize.descriptorCount = 1;

        return poolSize;
    }

    const vk::DescriptorPoolSize& DescriptorPool::getPoolSize() const
    {
        return poolSize;
    }

    vk::DescriptorPoolCreateInfo DescriptorPool::createCreateInfo() const
    {
        vk::DescriptorPoolCreateInfo createInfo;
        createInfo.poolSizeCount = 1u;
        createInfo.pPoolSizes = &poolSize;
        createInfo.maxSets = 1u;
        createInfo.flags = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet;

        return createInfo;
    }

    void DescriptorPool::create(Device& device, const vk::DescriptorPoolCreateInfo& createInfo)
    {
        internal = std::move(vk::raii::DescriptorPool{ device.getInternal(), createInfo });
    }
}