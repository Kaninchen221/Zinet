#include "Zinet/GraphicLayer/ZtGLDebugUtilsMessenger.h"

namespace zt::gl
{
    DebugUtilsMessenger::DebugUtilsMessenger()
        : debugMessenger(std::nullptr_t())
    {

    }

    VkBool32 DebugUtilsMessenger::DebugCallback(
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

    const vk::raii::DebugUtilsMessengerEXT& DebugUtilsMessenger::getDebugMessenger() const
    {
        return debugMessenger;
    }

    void DebugUtilsMessenger::createDebugUtilsMessenger(vk::raii::Instance& instance)
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

}