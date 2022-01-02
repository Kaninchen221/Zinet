#include "Zinet/GraphicLayer/ZtGLContext.h"

namespace zt::gl
{

    Context::~Context() noexcept
    {
        destroyDebugUtilsMessengerCreateInfo();
        instance.destroy();
        deinitGLFW();
    }

    bool Context::initGLFW()
    {
        if (glfwInit())
        {
            Logger->info("Succesfull initialize GLFW");

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Don't create OpenGL context
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

            return true;
        }
        else
        {
            Logger->error("Failed initialize glfw");
            return false;
        }

        return false;
    }

    void Context::deinitGLFW()
    {
        glfwTerminate();
    }

    void Context::createApplicationInfo()
    {
        applicationInfo.sType = vk::StructureType::eApplicationInfo;
        applicationInfo.pApplicationName = "Zinet";
        applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);;
        applicationInfo.pEngineName = "Zinet Renderer";
        applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);;
        applicationInfo.apiVersion = VK_API_VERSION_1_0;
    }

    const vk::ApplicationInfo& Context::getApplicationInfo() const
    {
        return applicationInfo;
    }

    void Context::createInstanceCreateInfo()
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
            instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugUtilsMessengerCreateInfo;
        }
        else 
        {
            instanceCreateInfo.enabledLayerCount = 0;
            instanceCreateInfo.pNext = nullptr;
        }
    }

    const vk::InstanceCreateInfo& Context::getInstanceCreateInfo() const
    {
        return instanceCreateInfo;
    }

    void Context::createInstance()
    {
        if (enableValidationLayers && !checkValidationLayerSupport())
        {
            Logger->error("Validation layers requested, but not available!");
            return;
        }

        instance = vk::createInstance(instanceCreateInfo);
    }

    const vk::Instance& Context::getInstance() const
    {
        return instance;
    }

    void Context::createPhysicalDevices()
    {
        physicalDevices = instance.enumeratePhysicalDevices();
    }

    const std::vector<vk::PhysicalDevice>& Context::getPhysicalDevices() const
    {
        return physicalDevices;
    }

    const std::vector<const char*>& Context::getValidationLayers() const
    {
        return validationLayers;
    }

    bool Context::checkValidationLayerSupport() const
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

    std::vector<const char*> Context::getRequiredExtensions()
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

    VkBool32 Context::DebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
        VkDebugUtilsMessageTypeFlagsEXT messageType, 
        const VkDebugUtilsMessengerCallbackDataEXT* callbackData, 
        void* userData)
    {
        std::string messageTypeAsString;
        if (messageType == VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
        {
            messageTypeAsString = "General";
        }
        else if (messageType == VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
        {
            messageTypeAsString = "Validation";
        }
        else if (messageType == VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
        {
            messageTypeAsString = "Performance";
        }
        else
        {
            return false;
        }

        std::string messagePattern =
            "Type: {} IdName: {} IdNumber: {} Message: {}";

        if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
        {
            Logger->debug(messagePattern, 
                messageTypeAsString, 
                callbackData->pMessageIdName, 
                callbackData->messageIdNumber,
                callbackData->pMessage);
        }
        else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
        {
            Logger->info(messagePattern,
                messageTypeAsString,
                callbackData->pMessageIdName,
                callbackData->messageIdNumber,
                callbackData->pMessage);
        }
        else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
        {
            Logger->warn(messagePattern,
                messageTypeAsString,
                callbackData->pMessageIdName,
                callbackData->messageIdNumber,
                callbackData->pMessage);
        }
        else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
        {
            Logger->error(messagePattern,
                messageTypeAsString,
                callbackData->pMessageIdName,
                callbackData->messageIdNumber,
                callbackData->pMessage);
        }
        else
        {
            Logger->error("Not expected message severity");
            return false;
        }

        return true;
    }

    const VkDebugUtilsMessengerEXT& Context::getDebugMessenger() const
    {
        return debugMessenger;
    }

    void Context::createDebugUtilsMessengerCreateInfo()
    {
        debugUtilsMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

        debugUtilsMessengerCreateInfo.messageSeverity = 
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | 
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | 
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

        debugUtilsMessengerCreateInfo.messageType = 
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | 
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | 
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

        debugUtilsMessengerCreateInfo.pfnUserCallback = DebugCallback;
        debugUtilsMessengerCreateInfo.pUserData = nullptr;
    }

    const VkDebugUtilsMessengerCreateInfoEXT& Context::getDebugUtilsMessengerCreateInfo() const
    {
        return debugUtilsMessengerCreateInfo;
    }

    VkResult Context::createDebugUtilsMessenger()
    {
        auto function = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (function != nullptr) 
        {
            const VkAllocationCallbacks* allocator = nullptr;
            return function(instance, &debugUtilsMessengerCreateInfo, nullptr, &debugMessenger);
        }
        else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void Context::destroyDebugUtilsMessengerCreateInfo()
    {
        auto function = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (function != nullptr) 
        {
            const VkAllocationCallbacks* allocator = nullptr;
            function(instance, debugMessenger, allocator);
        }
    }

    VkResult Context::initVulkan()
    {
        initGLFW();
        createApplicationInfo();
        createInstanceCreateInfo();
        createDebugUtilsMessengerCreateInfo();
        createInstance();
        createDebugUtilsMessengerCreateInfo();
        VkResult result = createDebugUtilsMessenger();

        if (result != VkResult::VK_SUCCESS)
            return result;



        return VkResult::VK_SUCCESS;
    }
}