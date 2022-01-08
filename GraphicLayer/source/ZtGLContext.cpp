#include "Zinet/GraphicLayer/ZtGLContext.h"

namespace zt::gl
{
    Context::Context()
        : instance(std::nullptr_t()),
        debugMessenger(std::nullptr_t())
    {

    }

    Context::~Context() noexcept
    {
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

        instance = vk::raii::Instance(context, instanceCreateInfo);
    }

    const vk::raii::Instance& Context::getInstance() const
    {
        return instance;
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

    const vk::raii::DebugUtilsMessengerEXT& Context::getDebugMessenger() const
    {
        return debugMessenger;
    }

    void Context::createDebugUtilsMessenger()
    {
        vk::DebugUtilsMessageSeverityFlagsEXT severityFlags(
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo |
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eError);

        vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags(
            vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
            vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
            vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation);

        vk::DebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfo({}, severityFlags, messageTypeFlags, &DebugCallback);
        
        debugMessenger = vk::raii::DebugUtilsMessengerEXT(instance, debugUtilsMessengerCreateInfo);
    }

    vk::raii::PhysicalDevices Context::enumeratePhysicalDevices() const
    {
        return vk::raii::PhysicalDevices(instance);
    }

    vk::raii::PhysicalDevice Context::pickPhysicalDevice() const
    {
        vk::raii::PhysicalDevices physicalDevices = enumeratePhysicalDevices();
        if (physicalDevices.size() == 0u)
        {
            Logger->error("Can't find physical device supporting vulkan");
            return vk::raii::PhysicalDevice(std::nullptr_t());
        }

        return std::move(physicalDevices.front());
    }

    uint32_t Context::pickQueueFamilyIndex(const vk::raii::PhysicalDevice& physicalDevice) const
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

    vk::DeviceQueueCreateInfo Context::createDeviceQueueCreateInfo(const vk::raii::PhysicalDevice& physicalDevice)
    {
        deviceQueueCreateInfo.sType = vk::StructureType::eDeviceQueueCreateInfo;
        deviceQueueCreateInfo.queueFamilyIndex = pickQueueFamilyIndex(physicalDevice);
        deviceQueueCreateInfo.queueCount = 1; 
        deviceQueueCreateInfo.pQueuePriorities = &queuePriority; // Reference to local variable

        return deviceQueueCreateInfo;
    }

    vk::PhysicalDeviceFeatures Context::createPhysicalDeviceFeatures() const
    {
        return physicalDeviceFeatures;
    }

    vk::DeviceCreateInfo Context::createDeviceCreateInfo() const
    {
        vk::DeviceCreateInfo deviceCreateInfo;
        deviceCreateInfo.sType = vk::StructureType::eDeviceCreateInfo;
        deviceCreateInfo.queueCreateInfoCount = 1;
        deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
        deviceCreateInfo.pEnabledFeatures = &physicalDeviceFeatures;

        deviceCreateInfo.enabledExtensionCount = 0;
        if (enableValidationLayers) 
        {
            deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            deviceCreateInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else 
        {
            deviceCreateInfo.enabledLayerCount = 0;
        }

        return deviceCreateInfo;
    }

    vk::raii::Device Context::createDevice(const vk::raii::PhysicalDevice& physicalDevice)
    {
        vk::DeviceCreateInfo deviceCreateInfo = createDeviceCreateInfo();
        vk::raii::Device device(physicalDevice, deviceCreateInfo);
        return std::move(device);
    }

    vk::raii::Queue Context::createQueue(const vk::raii::Device& device, uint32_t queueFamilyIndex) const
    {
        // We creating only one queue
        uint32_t queueIndex = 0u;
        vk::raii::Queue queue(device, queueFamilyIndex, queueIndex);
        return std::move(queue);
    }

}