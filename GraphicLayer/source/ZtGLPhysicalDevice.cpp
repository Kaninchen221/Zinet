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

    uint32_t PhysicalDevice::pickQueueFamilyIndex(const Surface& surface) const
    {
        std::vector<vk::QueueFamilyProperties> queueFamiliesProperties = internal.getQueueFamilyProperties();

        uint32_t index = 0u;
        for (const vk::QueueFamilyProperties& queueFamilyProperties : queueFamiliesProperties)
        {
            const vk::QueueFlags& queueFlags = queueFamilyProperties.queueFlags;
            bool neededFlags = static_cast<bool>(queueFlags & vk::QueueFlagBits::eGraphics);

            VkBool32 surfaceSupport{};
            vkGetPhysicalDeviceSurfaceSupportKHR(*internal, index, surface.getInternal(), &surfaceSupport);

            if (neededFlags && surfaceSupport)
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

    vk::raii::PhysicalDevices PhysicalDevice::enumeratePhysicalDevices(const Instance& instance) const
    {
        return vk::raii::PhysicalDevices(instance.getInternal());
    }

    const std::vector<const char*>& PhysicalDevice::GetPhysicalDeviceExtensions()
    {
        return PhysicalDeviceExtensions;
    }

    bool PhysicalDevice::isDeviceHasNeededExtensions(const vk::raii::PhysicalDevice& physicalDevice) const
    {
        std::vector<vk::ExtensionProperties> availableExtensionProperties = physicalDevice.enumerateDeviceExtensionProperties();
        for (const char* neededExtension : PhysicalDeviceExtensions)
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

    SwapChainSupportDetails PhysicalDevice::getSwapChainSupportDetails(const Surface& surface)
    {
        SwapChainSupportDetails swapChainSupportDetails;
        swapChainSupportDetails.capabilities = internal.getSurfaceCapabilitiesKHR(surface.getInternal());
        swapChainSupportDetails.formats = internal.getSurfaceFormatsKHR(surface.getInternal());
        swapChainSupportDetails.presentModes = internal.getSurfacePresentModesKHR(surface.getInternal());

        return swapChainSupportDetails;
    }

    bool PhysicalDevice::create(const Instance& instance)
    {
        vk::raii::PhysicalDevices physicalDevices = enumeratePhysicalDevices(instance);
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

}