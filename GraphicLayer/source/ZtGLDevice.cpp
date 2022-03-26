#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLQueue.h"
#include "Zinet/GraphicLayer/ZtGLFence.h"

namespace zt::gl
{
    Device::Device()
        : internal(std::nullptr_t())
    {
    }

    vk::DeviceQueueCreateInfo Device::createDeviceQueueCreateInfo(const PhysicalDevice& physicalDevice, const Surface& surface)
    {
        deviceQueueCreateInfo.sType = vk::StructureType::eDeviceQueueCreateInfo;
        deviceQueueCreateInfo.queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
        deviceQueueCreateInfo.queueCount = 1;
        deviceQueueCreateInfo.pQueuePriorities = &queuePriority;

        return deviceQueueCreateInfo;
    }

    vk::DeviceCreateInfo Device::createDeviceCreateInfo(const PhysicalDevice& physicalDevice, const Surface& surface)
    {
        createDeviceQueueCreateInfo(physicalDevice, surface);

        vk::DeviceCreateInfo deviceCreateInfo;
        deviceCreateInfo.sType = vk::StructureType::eDeviceCreateInfo;
        deviceCreateInfo.queueCreateInfoCount = 1;
        deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
        deviceCreateInfo.pEnabledFeatures = &physicalDevice.getFeatures();
        deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(PhysicalDevice::GetPhysicalDeviceExtensions().size());
        deviceCreateInfo.ppEnabledExtensionNames = PhysicalDevice::GetPhysicalDeviceExtensions().data();

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

    void Device::create(const PhysicalDevice& physicalDevice, const Surface& surface)
    {
        vk::DeviceCreateInfo deviceCreateInfo = createDeviceCreateInfo(physicalDevice, surface);
        internal = vk::raii::Device(physicalDevice.getInternal(), deviceCreateInfo);
    }

    vk::raii::Device& Device::getInternal()
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

    vk::Result Device::waitForFence(Fence& fence, uint64_t timeout) const
    {
        vk::Result result;
        result = internal.waitForFences({ *fence.getInternal() }, VK_TRUE, timeout);

        return result;
    }
}