#include "Zinet/GraphicLayer/ZtGLInstance.hpp"

namespace zt::gl
{
    vk::ApplicationInfo Instance::createApplicationInfo() const
    {
        vk::ApplicationInfo applicationInfo{};
        applicationInfo.pNext = nullptr;
        applicationInfo.pApplicationName = "Zinet";
        applicationInfo.applicationVersion = 0u;
        applicationInfo.pEngineName = "Zinet Renderer";
        applicationInfo.engineVersion = 0u;
        applicationInfo.apiVersion = VK_API_VERSION_1_0;

        return applicationInfo;
    }

    vk::InstanceCreateInfo Instance::createInstanceCreateInfo(const vk::ApplicationInfo& applicationInfo) const
    {
        vk::InstanceCreateInfo instanceCreateInfo{};
        instanceCreateInfo.pApplicationInfo = &applicationInfo;

        instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        instanceCreateInfo.ppEnabledExtensionNames = extensions.data();

        if (getEnableValidationLayers())
        {
            instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers.size());
            instanceCreateInfo.ppEnabledLayerNames = ValidationLayers.data();
        }
        else
        {
            instanceCreateInfo.enabledLayerCount = 0;
            instanceCreateInfo.pNext = nullptr;
        }

        return instanceCreateInfo;
    }

    void Instance::create(Context& context, vk::InstanceCreateInfo createInfo)
    {
        if (getEnableValidationLayers() && !CheckValidationLayerSupport())
        {
            Logger->error("Validation layers requested, but not available!");
            return;
        }

        vk::raii::Instance tempInstance{context.getInternal(), createInfo};
        internal.swap(tempInstance);
        tempInstance.release();
    }

    vk::raii::PhysicalDevices Instance::enumeratePhysicalDevices() const
    {
        return vk::raii::PhysicalDevices(internal);
    }

    const std::vector<const char*>& Instance::GetValidationLayers()
    {
        return ValidationLayers;
    }

    bool Instance::CheckValidationLayerSupport()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* validationLayer : ValidationLayers)
        {
            bool layerFound = false;

            for (const VkLayerProperties& availableLayer : availableLayers)
            {
                if (validationLayer != availableLayer.layerName)
                {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }

    std::vector<const char*>& Instance::getRequiredExtensions()
    {
        return extensions;
    }

    void Instance::populateRequiredExtensions()
    {
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		extensions = std::vector<const char*>(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (getEnableValidationLayers()) {
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}
    }

}