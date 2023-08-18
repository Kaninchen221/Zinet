#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"

namespace zt::gl
{

    uint32_t PhysicalDevice::pickQueueFamilyIndex(const Surface& surface) const
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

    bool PhysicalDevice::create(Instance& instance)
    {
        vk::raii::PhysicalDevices physicalDevices = instance.enumeratePhysicalDevices();
        if (physicalDevices.size() == 0u)
        {
            Logger->error("Can't find physical device supporting vulkan");
            return false;
        }

        std::vector<std::int16_t> ratings;
		ratings.reserve(physicalDevices.size());

		size_t preferredDeviceIndex = 0;
		std::int16_t highestRating = std::numeric_limits<std::int16_t>::min();

        for (size_t index = 0u; vk::raii::PhysicalDevice& physicalDevice : physicalDevices)
        {
			ratings.push_back(ratePhysicalDevice(physicalDevice));

			if (highestRating < ratings[index])
			{
				highestRating = ratings[index];
				preferredDeviceIndex = index;
			}

			++index;
        }

		internal.swap(physicalDevices[preferredDeviceIndex]);
		physicalDevices[preferredDeviceIndex].release();

        return highestRating >= 0;
	}

    std::int16_t PhysicalDevice::ratePhysicalDevice(const vk::raii::PhysicalDevice& physicalDevice)
	{
		std::int16_t rating = 0;

		if (!hasRequiredExtensions(physicalDevice))
			rating -= 100;
		else
			rating += 100;

		vk::PhysicalDeviceProperties deviceProperties = physicalDevice.getProperties();
		if (deviceProperties.deviceType == vk::PhysicalDeviceType::eIntegratedGpu)
			rating -= 1;
		else
			rating += 1;

		return rating;
	}

	bool PhysicalDevice::hasRequiredExtensions(const vk::raii::PhysicalDevice& physicalDevice) const
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

    SwapChainSupportDetails PhysicalDevice::getSwapChainSupportDetails(const Surface& surface) const
    {
        SwapChainSupportDetails swapChainSupportDetails;
        swapChainSupportDetails.surfaceCapabilities = internal.getSurfaceCapabilitiesKHR(*surface.getInternal());
        swapChainSupportDetails.surfaceFormats = internal.getSurfaceFormatsKHR(*surface.getInternal());
        swapChainSupportDetails.presentModes = internal.getSurfacePresentModesKHR(*surface.getInternal());
        
        return swapChainSupportDetails;
	}

	bool PhysicalDevice::findSupportedFormat(const FindSupportedFormatInput& input, vk::Format& supportedFormat) const
	{
		for (vk::Format candidateFormat : input.candidates)
		{
			vk::FormatProperties formatProperties = internal.getFormatProperties(candidateFormat);

			switch (input.imageTiling)
			{
			case vk::ImageTiling::eLinear:
				if ((formatProperties.linearTilingFeatures & input.formatFeatureFlags) == input.formatFeatureFlags)
				{
					supportedFormat = candidateFormat;
					return true;
				}
				break;
			case vk::ImageTiling::eOptimal:
				if ((formatProperties.optimalTilingFeatures & input.formatFeatureFlags) == input.formatFeatureFlags)
				{
					supportedFormat = candidateFormat;
					return true;
				}
				break;
			}
		}

		supportedFormat = vk::Format{};
		return false;
	}

	bool PhysicalDevice::isFormatSupportingGeneratingMipmaps(vk::Format format) const
	{
		vk::FormatProperties formatProperties = internal.getFormatProperties(format);

		bool isSupporting = 
			(formatProperties.optimalTilingFeatures & vk::FormatFeatureFlagBits::eSampledImageFilterLinear).operator bool();

		return isSupporting;
	}

}