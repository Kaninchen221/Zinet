#include "Zinet/GraphicLayer/ZtGLRenderer.h"

namespace zt::gl
{
    Renderer::Renderer()
    {
        GLFW::InitGLFW();
        instanceHelper.createApplicationInfo();
        instanceHelper.createInstanceCreateInfo();
        instanceHelper.createInstance(context);
    }

    Renderer::~Renderer() noexcept
    {
        GLFW::DeinitGLFW();
    }

    vk::DeviceQueueCreateInfo Renderer::createDeviceQueueCreateInfo(const vk::raii::PhysicalDevice& physicalDevice)
    {
        deviceQueueCreateInfo.sType = vk::StructureType::eDeviceQueueCreateInfo;
        deviceQueueCreateInfo.queueFamilyIndex = physicalDeviceHelper.pickQueueFamilyIndex(physicalDevice);
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
        deviceCreateInfo.pEnabledFeatures = &physicalDeviceHelper.physicalDeviceFeatures;

        deviceCreateInfo.enabledExtensionCount = 0;
        if (instanceHelper.enableValidationLayers)
        {
            deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(instanceHelper.validationLayers.size());
            deviceCreateInfo.ppEnabledLayerNames = instanceHelper.validationLayers.data();
        }
        else 
        {
            deviceCreateInfo.enabledLayerCount = 0;
        }

        return deviceCreateInfo;
    }

    vk::raii::Device Renderer::createDevice(const vk::raii::PhysicalDevice& physicalDevice)
    {
        vk::DeviceCreateInfo deviceCreateInfo = createDeviceCreateInfo();
        vk::raii::Device device(physicalDevice, deviceCreateInfo);
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