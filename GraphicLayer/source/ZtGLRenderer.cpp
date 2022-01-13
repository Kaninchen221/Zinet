#include "Zinet/GraphicLayer/ZtGLRenderer.h"

namespace zt::gl
{
    Renderer::Renderer()
    {
        GLFW::InitGLFW();
        instanceHelper.createApplicationInfo();
        instanceHelper.createInstanceCreateInfo();
        instanceHelper.createInstance(context);

        physicalDevice = instanceHelper.pickPhysicalDevice();
    }

    Renderer::~Renderer() noexcept
    {
        GLFW::DeinitGLFW();
    }

    vk::DeviceQueueCreateInfo Renderer::createDeviceQueueCreateInfo()
    {
        deviceQueueCreateInfo.sType = vk::StructureType::eDeviceQueueCreateInfo;
        deviceQueueCreateInfo.queueFamilyIndex = physicalDevice.pickQueueFamilyIndex();
        deviceQueueCreateInfo.queueCount = 1; 
        deviceQueueCreateInfo.pQueuePriorities = &queuePriority;

        return deviceQueueCreateInfo;
    }

    vk::DeviceCreateInfo Renderer::createDeviceCreateInfo() const
    {
        vk::DeviceCreateInfo deviceCreateInfo;
        deviceCreateInfo.sType = vk::StructureType::eDeviceCreateInfo;
        deviceCreateInfo.queueCreateInfoCount = 1;
        deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
        deviceCreateInfo.pEnabledFeatures = &physicalDevice.getFeatures();

        deviceCreateInfo.enabledExtensionCount = 0;
        if (Instance::GetEnabledValidationLayers())
        {
            deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(Instance::ValidationLayers.size());
            deviceCreateInfo.ppEnabledLayerNames = Instance::ValidationLayers.data();
        }
        else 
        {
            deviceCreateInfo.enabledLayerCount = 0;
        }

        return deviceCreateInfo;
    }

    vk::raii::Device Renderer::createDevice()
    {
        vk::DeviceCreateInfo deviceCreateInfo = createDeviceCreateInfo();
        vk::raii::Device device(physicalDevice.getInternal(), deviceCreateInfo);
        return device;
    }

    vk::raii::Queue Renderer::createQueue(const vk::raii::Device& device, uint32_t queueFamilyIndex) const
    {
        // We creating only one queue
        uint32_t queueIndex = 0u;
        vk::raii::Queue queue(device, queueFamilyIndex, queueIndex);
        return queue;
    }

}