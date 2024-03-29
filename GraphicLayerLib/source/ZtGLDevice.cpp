#include "Zinet/GraphicLayer/ZtGLDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLInstance.hpp"
#include "Zinet/GraphicLayer/ZtGLQueue.hpp"
#include "Zinet/GraphicLayer/ZtGLFence.hpp"

namespace zt::gl
{
    vk::DeviceQueueCreateInfo Device::createDeviceQueueCreateInfo(PhysicalDevice& physicalDevice, Surface& surface)
    {
        vk::DeviceQueueCreateInfo deviceQueueCreateInfo;
        deviceQueueCreateInfo.sType = vk::StructureType::eDeviceQueueCreateInfo;
        deviceQueueCreateInfo.queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
        deviceQueueCreateInfo.queueCount = 1;
        deviceQueueCreateInfo.pQueuePriorities = &queuePriority;

        return deviceQueueCreateInfo;
    }

    vk::DeviceCreateInfo Device::createDeviceCreateInfo(const Instance& instance, PhysicalDevice& physicalDevice, Surface& surface, vk::DeviceQueueCreateInfo& deviceQueueCreateInfo)
    {
        createDeviceQueueCreateInfo(physicalDevice, surface);

        vk::DeviceCreateInfo deviceCreateInfo;
        deviceCreateInfo.sType = vk::StructureType::eDeviceCreateInfo;
        deviceCreateInfo.queueCreateInfoCount = 1;
        deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
        deviceCreateInfo.pEnabledFeatures = &physicalDevice.getFeatures();
        deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(physicalDevice.getPhysicalDeviceExtensions().size());
        deviceCreateInfo.ppEnabledExtensionNames = physicalDevice.getPhysicalDeviceExtensions().data();

        if (instance.getEnableValidationLayers())
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

    void Device::create(PhysicalDevice& physicalDevice, vk::DeviceCreateInfo& deviceCreateInfo)
    {
        vk::raii::Device tempDevice(physicalDevice.getInternal(), deviceCreateInfo);
        internal.swap(tempDevice);
        tempDevice.release();
    }

    vk::Result Device::waitForFence(Fence& fence, uint64_t timeout) const
    {
        vk::Result result;
        result = internal.waitForFences({ *fence.getInternal() }, VK_TRUE, timeout);

        return result;
    }

    void Device::resetFence(Fence& fence) const
    {
        internal.resetFences({ *fence.getInternal() });
    }

}