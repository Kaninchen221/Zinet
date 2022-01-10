#include "Zinet/GraphicLayer/ZtGLContext.h"

namespace zt::gl
{
    Context::Context()
    {
        GLFW::InitGLFW();
        instanceHelper.createApplicationInfo();
        instanceHelper.createInstanceCreateInfo();
        instanceHelper.createInstance(context);
    }

    Context::~Context() noexcept
    {
        GLFW::DeinitGLFW();
    }

    vk::DeviceQueueCreateInfo Context::createDeviceQueueCreateInfo(const vk::raii::PhysicalDevice& physicalDevice)
    {
        deviceQueueCreateInfo.sType = vk::StructureType::eDeviceQueueCreateInfo;
        deviceQueueCreateInfo.queueFamilyIndex = physicalDeviceHelper.pickQueueFamilyIndex(physicalDevice);
        deviceQueueCreateInfo.queueCount = 1; 
        deviceQueueCreateInfo.pQueuePriorities = &queuePriority;

        return deviceQueueCreateInfo;
    }

    vk::DeviceCreateInfo Context::createDeviceCreateInfo() const
    {
        vk::DeviceCreateInfo deviceCreateInfo;
        deviceCreateInfo.sType = vk::StructureType::eDeviceCreateInfo;
        deviceCreateInfo.queueCreateInfoCount = 1;
        deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
        deviceCreateInfo.pEnabledFeatures = &physicalDeviceHelper.physicalDeviceFeatures;

        deviceCreateInfo.enabledExtensionCount = 0;
        if (instanceHelper.enableValidationLayers)
        {
            deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(instanceHelper.validationLayers.size());
            deviceCreateInfo.ppEnabledLayerNames = instanceHelper.validationLayers.data();
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
        return device;
    }

    vk::raii::Queue Context::createQueue(const vk::raii::Device& device, uint32_t queueFamilyIndex) const
    {
        // We creating only one queue
        uint32_t queueIndex = 0u;
        vk::raii::Queue queue(device, queueFamilyIndex, queueIndex);
        return queue;
    }

}