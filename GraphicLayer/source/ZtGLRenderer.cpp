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

        /// SwapChain

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

        /// Shaders

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

        vk::PipelineShaderStageCreateInfo vertexShaderStage = pipelineLayout.createShaderStageCreateInfo(vertexShaderModule);
        vk::PipelineShaderStageCreateInfo fragmentShaderStage = pipelineLayout.createShaderStageCreateInfo(fragmentShaderModule);

        std::vector<vk::PipelineShaderStageCreateInfo> shaderStages = { vertexShaderStage, fragmentShaderStage };

        /// Pipeline
        /// Draw at entire space
        
        vk::Extent2D swapExtent = swapChainSupportDetails.pickSwapExtent(window);
        pipelineLayout.setViewportSize(swapExtent.width, swapExtent.height);

        vk::Rect2D scissor;
        scissor.offset = vk::Offset2D{ 0, 0 };
        scissor.extent = swapExtent;
        pipelineLayout.setScissor(scissor);

        pipelineLayout.createColorBlendAttachmentState();

        pipelineLayout.createPipelineLayout(device);
        
        /// RenderPass

        renderPass.createAttachmentDescription(swapChainSupportDetails.pickFormat().format);
        renderPass.createAttachmentReference();
        renderPass.createSubpassDescription();

        renderPass.create(device);

        /// Pipeline

        vk::GraphicsPipelineCreateInfo createInfo = pipeline.createGraphicsPipelineCreateInfo(pipelineLayout, renderPass, shaderStages);
        pipeline.create(device, createInfo);

        // Framebuffers

        for (ImageView& imageView : imageViews)
        {
            Framebuffer framebuffer;
            framebuffer.create(device, imageView, renderPass, swapExtent);
            framebuffers.push_back(std::move(framebuffer));
        }

        // Commands

        for(Framebuffer& framebuffer : framebuffers)
        { 

            // Command Pool

            uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
            commandPool.create(device, queueFamilyIndex);

            // Command Buffer

            commandBuffer.allocateCommandBuffer(device, commandPool);

            commandBuffer.begin();

            vk::Rect2D renderArea; 
            renderArea.offset = vk::Offset2D{ 0, 0 };
            renderArea.extent = swapExtent;

            commandBuffer.beginRenderPass(renderPass, framebuffer, renderArea);

            commandBuffer->draw(3, 1, 0, 0);

            commandBuffer.endRenderPass();
            commandBuffer.end();
            
        }
    }

    Renderer::~Renderer() noexcept
    {
        framebuffers.clear();
        imageViews.clear();
        swapChain.reset();

        GLFW::DeinitGLFW();
    }

}