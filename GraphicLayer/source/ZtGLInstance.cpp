#include "Zinet/GraphicLayer/ZtGLInstance.h"

namespace zt::gl
{
    Instance::Instance()
        : instance(std::nullptr_t())
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

        if (enableValidationLayers)
        {
            instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
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

    void Instance::createInstance(const vk::raii::Context& context)
    {
        if (enableValidationLayers && !checkValidationLayerSupport())
        {
            Logger->error("Validation layers requested, but not available!");
            return;
        }

        instance = vk::raii::Instance(context, instanceCreateInfo);
    }

    const vk::raii::Instance& Instance::getInstance() const
    {
        return instance;
    }

    const std::vector<const char*>& Instance::getValidationLayers() const
    {
        return validationLayers;
    }

    bool Instance::checkValidationLayerSupport() const
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* validationLayer : validationLayers)
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

        if (enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    vk::raii::PhysicalDevices Instance::enumeratePhysicalDevices() const
    {
        return vk::raii::PhysicalDevices(instance);
    }

    vk::raii::PhysicalDevice Instance::pickPhysicalDevice() const
    {
        vk::raii::PhysicalDevices physicalDevices = enumeratePhysicalDevices();
        if (physicalDevices.size() == 0u)
        {
            Logger->error("Can't find physical device supporting vulkan");
            return vk::raii::PhysicalDevice(std::nullptr_t());
        }

        return std::move(physicalDevices.front());
    }
}