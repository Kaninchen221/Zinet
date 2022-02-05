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

        swapChainImages = swapChain->getImages();
        imageViews.reserve(swapChainImages.size());
        for (vk::Image swapChainImage : swapChainImages)
        {
            ImageView imageView;
            imageView.create(device, swapChainImage, swapChainSupportDetails.pickFormat().format);
            imageViews.push_back(std::move(imageView));
        }
    }

    Renderer::~Renderer() noexcept
    {
        imageViews.clear();
        swapChain.reset();
        surface.destroy(instance);

        GLFW::DeinitGLFW();
    }

}