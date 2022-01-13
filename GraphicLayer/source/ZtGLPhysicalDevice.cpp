#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"

namespace zt::gl
{

    PhysicalDevice::PhysicalDevice()
        : internal(std::nullptr_t())
    {

    }

    PhysicalDevice::PhysicalDevice(vk::raii::PhysicalDevice&& physicalDevice)
        : internal(std::move(physicalDevice))
    {

    }

    uint32_t PhysicalDevice::pickQueueFamilyIndex() const
    {
        std::vector<vk::QueueFamilyProperties> queueFamiliesProperties = internal.getQueueFamilyProperties();

        uint32_t index = 0u;
        for (const vk::QueueFamilyProperties& queueFamilyProperties : queueFamiliesProperties)
        {
            const vk::QueueFlags& queueFlags = queueFamilyProperties.queueFlags;
            if (queueFlags & vk::QueueFlagBits::eGraphics)
            {
                return index;
            }

            index++;
        }

        return std::numeric_limits<uint32_t>::max();
    }

    vk::PhysicalDeviceFeatures PhysicalDevice::createFeatures() const
    {
        return features;
    }

    const vk::PhysicalDeviceFeatures& PhysicalDevice::getFeatures() const
    {
        return features;
    }

    const vk::raii::PhysicalDevice& PhysicalDevice::getInternal() const
    {
        return internal;
    }
}