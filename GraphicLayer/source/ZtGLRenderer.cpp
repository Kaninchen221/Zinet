#include "Zinet/GraphicLayer/ZtGLRenderer.h"

namespace zt::gl
{
    Renderer::Renderer()
    {
        GLFW::InitGLFW();

        instance.createApplicationInfo();
        instance.createInstanceCreateInfo();
        instance.create(context);

        debugUtilsMessenger.createDebugUtilsMessenger(instance);

        window.createWindow();

        bool surfaceResult = surface.create(instance, window);
        if (!surfaceResult)
        {
            Logger->error("Can't create surface");
            return;
        }

        bool physicalDeviceResult = physicalDevice.create(instance);
        if(!physicalDeviceResult)
        {
            Logger->error("Can't create physical device");
            return;
        }

        device.createDeviceQueueCreateInfo(physicalDevice, surface);
        device.create(physicalDevice);

        queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);

        queue = device.createQueue(queueFamilyIndex);
    }

    Renderer::~Renderer() noexcept
    {
        surface.destroy(instance); // Must be called
        GLFW::DeinitGLFW();
    }

}