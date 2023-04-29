#include "ZtGLRendererBuilder.h"

#include "Zinet/GraphicLayer/ZtGLShader.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLStagingBuffer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLBuffer.h"
#include "Zinet/GraphicLayer/ZtGLSTBImage.h"

namespace zt::gl::tests
{
    RendererBuilder::RendererBuilder()
    {
        GLFW::Init();
        GLFW::HideWindow();
    }

    void RendererBuilder::createAll()
    {
        createInstance();
        createDebugUtilsMessenger();
        createWindow();
        createSurface();
        createPhysicalDevice();
        createDevice();

		VmaAllocatorCreateInfo allocatorCreateInfo = vma.createAllocatorCreateInfo(instance, device, physicalDevice);
		vma.create(allocatorCreateInfo);

        createQueue();
        createSwapChain();
        createImageViews();
        createVertexShader();
        createFragmentShader();
        createShaderStages();
        createDescriptorSetLayouts();
        createPipelineLayout();
        createRenderPass();
        createFramebuffers();
        createPipeline();
        createCommandPool();
        createCommandBuffer();
        createFences();
        createSemaphores();
        createVertexBuffer();
        createIndexBuffer();
        createUniformBuffer();
        createTexture();
        createDescrptorPool();
        createDescriptorSets();

        updateDescriptorSets();

		device.waitForFence(drawFence);
    }

    void RendererBuilder::run()
    {
        while (!window.shouldBeClosed())
        {
            glfwPollEvents();
            updateMVP();
            drawFrame();
        }
    }

    void RendererBuilder::createInstance()
    {
        vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
        instance.populateRequiredExtensions();
        vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
        instance.create(context, instanceCreateInfo);
    }

    void RendererBuilder::createDebugUtilsMessenger()
    {
        bool canBeCreated = Instance::GetEnabledValidationLayers();
        if (!canBeCreated)
        {
            Logger->error("Can't create debug utils messenger");
            return;
        }

        debugUtilsMessenger.create(instance);
    }

    void RendererBuilder::createWindow()
    {
        window.create();
    }

    void RendererBuilder::createSurface()
    {
        bool surfaceResult = surface.create(instance, window);
        if (!surfaceResult)
        {
            Logger->error("Can't create surface");
        }
    }

    void RendererBuilder::createPhysicalDevice()
    {
        bool physicalDeviceResult = physicalDevice.create(instance);
        if (!physicalDeviceResult)
        {
            Logger->error("Can't create physical device");
        }
    }

    void RendererBuilder::createDevice()
    {
        queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
        vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
        vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice, surface, deviceQueueCreateInfo);
        device.create(physicalDevice, deviceCreateInfo);
    }

    void RendererBuilder::createQueue()
    {
        queue.create(device, queueFamilyIndex);
    }

    void RendererBuilder::createSwapChain()
    {
        swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);
        vk::SwapchainCreateInfoKHR creatInfo = swapChain.createCreateInfo(swapChainSupportDetails, surface, window);
        swapChain.create(device, creatInfo);
    }

    void RendererBuilder::createImageViews()
    {
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

    void RendererBuilder::createVertexShader()
    {
        vertexShader.setType(ShaderType::Vertex);
        vertexShader.loadFromFile((contentPath / "shader.vert").string());
        if (!vertexShader.compile())
        {
            Logger->error("Can't compile vertex shader");
            return;
        }

        //vertexShaderModule = ShaderModule{};
        vk::ShaderModuleCreateInfo vertexShaderCreateInfo = vertexShaderModule.createShaderModuleCreateInfo(vertexShader);
        vertexShaderModule.create(device, ShaderType::Vertex, vertexShaderCreateInfo);
    }
    
    void RendererBuilder::createFragmentShader()
    {
        fragmentShader.setType(ShaderType::Fragment);
        fragmentShader.loadFromFile((contentPath / "shader.frag").string());
        if (!fragmentShader.compile())
        {
            Logger->error("Can't compile fragment shader");
            return;
        }

		//fragmentShaderModule = ShaderModule{};
		vk::ShaderModuleCreateInfo fragmentShaderCreateInfo = fragmentShaderModule.createShaderModuleCreateInfo(fragmentShader);
		fragmentShaderModule.create(device, ShaderType::Fragment, fragmentShaderCreateInfo);
    }

    void RendererBuilder::createShaderStages()
    {
        vk::PipelineShaderStageCreateInfo vertexShaderStage = pipelineLayout.createShaderStageCreateInfo(vertexShaderModule);
        vk::PipelineShaderStageCreateInfo fragmentShaderStage = pipelineLayout.createShaderStageCreateInfo(fragmentShaderModule);

        shaderStages = { vertexShaderStage, fragmentShaderStage };
    }

    void RendererBuilder::createPipelineLayout()
    {
        swapExtent = swapChainSupportDetails.pickSwapExtent(window);
        pipelineLayout.setViewportSize(static_cast<float>(swapExtent.width), static_cast<float>(swapExtent.height));

        vk::Rect2D scissor;
        scissor.offset = vk::Offset2D{ 0, 0 };
        scissor.extent = swapExtent;
        pipelineLayout.setScissor(scissor);

        pipelineLayout.createColorBlendAttachmentState();

        vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo = pipelineLayout.createPipelineLayoutCreateInfo();
        pipelineLayout.create(device, pipelineLayoutCreateInfo);
    }

    void RendererBuilder::createRenderPass()
    {
        renderPass.createAttachmentDescription(swapChainSupportDetails.pickFormat().format);
        renderPass.createAttachmentReference();
        renderPass.createSubpassDescription();
        renderPass.createSubpassDependency();

        renderPass.create(device);
    }

    void RendererBuilder::createPipeline()
    {
        vk::GraphicsPipelineCreateInfo createInfo = pipeline.createGraphicsPipelineCreateInfo(pipelineLayout, renderPass, shaderStages);
        pipeline.create(device, createInfo);
    }

    void RendererBuilder::createFramebuffers()
    {
        for (ImageView& imageView : imageViews)
        {
			Framebuffer framebuffer;
			vk::FramebufferCreateInfo framebufferCreateInfo = framebuffer.createCreateInfo(imageView, renderPass, swapExtent);
			framebuffer.create(device, framebufferCreateInfo);
            framebuffers.push_back(std::move(framebuffer));
        }
    }

    void RendererBuilder::createCommandPool()
    {
        commandPool.create(device, queueFamilyIndex);
    }

    void RendererBuilder::createCommandBuffer()
    {
        commandBuffer.allocateCommandBuffer(device, commandPool);
    }

    void RendererBuilder::createFences()
    {
        drawFence.createSignaled(device);
    }

    void RendererBuilder::createSemaphores()
    {
        imageAvailableSemaphore.create(device);
        renderFinishedSemaphore.create(device);
    }

    void RendererBuilder::createVertexBuffer()
    {
        //// Vertices
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

		std::uint64_t verticesSize = sizeof(Vertex) * vertices.size();
		BufferCreateInfo bufferCreateInfo{ .device = device, .vma = vma };
		bufferCreateInfo.vkBufferCreateInfo = vertexBuffer.createCreateInfo(verticesSize);
		bufferCreateInfo.allocationCreateInfo = vertexBuffer.createVmaAllocationCreateInfo(false, true);

		vertexBuffer.create(bufferCreateInfo);
        vertexBuffer.fillWithStdContainer(vertices);
    }

    void RendererBuilder::createIndexBuffer()
    {
		indices = { 0, 1, 2, 2, 3, 0 };

		std::uint64_t size = sizeof(decltype(indices)::value_type) * indices.size();
		BufferCreateInfo bufferCreateInfo{ .device = device, .vma = vma };
		bufferCreateInfo.vkBufferCreateInfo = indexBuffer.createCreateInfo(size);
		bufferCreateInfo.allocationCreateInfo = indexBuffer.createVmaAllocationCreateInfo(false, true);

        indexBuffer.create(bufferCreateInfo);
        indexBuffer.fillWithStdContainer(indices);
    }

    void RendererBuilder::createUniformBuffer()
    {
		BufferCreateInfo bufferCreateInfo{ .device = device, .vma = vma };
		bufferCreateInfo.vkBufferCreateInfo = uniformBuffer.createCreateInfo(sizeof(MVP));
		bufferCreateInfo.allocationCreateInfo = uniformBuffer.createVmaAllocationCreateInfo(false, true);

        uniformBuffer.create(bufferCreateInfo);
        uniformBuffer.fillWithObject(mvp);
    }

    void RendererBuilder::createTexture()
    {
        // Buffer
        STBImage stbImage;
        if (!stbImage.load((contentPath / "texture.jpg").string()))
        {
            Logger->error("Can't load texture image");
            return;
        }
        
        std::uint64_t size = stbImage.sizeBytes();

		BufferCreateInfo bufferCreateInfo{ .device = device, .vma = vma };
		bufferCreateInfo.vkBufferCreateInfo = imageBuffer.createCreateInfo(size);
		bufferCreateInfo.allocationCreateInfo = imageBuffer.createVmaAllocationCreateInfo(false, true);

        imageBuffer.create(bufferCreateInfo);
		imageBuffer.fillWithCArray(stbImage.get());

        //// Image
		Image::CreateInfo imageCreateInfo{
			.device = device,
			.vma = vma,
			.vkImageCreateInfo = image.createCreateInfo(stbImage.getWidth(), stbImage.getHeight()),
			.allocationCreateInfo = image.createAllocationCreateInfo()
		};

		image.create(imageCreateInfo);

        // Transfer CommandBuffer
        vk::CommandBufferAllocateInfo allocateInfo = commandBuffer.createCommandBufferAllocateInfo(commandPool);
        commandBuffer.allocateCommandBuffer(device, commandPool);
        
        commandBuffer.begin();
        
        // Barrier
        vk::ImageLayout oldLayout = vk::ImageLayout::eUndefined;
        vk::ImageLayout newLayout = vk::ImageLayout::eTransferDstOptimal;
        vk::ImageMemoryBarrier barrier = commandBuffer.createImageMemoryBarrier(image, oldLayout, newLayout);
        
        vk::PipelineStageFlags sourceStage = vk::PipelineStageFlagBits::eTopOfPipe;
        
        vk::PipelineStageFlags destinationStage = vk::PipelineStageFlagBits::eFragmentShader;
        
        commandBuffer->pipelineBarrier(
            sourceStage,
            destinationStage,
            vk::DependencyFlags{},
            {},
            {},
            barrier);
        
        commandBuffer.end();
        
        vk::SubmitInfo submitInfo{};
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
        commandBuffer.copyBufferToImage(imageBuffer, image, newLayout, imageRegion);
        commandBuffer.end();
        
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
        vk::ImageViewCreateInfo imageViewCreateInfo = textureImageView.createCreateInfo(*image.getInternal(), vk::Format::eR8G8B8A8Srgb);
        textureImageView.create(device, imageViewCreateInfo);
        
        // Sampler
        vk::SamplerCreateInfo samplerCreateInfo = sampler.createCreateInfo();
        sampler.create(device, samplerCreateInfo);
    }

    void RendererBuilder::createDescrptorPool()
    {
        vk::DescriptorPoolSize uniformPoolSize = descriptorPool.createUniformPoolSize();
        vk::DescriptorPoolSize imageSamplerPoolSize = descriptorPool.createImageSamplerPoolSize();

        std::vector<vk::DescriptorPoolSize> poolSizes = { uniformPoolSize, imageSamplerPoolSize };
        vk::DescriptorPoolCreateInfo descriptorPoolCreateInfo = descriptorPool.createCreateInfo(poolSizes);
        descriptorPool.create(device, descriptorPoolCreateInfo);
    }

    void RendererBuilder::createDescriptorSets()
    {
        const std::vector<vk::DescriptorSetLayout>& vkDescriptorSetLayouts = pipelineLayout.getVkDescriptorSetLayouts();
        vk::DescriptorSetAllocateInfo descriptorsSetsAllocateInfo = descriptorPool.createDescriptorSetAllocateInfo(vkDescriptorSetLayouts);

        descriptorSets = DescriptorSets{ device, descriptorsSetsAllocateInfo };
    }

    void RendererBuilder::updateDescriptorSets()
    {
        vk::DescriptorBufferInfo uniformDescriptorBufferInfo = uniformBuffer.createDescriptorBufferInfo();
        vk::WriteDescriptorSet uniformWriteDescriptorSet = descriptorSets->createBufferWriteDescriptorSet(0u, uniformDescriptorBufferInfo);

        vk::DescriptorImageInfo imageDescriptorBufferInfo = imageBuffer.createDescriptorImageInfo(sampler, textureImageView, vk::ImageLayout::eShaderReadOnlyOptimal);
        vk::WriteDescriptorSet imageWriteDescriptorSet = descriptorSets->createImageWriteDescriptorSet(0u, imageDescriptorBufferInfo);

        writeDescriptorSets = std::array<vk::WriteDescriptorSet, 2>{ uniformWriteDescriptorSet, imageWriteDescriptorSet };

        device->updateDescriptorSets(writeDescriptorSets, {});
    }

    void RendererBuilder::createDescriptorSetLayouts()
    {
        DescriptorSetLayout descriptorSetLayout;
        vk::DescriptorSetLayoutBinding uniformLayoutBinding = descriptorSetLayout.createUniformLayoutBinding();
        vk::DescriptorSetLayoutBinding imageSamplerLayoutBinding = descriptorSetLayout.createImageSamplerLayoutBinding();
        std::vector<vk::DescriptorSetLayoutBinding> bindings = { uniformLayoutBinding, imageSamplerLayoutBinding };

        vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo = descriptorSetLayout.createDescriptorSetLayoutCreateInfo(bindings);
        descriptorSetLayout.create(device, descriptorSetLayoutCreateInfo);
        descriptorSetLayouts = { std::move(descriptorSetLayout) };
        pipelineLayout.setDescriptorSetLayouts(descriptorSetLayouts);
    }

    void RendererBuilder::drawFrame()
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

		vk::ClearValue clearValue;

        commandBuffer.beginRenderPass(renderPass, framebuffers[nextImage.second], renderArea, clearValue);
        commandBuffer.bindPipeline(pipeline);
        commandBuffer.bindVertexBuffer(0u, vertexBuffer, vk::DeviceSize{ 0 });
        commandBuffer.bindIndexBuffer(indexBuffer, vk::DeviceSize{ 0 }, vk::IndexType::eUint16);

		if (descriptorSets.has_value())
		{
			commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipelineLayout, 0, descriptorSets.value(), {});
		}

        commandBuffer->drawIndexed(static_cast<std::uint32_t>(indices.size()), 1, 0, 0, 0);
        commandBuffer.endRenderPass();
        commandBuffer.end();

        submit();

        present(nextImage.second);

    }

    void RendererBuilder::submit()
    {
        std::array<Semaphore*, 1> waitSemaphores = { &imageAvailableSemaphore };
        vk::PipelineStageFlags waitPipelineStageFlags = vk::PipelineStageFlagBits::eColorAttachmentOutput;
        std::vector<vk::CommandBuffer> commandBuffers = { *commandBuffer.getInternal() };
        std::array<Semaphore*, 1> signalSemaphores = { &renderFinishedSemaphore };

        vk::SubmitInfo submitInfo = queue.createSubmitInfo(
            waitSemaphores,
            waitPipelineStageFlags,
            commandBuffers,
            signalSemaphores);

        queue.submitWithFence(submitInfo, drawFence);
    }

    void RendererBuilder::present(uint32_t imageToDraw)
    {
        std::array<Semaphore*, 1> waitSemaphores = { &renderFinishedSemaphore };
        std::array<SwapChain*, 1> swapChains = { &swapChain };
        vk::PresentInfoKHR presentInfo = queue.createPresentInfo(
            waitSemaphores,
            swapChains,
            imageToDraw);

        queue.present(presentInfo);
    }

    void RendererBuilder::updateMVP()
    {
        float time = static_cast<float>(glfwGetTime());
        mvp.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        mvp.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        mvp.proj = glm::perspective(glm::radians(45.0f), swapExtent.width / (float)swapExtent.height, 0.1f, 10.0f);
        mvp.proj[1][1] *= -1;

        uniformBuffer.fillWithObject(mvp);
    }

    RendererBuilder::~RendererBuilder() noexcept
    {
        if (drawFence != nullptr)
            device.waitForFence(drawFence);

        framebuffers.clear();
        imageViews.clear();

        GLFW::Deinit();
    }

}