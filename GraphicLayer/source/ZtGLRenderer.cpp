#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "Zinet/GraphicLayer/ZtGLShader.h"

namespace zt::gl
{
    void Renderer::prepare()
    {
        GLFW::InitGLFW();

        instance.createApplicationInfo();
        instance.createInstanceCreateInfo();
        instance.create(context);

        debugUtilsMessenger.create(instance);

        window.create();

        bool surfaceResult = surface.create(instance, window);
        if (!surfaceResult)
        {
            Logger->error("Can't create surface");
        }

        bool physicalDeviceResult = physicalDevice.create(instance);
        if (!physicalDeviceResult)
        {
            Logger->error("Can't create physical device");
        }

        queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
        device.create(physicalDevice, surface);
        queue.create(device, queueFamilyIndex);

        prepareSwapChain();
        prepareShaders();

        /// Pipeline
        /// Draw at entire space
        
        swapExtent = swapChainSupportDetails.pickSwapExtent(window);
        pipelineLayout.setViewportSize(swapExtent.width, swapExtent.height);

        vk::Rect2D scissor;
        scissor.offset = vk::Offset2D{ 0, 0 };
        scissor.extent = swapExtent;
        pipelineLayout.setScissor(scissor);

        pipelineLayout.createColorBlendAttachmentState();

        pipelineLayout.create(device);
        
        /// RenderPass

        renderPass.createAttachmentDescription(swapChainSupportDetails.pickFormat().format);
        renderPass.createAttachmentReference();
        renderPass.createSubpassDescription();
        renderPass.createSubpassDependency();

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

        // Command Pool
        commandPool.create(device, queueFamilyIndex);

        // Command Buffer
        commandBuffer.allocateCommandBuffer(device, commandPool);

        // Fences
        drawFence.createSignaled(device);
        //acquireNextImageFence.createSignaled(device);

        // Semaphores
        imageAvailableSemaphore.create(device);
        renderFinishedSemaphore.create(device);
        
        // Vertices
        std::vector<Vertex> vertices;

        Vertex vertex;
        glm::vec3 position;
        position.x = 0.f;
        position.y = -0.5f;
        position.z = 0.f;
        vertex.setPosition(position);
        vertex.setColor({ 0.0f, 0.0f, 1.0f, 1.0f });
        vertices.push_back(vertex);

        position.x = 0.5f;
        position.y = 0.5f;
        position.z = 0.f;
        vertex.setPosition(position);
        vertex.setColor({ 0.0f, 1.0f, 0.0f, 1.0f });
        vertices.push_back(vertex);

        position.x = -0.5f;
        position.y = 0.5f;
        position.z = 0.f;
        vertex.setPosition({ -0.5f, 0.5f, 0.f });
        vertex.setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
        vertices.push_back(vertex);

        // Vertex Buffer & Device Memory
        vertexBuffer.setVertices(vertices);

        vk::BufferCreateInfo vertexBufferCreateInfo = vertexBuffer.createCreateInfo();
        vertexBuffer.create(device, vertexBufferCreateInfo);

        vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
        vk::MemoryPropertyFlags memoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
        vk::MemoryAllocateInfo vertexBufferMemoryAllocateInfo = vertexBuffer.createMemoryAllocateInfo(physicalDeviceMemoryProperties, memoryPropertyFlags);

        deviceMemory.create(device, vertexBufferMemoryAllocateInfo);

        vertexBuffer.bindMemory(deviceMemory);

        deviceMemory.fillWithVertexBuffer(vertexBuffer);
    }

    void Renderer::run()
    {
        while (!window.shouldBeClosed())
        {
            glfwPollEvents();
            drawFrame();
        }
    }

    void Renderer::prepareSwapChain()
    {
        swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);
        swapChain.create(device, swapChainSupportDetails, surface, window);

        swapChainImages = swapChain.getImages();
        imageViews.reserve(swapChainImages.size());
        for (vk::Image swapChainImage : swapChainImages)
        {
            ImageView imageView;
            imageView.create(device, swapChainImage, swapChainSupportDetails.pickFormat().format);
            imageViews.push_back(std::move(imageView));
        }
    }

    void Renderer::prepareShaders()
    {
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

        shaderStages = { vertexShaderStage, fragmentShaderStage };

    }

    void Renderer::drawFrame()
    {
        device.waitForFence(drawFence);
        //device.waitForFence(acquireNextImageFence); /* Perhaps should be in other place */
        device.resetFence(drawFence);
        //device.resetFence(acquireNextImageFence);

        uint64_t nextImageTimeout = UINT64_MAX;
        Fence acquireNextImageFence;
        std::pair<vk::Result, uint32_t> nextImage = swapChain.acquireNextImage(nextImageTimeout, imageAvailableSemaphore, acquireNextImageFence);
        
        commandBuffer.reset();
        commandBuffer.begin();

        vk::Rect2D renderArea;
        renderArea.offset = vk::Offset2D{ 0, 0 };
        renderArea.extent = swapExtent;

        commandBuffer.beginRenderPass(renderPass, framebuffers[nextImage.second], renderArea);
        commandBuffer.bindPipeline(pipeline);
        vk::ArrayProxy<const vk::Buffer> vertexBuffers{ *vertexBuffer.getInternal() };
        commandBuffer->bindVertexBuffers(0u, vertexBuffers, vk::DeviceSize{ 0 });
        commandBuffer->draw(3, 1, 0, 0);
        commandBuffer.endRenderPass();
        commandBuffer.end();

        submit();

        present(nextImage.second);

    }

    void Renderer::submit()
    {
        std::array<Semaphore*, 1> waitSemaphores = { &imageAvailableSemaphore };
        vk::PipelineStageFlags waitPipelineStageFlags = vk::PipelineStageFlagBits::eColorAttachmentOutput;
        std::array<CommandBuffer*, 1> commandBuffers = { &commandBuffer };
        std::array<Semaphore*, 1> signalSemaphores = { &renderFinishedSemaphore };

        vk::SubmitInfo submitInfo = Queue::CreateSubmitInfo(
            waitSemaphores,
            waitPipelineStageFlags,
            commandBuffers,
            signalSemaphores);

        std::array<vk::SubmitInfo, 1> submitInfos = { submitInfo };
        queue.submit(submitInfos, drawFence);
    }

    void Renderer::present(uint32_t image)
    {
        std::array<Semaphore*, 1> waitSemaphores = { &renderFinishedSemaphore };
        std::array<SwapChain*, 1> swapChains = { &swapChain };
        vk::PresentInfoKHR presentInfo = Queue::CreatePresentInfo(
            waitSemaphores,
            swapChains,
            image);

        queue.present(presentInfo);
    }

    Renderer::~Renderer() noexcept
    {
        if (*drawFence.getInternal() != *vk::raii::Fence{ std::nullptr_t{} })
            device.waitForFence(drawFence);

        framebuffers.clear();
        imageViews.clear();

        GLFW::DeinitGLFW();
    }

    Context& Renderer::getContext()
    {
        return context;
    }

    Instance& Renderer::getInstance()
    {
        return instance;
    }

    DebugUtilsMessenger& Renderer::getDebugUtilsMessenger()
    {
        return debugUtilsMessenger;
    }

    Window& Renderer::getWindow()
    {
        return window;
    }

    Surface& Renderer::getSurface()
    {
        return surface;
    }

    PhysicalDevice& Renderer::getPhysicalDevice()
    {
        return physicalDevice;
    }

    Device& Renderer::getDevice()
    {
        return device;
    }

    Queue& Renderer::getQueue()
    {
        return queue;
    }

    SwapChain& Renderer::getSwapChain()
    {
        return swapChain;
    }

    PipelineLayout& Renderer::getPipelineLayout()
    {
        return pipelineLayout;
    }

    RenderPass& Renderer::getRenderPass()
    {
        return renderPass;
    }

    Pipeline& Renderer::getPipeline()
    {
        return pipeline;
    }

    std::vector<Framebuffer>& Renderer::getFramebuffers()
    {
        return framebuffers;
    }

    CommandPool& Renderer::getCommandPool()
    {
        return commandPool;
    }

    CommandBuffer& Renderer::getCommandBuffer()
    {
        return commandBuffer;
    }

}