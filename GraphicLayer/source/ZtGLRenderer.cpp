#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "Zinet/GraphicLayer/ZtGLShader.h"

namespace zt::gl
{
    void Renderer::run()
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

        vertexShader.setType(ShaderType::Vertex);
        vertexShader.loadFromFile((contentPath / "shader.vert").string());
        if (!vertexShader.compile())
        {
            Logger->error("Can't compile vertex shader");
            return;
        }

        fragmentShader.setType(ShaderType::Fragment);
        fragmentShader.loadFromFile((contentPath / "shader.frag").string());
        if (!fragmentShader.compile())
        {
            Logger->error("Can't compile fragment shader");
            return;
        }

        vertexShaderModule.create(device, vertexShader);
        fragmentShaderModule.create(device, fragmentShader);

        pipeline.createPipelineLayout(device);
    }

    Renderer::~Renderer() noexcept
    {
        imageViews.clear();
        swapChain.reset();
        surface.destroy(instance);

        GLFW::DeinitGLFW();
    }

}