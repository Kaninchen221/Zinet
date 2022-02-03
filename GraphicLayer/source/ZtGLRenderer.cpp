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

        device.create(physicalDevice, surface);

        queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);

        queue = device.createQueue(queueFamilyIndex);

        SwapChainSupportDetails swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);
        swapChain = std::make_unique<SwapChain>();
        swapChain->create(device, swapChainSupportDetails, surface, window);

        swapChainImages = swapChain->getInternal().getImages();
    }

    Renderer::~Renderer() noexcept
    {
        swapChain.reset();

        surface.destroy(instance); // Must be called
        GLFW::DeinitGLFW();
    }

}