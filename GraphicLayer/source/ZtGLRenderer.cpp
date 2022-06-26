#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "Zinet/GraphicLayer/ZtGLShader.h"
#include "Zinet/GraphicLayer/ZtGLStagingBuffer.h"
#include "Zinet/GraphicLayer/ZtGLBuffer.h"
#include "Zinet/GraphicLayer/ZtGLSTBImage.h"

namespace zt::gl
{
    void Renderer::prepare()
    {
        GLFW::Init();

        vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
        instance.getRequiredExtensions();
        vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
        instance.create(context, instanceCreateInfo);
        
        if(Instance::GetEnabledValidationLayers())
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
        vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
        vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice, surface, deviceQueueCreateInfo);
        device.create(physicalDevice, deviceCreateInfo);
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
        prepareTexture();

        vk::DescriptorPoolSize uniformPoolSize = descriptorPool.createUniformPoolSize();
        vk::DescriptorPoolSize imageSamplerPoolSize = descriptorPool.createImageSamplerPoolSize();

        std::vector<vk::DescriptorPoolSize> poolSizes = { uniformPoolSize, imageSamplerPoolSize };
        vk::DescriptorPoolCreateInfo descriptorPoolCreateInfo = descriptorPool.createCreateInfo(poolSizes);
        descriptorPool.create(device, descriptorPoolCreateInfo);

        std::size_t descriptorSetCount = 1u;
        vk::DescriptorSetAllocateInfo descriptorsSetsAllocateInfo = descriptorPool.createDescriptorSetAllocateInfo(pipelineLayout.getDescriptorSetLayout(), descriptorSetCount);

        descriptorSets = DescriptorSets{ device, descriptorsSetsAllocateInfo };

        vk::DescriptorBufferInfo uniformDescriptorBufferInfo = uniformBuffer.createDescriptorBufferInfo();
        vk::WriteDescriptorSet uniformWriteDescriptorSet = descriptorSets->createWriteDescriptorSet(0u, uniformDescriptorBufferInfo);

        vk::DescriptorImageInfo imageDescriptorBufferInfo = imageBuffer.createDescriptorImageInfo(sampler, imageView, vk::ImageLayout::eShaderReadOnlyOptimal);
        //vk::DescriptorImageInfo imageDescriptorBufferInfo = imageBuffer.createDescriptorImageInfo(sampler, imageView, vk::ImageLayout::eTransferDstOptimal);
        vk::WriteDescriptorSet imageWriteDescriptorSet = descriptorSets->createWriteDescriptorSet(0u, imageDescriptorBufferInfo);

        std::array<vk::WriteDescriptorSet, 2> descriptorSets{ uniformWriteDescriptorSet, imageWriteDescriptorSet };
        device->updateDescriptorSets(descriptorSets, {});

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
            vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(swapChainImage, swapChainSupportDetails.pickFormat().format);
            imageView.create(device, imageViewCreateInfo);
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
        vertex.setTextureCoordinates({ 1.0f, 0.0f });
        vertices.push_back(vertex);

        vertex.setPosition({ 0.5f, -0.5f, 0.f });
        vertex.setColor({ 0.0f, 1.0f, 0.0f, 1.0f });
        vertex.setTextureCoordinates({ 0.0f, 0.0f });
        vertices.push_back(vertex);

        vertex.setPosition({ 0.5f, 0.5f, 0.f });
        vertex.setColor({ 0.0f, 0.0f, 1.0f, 1.0f });
        vertex.setTextureCoordinates({ 0.0f, 1.0f });
        vertices.push_back(vertex);

        vertex.setPosition({ -0.5f, 0.5f, 0.f });
        vertex.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
        vertex.setTextureCoordinates({ 1.0f, 1.0f });
        vertices.push_back(vertex);

        // Staging Buffer
        StagingBuffer stagingBuffer;
        std::uint64_t verticesSize = sizeof(Vertex) * vertices.size();
        vk::BufferCreateInfo stagingBufferCreateInfo = stagingBuffer.createCreateInfo(verticesSize);
        stagingBuffer.create(device, stagingBufferCreateInfo);
        
        vk::MemoryRequirements stagingBufferMemoryRequirements = stagingBuffer->getMemoryRequirements();
        vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
        vk::MemoryPropertyFlags stagingBufferMemoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
        vk::MemoryAllocateInfo stagingBufferMemoryAllocateInfo = stagingBuffer.createMemoryAllocateInfo(stagingBufferMemoryRequirements, physicalDeviceMemoryProperties, stagingBufferMemoryPropertyFlags);

        DeviceMemory stagingBufferDeviceMemory;
        stagingBufferDeviceMemory.create(device, stagingBufferMemoryAllocateInfo);

        stagingBuffer.bindMemory(stagingBufferDeviceMemory);
        stagingBufferDeviceMemory.fillWithSTDContainer(vertices);

        // Vertex Buffer
        vk::BufferCreateInfo vertexBufferCreateInfo = vertexBuffer.createCreateInfo(verticesSize);
        vertexBuffer.create(device, vertexBufferCreateInfo);

        vk::MemoryRequirements vertexBufferMemoryRequirements = vertexBuffer->getMemoryRequirements();
        vk::MemoryPropertyFlags vertexBufferMemoryPropertyFlags = vk::MemoryPropertyFlagBits::eDeviceLocal;
        vk::MemoryAllocateInfo vertexBufferMemoryAllocateInfo = vertexBuffer.createMemoryAllocateInfo(vertexBufferMemoryRequirements, physicalDeviceMemoryProperties, vertexBufferMemoryPropertyFlags);

        vertexBufferDeviceMemory.create(device, vertexBufferMemoryAllocateInfo);

        vertexBuffer.bindMemory(vertexBufferDeviceMemory);

        // Copy Staging Buffer to Vertex Buffer
        CommandBuffer transferCommandBuffer;
        vk::CommandBufferAllocateInfo allocateInfo = transferCommandBuffer.createCommandBufferAllocateInfo(commandPool);
        transferCommandBuffer.allocateCommandBuffer(device, commandPool);

        queue.copyBufferToBufferWaitIdle(transferCommandBuffer, stagingBuffer, vertexBuffer);
    }

    void Renderer::prepareIndexBuffer()
    {
        // Indices
        indices = { 0, 1, 2, 2, 3, 0 };

        // Staging Buffer
        StagingBuffer stagingBuffer;
        std::uint64_t size = sizeof(decltype(indices)::value_type) * indices.size();
        vk::BufferCreateInfo stagingBufferCreateInfo = stagingBuffer.createCreateInfo(size);
        stagingBuffer.create(device, stagingBufferCreateInfo);

        vk::MemoryRequirements stagingBufferMemoryRequirements = stagingBuffer->getMemoryRequirements();
        vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
        vk::MemoryPropertyFlags stagingBufferMemoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
        vk::MemoryAllocateInfo stagingBufferMemoryAllocateInfo = stagingBuffer.createMemoryAllocateInfo(stagingBufferMemoryRequirements, physicalDeviceMemoryProperties, stagingBufferMemoryPropertyFlags);

        DeviceMemory stagingBufferDeviceMemory;
        stagingBufferDeviceMemory.create(device, stagingBufferMemoryAllocateInfo);

        stagingBuffer.bindMemory(stagingBufferDeviceMemory);
        stagingBufferDeviceMemory.fillWithSTDContainer(indices);

        // IndexBuffer
        vk::BufferCreateInfo indexBufferCreateInfo = indexBuffer.createCreateInfo(size);
        indexBuffer.create(device, indexBufferCreateInfo);

        vk::MemoryRequirements indexBufferMemoryRequirements = indexBuffer->getMemoryRequirements();
        vk::MemoryPropertyFlags indexBufferMemoryPropertyFlags = vk::MemoryPropertyFlagBits::eDeviceLocal;
        vk::MemoryAllocateInfo indexBufferMemoryAllocateInfo = indexBuffer.createMemoryAllocateInfo(indexBufferMemoryRequirements, physicalDeviceMemoryProperties, indexBufferMemoryPropertyFlags);

        indexBufferDeviceMemory.create(device, indexBufferMemoryAllocateInfo);

        indexBuffer.bindMemory(indexBufferDeviceMemory);

        // Copy Staging Buffer to Index Buffer
        CommandBuffer transferCommandBuffer;
        vk::CommandBufferAllocateInfo allocateInfo = transferCommandBuffer.createCommandBufferAllocateInfo(commandPool);
        transferCommandBuffer.allocateCommandBuffer(device, commandPool);

        queue.copyBufferToBufferWaitIdle(commandBuffer, stagingBuffer, indexBuffer);
    }

    void Renderer::prepareUniformBuffer()
    {
        std::uint64_t size = sizeof(MVP);
        vk::BufferCreateInfo uniformBufferCreateInfo = uniformBuffer.createCreateInfo(size);
        uniformBuffer.create(device, uniformBufferCreateInfo);

        vk::MemoryRequirements memoryRequirements = uniformBuffer->getMemoryRequirements();
        vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
        vk::MemoryPropertyFlags uniformBufferMemoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
        vk::MemoryAllocateInfo uniformBufferMemoryAllocateInfo = uniformBuffer.createMemoryAllocateInfo(memoryRequirements, physicalDeviceMemoryProperties, uniformBufferMemoryPropertyFlags);

        uniformBufferDeviceMemory.create(device, uniformBufferMemoryAllocateInfo);

        uniformBuffer.bindMemory(uniformBufferDeviceMemory);
        uniformBufferDeviceMemory.fillWithObject(mvp);
    }

    void Renderer::prepareTexture()
    {
        STBImage stbImage;
        if (!stbImage.load((contentPath / "texture.jpg").string()))
        {
            Logger->error("Can't load texture image");
            return;
        }

        // Staging Buffer
        StagingBuffer stagingBuffer;
        std::uint64_t size = stbImage.sizeBytes();
        vk::BufferCreateInfo stagingBufferCreateInfo = stagingBuffer.createCreateInfo(size);
        stagingBuffer.create(device, stagingBufferCreateInfo);

        vk::MemoryRequirements stagingBufferMemoryRequirements = stagingBuffer->getMemoryRequirements();
        vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
        vk::MemoryPropertyFlags stagingBufferMemoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
        vk::MemoryAllocateInfo stagingBufferMemoryAllocateInfo = stagingBuffer.createMemoryAllocateInfo(stagingBufferMemoryRequirements, physicalDeviceMemoryProperties, stagingBufferMemoryPropertyFlags);

        DeviceMemory stagingBufferDeviceMemory;
        stagingBufferDeviceMemory.create(device, stagingBufferMemoryAllocateInfo);

        stagingBuffer.bindMemory(stagingBufferDeviceMemory);
        stagingBufferDeviceMemory.fillWithArray(stbImage.get(), size);

        // Image Buffer
        vk::BufferCreateInfo imageBufferCreateInfo = imageBuffer.createCreateInfo(size);
        imageBuffer.create(device, imageBufferCreateInfo);

        // Image
        vk::ImageCreateInfo createInfo = image.createCreateInfo(stbImage.getWidth(), stbImage.getHeight());
        image.create(device, createInfo);

        // Image Device Memory
        vk::MemoryRequirements memoryRequirements = image->getMemoryRequirements();
        vk::MemoryPropertyFlags imageBufferMemoryPropertyFlags = vk::MemoryPropertyFlagBits::eDeviceLocal;
        vk::MemoryAllocateInfo imageBufferMemoryAllocateInfo = imageBuffer.createMemoryAllocateInfo(memoryRequirements, physicalDeviceMemoryProperties, imageBufferMemoryPropertyFlags);

        imageDeviceMemory.create(device, imageBufferMemoryAllocateInfo);
        imageBuffer.bindMemory(imageDeviceMemory);

        // Image
        image->bindMemory(*imageDeviceMemory.getInternal(), 0u);

        // Transfer CommandBuffer
        vk::CommandBufferAllocateInfo allocateInfo = commandBuffer.createCommandBufferAllocateInfo(commandPool);
        commandBuffer.allocateCommandBuffer(device, commandPool);

        commandBuffer.begin();

        // Barrier
        vk::ImageLayout oldLayout = vk::ImageLayout::eUndefined;
        //vk::ImageLayout newLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
        vk::ImageLayout newLayout = vk::ImageLayout::eTransferDstOptimal;
        //vk::ImageLayout newLayout = vk::ImageLayout::eGeneral;
        vk::ImageMemoryBarrier barrier = commandBuffer.createImageMemoryBarrier(image, oldLayout, newLayout);

        vk::PipelineStageFlags sourceStage = vk::PipelineStageFlagBits::eTopOfPipe;
        //vk::PipelineStageFlags sourceStage = vk::PipelineStageFlagBits::eTransfer;

        //vk::PipelineStageFlags destinationStage = vk::PipelineStageFlagBits::eTransfer;
        vk::PipelineStageFlags destinationStage = vk::PipelineStageFlagBits::eFragmentShader;
        //vk::PipelineStageFlags destinationStage = vk::PipelineStageFlagBits::eTransferDstOptimal;

        commandBuffer->pipelineBarrier(
            sourceStage,
            destinationStage,
            vk::DependencyFlags{},
            {},
            {},
            barrier);

        commandBuffer.end();

        SubmitInfo submitInfo{};
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

        queue.submit(submitInfo);
        queue->waitIdle();

        // BufferImageCopy
        vk::BufferImageCopy imageRegion{};
        imageRegion.bufferOffset = 0;
        imageRegion.bufferRowLength = 0;
        imageRegion.bufferImageHeight = 0;

        imageRegion.imageSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
        imageRegion.imageSubresource.mipLevel = 0;
        imageRegion.imageSubresource.baseArrayLayer = 0;
        imageRegion.imageSubresource.layerCount = 1;

        imageRegion.imageOffset = vk::Offset3D{ 0, 0, 0 };
        imageRegion.imageExtent = vk::Extent3D{
            static_cast<std::uint32_t>(stbImage.getWidth()),
            static_cast<std::uint32_t>(stbImage.getHeight()),
            1
        };

        allocateInfo = commandBuffer.createCommandBufferAllocateInfo(commandPool);
        commandBuffer.allocateCommandBuffer(device, commandPool);

        commandBuffer.begin();

        newLayout = vk::ImageLayout::eTransferDstOptimal;
        commandBuffer->copyBufferToImage(*stagingBuffer.getInternal(), *image.getInternal(), newLayout, imageRegion); // TODO Simplify it
        commandBuffer->end();

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

        queue.submit(submitInfo);
        queue->waitIdle();

        // Barrier after copy=
        allocateInfo = commandBuffer.createCommandBufferAllocateInfo(commandPool);
        commandBuffer.allocateCommandBuffer(device, commandPool);

        commandBuffer.begin();

        oldLayout = vk::ImageLayout::eTransferDstOptimal;
        newLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
        vk::ImageMemoryBarrier barrierAfterCopy = commandBuffer.createImageMemoryBarrier(image, oldLayout, newLayout);

        sourceStage = vk::PipelineStageFlagBits::eTransfer;
        destinationStage = vk::PipelineStageFlagBits::eFragmentShader;

        commandBuffer->pipelineBarrier(
            sourceStage,
            destinationStage,
            vk::DependencyFlags{},
            {},
            {},
            barrierAfterCopy);

        commandBuffer.end();

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

        queue.submit(submitInfo);
        queue->waitIdle();

        // ImageView
        vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(*image.getInternal(), vk::Format::eR8G8B8A8Srgb);
        imageView.create(device, imageViewCreateInfo);

        // Sampler
        vk::SamplerCreateInfo samplerCreateInfo = sampler.createCreateInfo();
        sampler.create(device, samplerCreateInfo);
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
        commandBuffer->bindIndexBuffer(*indexBuffer.getInternal(), 0, vk::IndexType::eUint16); // TODO create simple function

        std::vector<vk::DescriptorSet> tempDescriptorSets;
        for (auto& set : *descriptorSets)
        {
            tempDescriptorSets.push_back(*set);
        }
        commandBuffer->bindDescriptorSets(vk::PipelineBindPoint::eGraphics, *pipelineLayout.getInternal(), 0, tempDescriptorSets, {}); // TODO create simple function

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

        GLFW::Deinit();
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