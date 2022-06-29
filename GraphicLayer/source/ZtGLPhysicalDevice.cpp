#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"

namespace zt::gl
{

    uint32_t PhysicalDevice::pickQueueFamilyIndex(Surface& surface)
    {
        std::vector<vk::QueueFamilyProperties> queueFamiliesProperties = internal.getQueueFamilyProperties();

        uint32_t index = 0u;
        for (const vk::QueueFamilyProperties& queueFamilyProperties : queueFamiliesProperties)
        {
            const vk::QueueFlags& queueFlags = queueFamilyProperties.queueFlags;
            bool neededFlags = static_cast<bool>(queueFlags & vk::QueueFlagBits::eGraphics);

            vk::Bool32 surfaceSupport = internal.getSurfaceSupportKHR(index, *surface.getInternal());

            if (neededFlags && surfaceSupport)
            {
                return index;
            }

            index++;
        }

        return std::numeric_limits<uint32_t>::max();
    }

    const vk::PhysicalDeviceFeatures& PhysicalDevice::getFeatures() const
    {
        return features;
    }

    const std::vector<const char*>& PhysicalDevice::getPhysicalDeviceExtensions() const
    {
        return physicalDeviceExtensions;
    }

    bool PhysicalDevice::isDeviceHasNeededExtensions(const vk::raii::PhysicalDevice& physicalDevice) const
    {
        std::vector<vk::ExtensionProperties> availableExtensionProperties = physicalDevice.enumerateDeviceExtensionProperties();
        for (const char* neededExtension : physicalDeviceExtensions)
        {
            auto predicate = [neededExtension](const vk::ExtensionProperties& extension) -> bool
            {
                std::string_view extensionAsStringView(extension.extensionName.data());
                return extensionAsStringView == neededExtension;
            };

            std::vector<vk::ExtensionProperties>::iterator result = std::find_if(
                availableExtensionProperties.begin(),
                availableExtensionProperties.end(),
                predicate);

            if (result == availableExtensionProperties.end())
            {
                return false;
            }
        }

        return true;
    }

    bool PhysicalDevice::create(Instance& instance)
    {
        vk::raii::PhysicalDevices physicalDevices = instance.enumeratePhysicalDevices();
        if (physicalDevices.size() == 0u)
        {
            Logger->error("Can't find physical device supporting vulkan");
            return false;
        }

        for (vk::raii::PhysicalDevice& physicalDevice : physicalDevices)
        {
            if (isDeviceHasNeededExtensions(physicalDevice))
            {
                internal = vk::raii::PhysicalDevice(std::move(physicalDevice));
                return true;
            }
        }

        return false;
    }

    SwapChainSupportDetails PhysicalDevice::getSwapChainSupportDetails(const Surface& surface) const
    {
        SwapChainSupportDetails swapChainSupportDetails;
        swapChainSupportDetails.surfaceCapabilities = internal.getSurfaceCapabilitiesKHR(*surface.getInternal());
        swapChainSupportDetails.surfaceFormats = internal.getSurfaceFormatsKHR(*surface.getInternal());
        swapChainSupportDetails.presentModes = internal.getSurfacePresentModesKHR(*surface.getInternal());
        
        return swapChainSupportDetails;
    }
}