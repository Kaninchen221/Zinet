#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"

namespace zt::gl
{
    uint32_t PhysicalDevice::pickQueueFamilyIndex(const vk::raii::PhysicalDevice& physicalDevice) const
    {
        std::vector<vk::QueueFamilyProperties> queueFamiliesProperties = physicalDevice.getQueueFamilyProperties();

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

    vk::PhysicalDeviceFeatures PhysicalDevice::createPhysicalDeviceFeatures() const
    {
        return physicalDeviceFeatures;
    }
}