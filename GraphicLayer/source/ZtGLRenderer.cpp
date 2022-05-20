#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "Zinet/GraphicLayer/ZtGLShader.h"
#include "Zinet/GraphicLayer/ZtGLStagingBuffer.h"

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

        prepareVertexBuffer();
        prepareIndexBuffer();
        prepareUniformBuffer();
    }

    void Renderer::run()
    {
        while (!window.shouldBeClosed())
        {
            glfwPollEvents();
            updateMVP();
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

    void Renderer::prepareVertexBuffer()
    {
        // Vertices
        Vertex vertex;
        vertex.setPosition({ -0.5f, -0.5f, 0.f });
        vertex.setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
        vertices.push_back(vertex);

        vertex.setPosition({ 0.5f, -0.5f, 0.f });
        vertex.setColor({ 0.0f, 1.0f, 0.0f, 1.0f });
        vertices.push_back(vertex);

        vertex.setPosition({ 0.5f, 0.5f, 0.f });
        vertex.setColor({ 0.0f, 0.0f, 1.0f, 1.0f });
        vertices.push_back(vertex);

        vertex.setPosition({ -0.5f, 0.5f, 0.f });
        vertex.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
        vertices.push_back(vertex);

        // Staging Buffer
        StagingBuffer stagingBuffer;
        std::uint64_t verticesSize = sizeof(Vertex) * vertices.size();
        stagingBuffer.setSize(verticesSize);
        vk::BufferCreateInfo stagingBufferCreateInfo = stagingBuffer.createCreateInfo();
        stagingBuffer.create(device, stagingBufferCreateInfo);

        vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
        vk::MemoryPropertyFlags stagingBufferMemoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
        vk::MemoryAllocateInfo stagingBufferMemoryAllocateInfo = stagingBuffer.createMemoryAllocateInfo(physicalDeviceMemoryProperties, stagingBufferMemoryPropertyFlags);

        DeviceMemory stagingBufferDeviceMemory;
        stagingBufferDeviceMemory.create(device, stagingBufferMemoryAllocateInfo);

        stagingBuffer.bindMemory(stagingBufferDeviceMemory);
        stagingBufferDeviceMemory.fillWithSTDContainer(vertices);

        // Vertex Buffer
        vertexBuffer.setSize(verticesSize);
        vk::BufferCreateInfo vertexBufferCreateInfo = vertexBuffer.createCreateInfo();
        vertexBuffer.create(device, vertexBufferCreateInfo);

        vk::MemoryPropertyFlags vertexBufferMemoryPropertyFlags = vk::MemoryPropertyFlagBits::eDeviceLocal;
        vk::MemoryAllocateInfo vertexBufferMemoryAllocateInfo = vertexBuffer.createMemoryAllocateInfo(physicalDeviceMemoryProperties, vertexBufferMemoryPropertyFlags);

        vertexBufferDeviceMemory.create(device, vertexBufferMemoryAllocateInfo);

        vertexBuffer.bindMemory(vertexBufferDeviceMemory);

        // Copy Staging Buffer to Vertex Buffer
        CommandBuffer transferCommandBuffer;
        vk::CommandBufferAllocateInfo allocateInfo = transferCommandBuffer.createCommandBufferAllocateInfo(commandPool);
        transferCommandBuffer.allocateCommandBuffer(device, commandPool);

        transferCommandBuffer.copyBuffer(stagingBuffer, vertexBuffer);

        SubmitInfo submitInfo{};
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &*transferCommandBuffer.getInternal();

        queue.submit(submitInfo);
        queue->waitIdle();
    }

    void Renderer::prepareIndexBuffer()
    {
        // Indices
        indices = { 0, 1, 2, 2, 3, 0 };

        // Staging Buffer
        StagingBuffer stagingBuffer;
        std::uint64_t size = sizeof(decltype(indices)::value_type) * indices.size();
        stagingBuffer.setSize(size);
        vk::BufferCreateInfo stagingBufferCreateInfo = stagingBuffer.createCreateInfo();
        stagingBuffer.create(device, stagingBufferCreateInfo);

        vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
        vk::MemoryPropertyFlags stagingBufferMemoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
        vk::MemoryAllocateInfo stagingBufferMemoryAllocateInfo = stagingBuffer.createMemoryAllocateInfo(physicalDeviceMemoryProperties, stagingBufferMemoryPropertyFlags);

        DeviceMemory stagingBufferDeviceMemory;
        stagingBufferDeviceMemory.create(device, stagingBufferMemoryAllocateInfo);

        stagingBuffer.bindMemory(stagingBufferDeviceMemory);
        stagingBufferDeviceMemory.fillWithSTDContainer(indices);

        // IndexBuffer
        indexBuffer.setSize(size);
        vk::BufferCreateInfo indexBufferCreateInfo = indexBuffer.createCreateInfo();
        indexBuffer.create(device, indexBufferCreateInfo);

        vk::MemoryPropertyFlags indexBufferMemoryPropertyFlags = vk::MemoryPropertyFlagBits::eDeviceLocal;
        vk::MemoryAllocateInfo indexBufferMemoryAllocateInfo = indexBuffer.createMemoryAllocateInfo(physicalDeviceMemoryProperties, indexBufferMemoryPropertyFlags);

        indexBufferDeviceMemory.create(device, indexBufferMemoryAllocateInfo);

        indexBuffer.bindMemory(indexBufferDeviceMemory);

        // Copy Staging Buffer to Index Buffer
        CommandBuffer transferCommandBuffer;
        vk::CommandBufferAllocateInfo allocateInfo = transferCommandBuffer.createCommandBufferAllocateInfo(commandPool);
        transferCommandBuffer.allocateCommandBuffer(device, commandPool);

        transferCommandBuffer.copyBuffer(stagingBuffer, indexBuffer);

        SubmitInfo submitInfo{};
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &*transferCommandBuffer.getInternal();

        queue.submit(submitInfo);
        queue->waitIdle();
    }

    void Renderer::prepareUniformBuffer()
    {
        std::uint64_t size = sizeof(MVP);
        uniformBuffer.setSize(size);
        vk::BufferCreateInfo uniformBufferCreateInfo = uniformBuffer.createCreateInfo();
        uniformBuffer.create(device, uniformBufferCreateInfo);

        vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
        vk::MemoryPropertyFlags uniformBufferMemoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
        vk::MemoryAllocateInfo uniformBufferMemoryAllocateInfo = uniformBuffer.createMemoryAllocateInfo(physicalDeviceMemoryProperties, uniformBufferMemoryPropertyFlags);

        uniformBufferDeviceMemory.create(device, uniformBufferMemoryAllocateInfo);

        uniformBuffer.bindMemory(uniformBufferDeviceMemory);
        uniformBufferDeviceMemory.fillWithObject(mvp);
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
        commandBuffer->bindIndexBuffer(*indexBuffer.getInternal(), 0, vk::IndexType::eUint16);
        commandBuffer->drawIndexed(indices.size(), 1, 0, 0, 0);
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

        SubmitInfo submitInfo = Queue::CreateSubmitInfo(
            waitSemaphores,
            waitPipelineStageFlags,
            commandBuffers,
            signalSemaphores);

        //std::array<SubmitInfo, 1> submitInfos = { submitInfo };
        queue.submit(submitInfo, drawFence);
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

    void Renderer::updateMVP()
    {
        float time = glfwGetTime();
        mvp.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        mvp.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        mvp.proj = glm::perspective(glm::radians(45.0f), swapExtent.width / (float)swapExtent.height, 0.1f, 10.0f);
        mvp.proj[1][1] *= -1;

        uniformBufferDeviceMemory.fillWithObject(mvp);
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