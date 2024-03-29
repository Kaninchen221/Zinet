#include "Zinet/GraphicLayer/ZtGLDescriptorSetLayout.hpp"
#include "Zinet/GraphicLayer/ZtGLDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLDescriptorPool.hpp"

namespace zt::gl
{
    vk::DescriptorSetLayoutBinding DescriptorSetLayout::createUniformLayoutBinding()
    {
        vk::DescriptorSetLayoutBinding uniformLayoutBinding;
        uniformLayoutBinding.binding = 0;
        uniformLayoutBinding.descriptorType = vk::DescriptorType::eUniformBuffer;
        uniformLayoutBinding.descriptorCount = 1;
        uniformLayoutBinding.stageFlags = vk::ShaderStageFlagBits::eVertex;
        uniformLayoutBinding.pImmutableSamplers = nullptr;

        return uniformLayoutBinding;
    }

    vk::DescriptorSetLayoutBinding DescriptorSetLayout::createImageSamplerLayoutBinding()
    {
        vk::DescriptorSetLayoutBinding imageSamplerLayoutBinding;
        imageSamplerLayoutBinding.binding = 1;
        imageSamplerLayoutBinding.descriptorType = vk::DescriptorType::eCombinedImageSampler;
        imageSamplerLayoutBinding.descriptorCount = 1;
        imageSamplerLayoutBinding.stageFlags = vk::ShaderStageFlagBits::eFragment;
        imageSamplerLayoutBinding.pImmutableSamplers = nullptr;

        return imageSamplerLayoutBinding;
    }

    vk::DescriptorSetLayoutCreateInfo DescriptorSetLayout::createDescriptorSetLayoutCreateInfo(const std::vector<vk::DescriptorSetLayoutBinding>& bindings)
    {
        vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo;
        descriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32_t>(bindings.size());
        descriptorSetLayoutCreateInfo.pBindings = bindings.data();

        return descriptorSetLayoutCreateInfo;
    }

    void DescriptorSetLayout::create(Device& device, const vk::DescriptorSetLayoutCreateInfo& createInfo)
    {
        vk::raii::DescriptorSetLayout temp{ device.getInternal(), createInfo };
        internal.swap(temp);
        temp.release();
    }
}