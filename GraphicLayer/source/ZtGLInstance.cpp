#include "Zinet/GraphicLayer/ZtGLInstance.h"

namespace zt::gl
{
    Instance::Instance()
        : internal(std::nullptr_t())
    {

    }

    void Instance::createApplicationInfo()
    {
        applicationInfo.sType = vk::StructureType::eApplicationInfo;
        applicationInfo.pApplicationName = "Zinet";
        applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        applicationInfo.pEngineName = "Zinet Renderer";
        applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        applicationInfo.apiVersion = VK_API_VERSION_1_0;
    }

    const vk::ApplicationInfo& Instance::getApplicationInfo() const
    {
        return applicationInfo;
    }

    void Instance::createInstanceCreateInfo()
    {
        instanceCreateInfo.sType = vk::StructureType::eInstanceCreateInfo;
        instanceCreateInfo.pApplicationInfo = &applicationInfo;

        extensions = getRequiredExtensions();
        instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        instanceCreateInfo.ppEnabledExtensionNames = extensions.data();

        if (GetEnabledValidationLayers())
        {
            instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers.size());
            instanceCreateInfo.ppEnabledLayerNames = ValidationLayers.data();
        }
        else
        {
            instanceCreateInfo.enabledLayerCount = 0;
            instanceCreateInfo.pNext = nullptr;
        }
    }

    const vk::InstanceCreateInfo& Instance::getInstanceCreateInfo() const
    {
        return instanceCreateInfo;
    }

    void Instance::createInstance(const Context& context)
    {
        if (GetEnabledValidationLayers() && !CheckValidationLayerSupport())
        {
            Logger->error("Validation layers requested, but not available!");
            return;
        }

        internal = vk::raii::Instance(context.getInternal(), instanceCreateInfo);
    }

    const vk::raii::Instance& Instance::getInternal() const
    {
        return internal;
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

    std::vector<const char*> Instance::getRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (GetEnabledValidationLayers()) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    bool Instance::GetEnabledValidationLayers()
    {
        #ifdef ZINET_DEBUG
            return true;
        #else
            return false;
        #endif
    }

    vk::raii::PhysicalDevices Instance::enumeratePhysicalDevices() const
    {
        return vk::raii::PhysicalDevices(internal);
    }

    PhysicalDevice Instance::pickPhysicalDevice() const
    {
        vk::raii::PhysicalDevices physicalDevices = enumeratePhysicalDevices();
        if (physicalDevices.size() == 0u)
        {
            Logger->error("Can't find physical device supporting vulkan");
            return vk::raii::PhysicalDevice(std::nullptr_t());
        }

        PhysicalDevice physicalDevice(std::move(physicalDevices.front()));

        return physicalDevice;
    }
}