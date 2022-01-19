#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{
    Device::Device()
        : internal(std::nullptr_t())
    {
    }

    vk::DeviceQueueCreateInfo Device::createDeviceQueueCreateInfo(const PhysicalDevice& physicalDevice)
    {
        deviceQueueCreateInfo.sType = vk::StructureType::eDeviceQueueCreateInfo;
        deviceQueueCreateInfo.queueFamilyIndex = physicalDevice.pickQueueFamilyIndex();
        deviceQueueCreateInfo.queueCount = 1;
        deviceQueueCreateInfo.pQueuePriorities = &queuePriority;

        return deviceQueueCreateInfo;
    }

    vk::DeviceCreateInfo Device::createDeviceCreateInfo(const PhysicalDevice& physicalDevice) const
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

    void Device::createDevice(const PhysicalDevice& physicalDevice)
    {
        vk::DeviceCreateInfo deviceCreateInfo = createDeviceCreateInfo(physicalDevice);
        internal = vk::raii::Device(physicalDevice.getInternal(), deviceCreateInfo);
    }

    const vk::raii::Device& Device::getInternal() const
    {
        return internal;
    }

    vk::raii::Queue Device::createQueue(uint32_t queueFamilyIndex) const
    {
        // We creating only one queue
        uint32_t queueIndex = 0u;
        vk::raii::Queue queue(internal, queueFamilyIndex, queueIndex);
        return queue;
    }
}