#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"

#include <map>

namespace zt::gl
{

	Renderer::Renderer()
		: queueFamilyIndex{ std::numeric_limits<uint32_t>::max() }
	{
		GLFW::Init();
	}

	Renderer::~Renderer() noexcept
	{
		if (queue != nullptr)
			queue->waitIdle();

		if (device != nullptr)
			device->waitIdle();

		if (drawFence != nullptr)
			device.waitForFence(drawFence);

		rendererPipeline.descriptorSets.reset(); // TODO Pipeline refactor
		GLFW::Deinit();
	}

	void Renderer::initialize()
	{
		createInstance();
		createDebugUtilsMessenger();
		createWindow();

		if (!createSurface())
			return;

		if (!createPhysicalDevice())
			return;

		queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);

		createDevice();
		createVma();
		createQueue();

		updateSwapChainSupportDetails();

		createSwapChain();
		createImageViews();

		createRenderPass();
		createFramebuffers();
		
		commandPool.create(device, queueFamilyIndex);
		imageAvailableSemaphore.create(device);
		renderingFinishedSemaphore.create(device);

		commandBuffer.allocateCommandBuffer(device, commandPool);

		drawFence.createSignaled(device);
		//device.waitForFence(drawFence);
	}

	const Context& Renderer::getContext() const
	{
		return context;
	}

	const Instance& Renderer::getInstance() const
	{
		return instance;
	}

	const DebugUtilsMessenger& Renderer::getDebugUtilsMessenger() const
	{
		return debugUtilsMessenger;
	}

	const Window& Renderer::getWindow() const
	{
		return window;
	}

	const Surface& Renderer::getSurface() const
	{
		return surface;
	}

	const PhysicalDevice& Renderer::getPhysicalDevice() const
	{
		return physicalDevice;
	}

	const Device& Renderer::getDevice() const
	{
		return device;
	}

	std::uint32_t Renderer::getQueueFamilyIndex() const
	{
		return queueFamilyIndex;
	}

	const Queue& Renderer::getQueue() const
	{
		return queue;
	}

	const SwapChainSupportDetails& Renderer::getSwapChainSupportDetails() const
	{
		return swapChainSupportDetails;
	}

	const SwapChain& Renderer::getSwapChain() const
	{
		return swapChain;
	}

	const std::vector<ImageView>& Renderer::getImageViews() const
	{
		return imageViews;
	}

	const vk::Extent2D& Renderer::getSwapExtent() const
	{
		return swapExtent;
	}

	const PipelineLayout& Renderer::getPipelineLayout() const
	{
		return rendererPipeline.pipelineLayout;
	}

	const RenderPass& Renderer::getRenderPass() const
	{
		return renderPass;
	}

	const std::vector<Framebuffer>& Renderer::getFramebuffers() const
	{
		return framebuffers;
	}

	const Pipeline& Renderer::getPipeline() const
	{
		return rendererPipeline.pipeline;
	}

	const Vma& Renderer::getVma() const
	{
		return vma;
	}

	const std::vector<ShaderModule>& Renderer::getShadersModules() const
	{
		return rendererPipeline.shadersModules;
	}

	const std::vector<vk::PipelineShaderStageCreateInfo>& Renderer::getShadersStages() const
	{
		return rendererPipeline.shadersStages;
	}

	const std::vector<DescriptorSetLayout>& Renderer::getDescriptorSetLayouts() const
	{
		return rendererPipeline.descriptorSetLayouts;
	}

	const DescriptorPool& Renderer::getDescriptorPool() const
	{
		return rendererPipeline.descriptorPool;
	}

	const std::optional<DescriptorSets>& Renderer::getDescriptorSets() const
	{
		return rendererPipeline.descriptorSets;
	}

	const CommandPool& Renderer::getCommandPool() const
	{
		return commandPool;
	}

	const CommandBuffer& Renderer::getCommandBuffer() const
	{
		return commandBuffer;
	}

	const std::vector<vk::WriteDescriptorSet>& Renderer::getWriteDescriptorSets() const
	{
		return rendererPipeline.writeDescriptorSets;
	}

	const std::vector<vk::DescriptorBufferInfo>& Renderer::getDescriptorBufferInfos() const
	{
		return rendererPipeline.descriptorBufferInfos;
	}

	const std::vector<vk::DescriptorImageInfo>& Renderer::getDescriptorImageInfos() const
	{
		return rendererPipeline.descriptorImageInfos;
	}

	void Renderer::createInstance()
	{
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		instance.populateRequiredExtensions();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);
	}

	void Renderer::createDebugUtilsMessenger()
	{
		bool canCreateDebugUtilsMessenger = Instance::GetEnabledValidationLayers();
		if (!canCreateDebugUtilsMessenger)
		{
			Logger->error("Can't create debug utils messenger");
			return;
		}

		debugUtilsMessenger.create(instance);
	}

	void Renderer::createWindow()
	{
		window.create();
		window.setRenderer(*this);
	}

	bool Renderer::createSurface()
	{
		bool createSurfaceResult = surface.create(instance, window);
		if (!createSurfaceResult)
		{
			Logger->error("Can't create surface");
		}

		return createSurfaceResult;
	}

	bool Renderer::createPhysicalDevice()
	{
		bool createPhysicalDeviceResult = physicalDevice.create(instance);
		if (!createPhysicalDeviceResult)
		{
			Logger->error("Can't create physical device");
		}

		return createPhysicalDeviceResult;
	}

	void Renderer::createDevice()
	{
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
		vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice, surface, deviceQueueCreateInfo);
		device.create(physicalDevice, deviceCreateInfo);
	}

	void Renderer::createQueue()
	{
		queue.create(device, queueFamilyIndex);
	}

	void Renderer::createSwapChain()
	{
		vk::SwapchainCreateInfoKHR creatInfo = swapChain.createCreateInfo(swapChainSupportDetails, surface, window);
		swapChain.create(device, creatInfo);
	}

	void Renderer::createImageViews()
	{
		std::vector<vk::Image> swapChainImages = swapChain.getImages();
		imageViews.reserve(swapChainImages.size());
		for (vk::Image swapChainImage : swapChainImages)
		{
			ImageView imageView;
			vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(swapChainImage, swapChainSupportDetails.pickFormat().format);
			imageView.create(device, imageViewCreateInfo);
			imageViews.push_back(std::move(imageView));
		}
	}

	void Renderer::createPipelineLayout()
	{
		rendererPipeline.pipelineLayout.setDescriptorSetLayouts(rendererPipeline.descriptorSetLayouts);

		rendererPipeline.pipelineLayout.setViewportSize(static_cast<float>(swapExtent.width), static_cast<float>(swapExtent.height));
		
		vk::Rect2D scissor;
		scissor.offset = vk::Offset2D{ 0, 0 };
		scissor.extent = swapExtent;
		rendererPipeline.pipelineLayout.setScissor(scissor);
		
		rendererPipeline.pipelineLayout.createColorBlendAttachmentState();
		
		vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo = rendererPipeline.pipelineLayout.createPipelineLayoutCreateInfo();
		rendererPipeline.pipelineLayout.create(device, pipelineLayoutCreateInfo);
	}

	void Renderer::createRenderPass()
	{
		renderPass.createAttachmentDescription(swapChainSupportDetails.pickFormat().format);
		renderPass.createAttachmentReference();
		renderPass.createSubpassDescription();
		renderPass.createSubpassDependency();

		renderPass.create(device);
	}

	void Renderer::createFramebuffers()
	{
		for (ImageView& imageView : imageViews)
		{
			Framebuffer framebuffer;
			framebuffer.create(device, imageView, renderPass, swapExtent);
			framebuffers.push_back(std::move(framebuffer));
		}
	}

	void Renderer::createVma()
	{
		VmaAllocatorCreateInfo allocatorCreateInfo = vma.createAllocatorCreateInfo(instance, device, physicalDevice);
		vma.create(allocatorCreateInfo);
	}

	void Renderer::createPipeline([[maybe_unused]] const DrawInfo& drawInfo)
	{
		createShadersModules(drawInfo.shaders);
		createShadersStages();
		createDescriptorSetLayouts(drawInfo.descriptors);
		createPipelineLayout();
		
		vk::GraphicsPipelineCreateInfo createInfo = rendererPipeline.pipeline.createGraphicsPipelineCreateInfo(rendererPipeline.pipelineLayout, renderPass, rendererPipeline.shadersStages);
		rendererPipeline.pipeline.create(device, createInfo);
	}

	void Renderer::createShadersModules(const std::span<Shader>& shaders)
	{
		rendererPipeline.shadersModules.clear();
		rendererPipeline.shadersModules.reserve(shaders.size());
		for (const Shader& shader : shaders)
		{
			ShaderModule& shaderModule = rendererPipeline.shadersModules.emplace_back();
			vk::ShaderModuleCreateInfo shaderModuleCreateInfo = shaderModule.createShaderModuleCreateInfo(shader);
			shaderModule.create(device, shader.getType(), shaderModuleCreateInfo);
		}
	}

	void Renderer::createShadersStages()
	{
		rendererPipeline.shadersStages.clear();
		rendererPipeline.shadersStages.reserve(rendererPipeline.shadersModules.size());
		for (ShaderModule& module : rendererPipeline.shadersModules)
		{
			rendererPipeline.shadersStages.push_back(rendererPipeline.pipelineLayout.createShaderStageCreateInfo(module));
		}
	}

	void Renderer::createDescriptorSetLayouts(const std::span<DrawInfo::Descriptor>& descriptors)
	{
		if (descriptors.empty())
			return;

		rendererPipeline.bindings.clear();
		rendererPipeline.bindings.reserve(descriptors.size());
		for (const DrawInfo::Descriptor& descriptor : descriptors)
		{
			vk::DescriptorSetLayoutBinding vkBinding = descriptor.toVkDescriptorSetLayoutBinding();
			rendererPipeline.bindings.push_back(vkBinding);
		}

		rendererPipeline.descriptorSetLayouts.clear();
		DescriptorSetLayout& descriptorSetLayout = rendererPipeline.descriptorSetLayouts.emplace_back();
		vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo = descriptorSetLayout.createDescriptorSetLayoutCreateInfo(rendererPipeline.bindings);
		descriptorSetLayout.create(device, descriptorSetLayoutCreateInfo);
	}

	void Renderer::prepareDraw(const DrawInfo& drawInfo)
	{
		// Should be in prepare draw
		device.waitForFence(drawFence);
		device.resetFence(drawFence);

		std::uint16_t nextImageTimeout = std::numeric_limits<std::uint16_t>::max();
		Fence acquireNextImageFence;
		nextImageToDraw = swapChain.acquireNextImage(nextImageTimeout, imageAvailableSemaphore, acquireNextImageFence);
		if (nextImageToDraw.first != vk::Result::eSuccess)
			Logger->error("Failed to acquire next image from swap chain");

		// Should be in separated function that will create pipeline from drawInfo
		//device.waitForFence(drawFence);

		rendererPipeline = RendererPipeline{};
		createPipeline(drawInfo);
		createDescriptorPool(drawInfo.descriptors);
		createDescriptorSets();
		createWriteDescriptorSets(drawInfo);

		if (!rendererPipeline.writeDescriptorSets.empty())
			device->updateDescriptorSets(rendererPipeline.writeDescriptorSets, {});
	}

	void Renderer::draw(const DrawInfo& drawInfo)
	{
		//device.waitForFence(drawFence);
		//device.resetFence(drawFence);

		//std::uint16_t nextImageTimeout = std::numeric_limits<std::uint16_t>::max();
		//Fence acquireNextImageFence;
		//nextImageToDraw = swapChain.acquireNextImage(nextImageTimeout, imageAvailableSemaphore, acquireNextImageFence);
		//if (nextImageToDraw.first != vk::Result::eSuccess)
		//	Logger->error("Failed to acquire next image from swap chain");

		commandBuffer.reset();
		commandBuffer.begin();

		vk::Rect2D renderArea;
		renderArea.offset = vk::Offset2D{ 0, 0 };
		renderArea.extent = swapExtent;

		commandBuffer.beginRenderPass(renderPass, framebuffers[nextImageToDraw.second], renderArea);
		commandBuffer.bindPipeline(rendererPipeline.pipeline);
		commandBuffer.bindVertexBuffer(0u, drawInfo.vertexBuffer, vk::DeviceSize{ 0 });

		vk::DeviceSize indexBufferOffset{ 0 };
		commandBuffer.bindIndexBuffer(drawInfo.indexBuffer, indexBufferOffset, vk::IndexType::eUint16);

		if (rendererPipeline.descriptorSets.has_value())
		{
			std::vector<vk::DescriptorSet> tempDescriptorSets;
			for (auto& set : *rendererPipeline.descriptorSets)
			{
				tempDescriptorSets.push_back(*set);
			}
			commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, rendererPipeline.pipelineLayout, 0, tempDescriptorSets, {});
		}

		commandBuffer->drawIndexed(static_cast<std::uint32_t>(drawInfo.indices.size()), 1, 0, 0, 0);
		commandBuffer.endRenderPass();
		commandBuffer.end();

		submit();
		present(nextImageToDraw.second);

		//Logger->info("Post draw");
	}

	void Renderer::submit()
	{
		submitWaitSemaphores = { &imageAvailableSemaphore };
		submitWaitPipelineStageFlags = vk::PipelineStageFlagBits::eColorAttachmentOutput;
		submitCommandBuffers = { &commandBuffer };
		submitSignalSemaphores = { &renderingFinishedSemaphore };

		submitInfo = queue.createSubmitInfo(
			submitWaitSemaphores,
			submitWaitPipelineStageFlags,
			submitCommandBuffers,
			submitSignalSemaphores);

		queue.submitWithFence(submitInfo, drawFence);
	}

	void Renderer::present(uint32_t& image)
	{
		vk::Result results[1];
		presentWaitSemaphores = { &renderingFinishedSemaphore };
		presentSwapChains = { &swapChain };
		presentInfo = queue.createPresentInfo(
			presentWaitSemaphores,
			presentSwapChains,
			image);
		presentInfo.pResults = results;

		queue.present(presentInfo);
		if (results[0] != vk::Result::eSuccess)
			Logger->error("present return non success vk::Result");
	}

	void Renderer::createDescriptorPool(const std::span<DrawInfo::Descriptor>& descriptors)
	{
		if (descriptors.empty())
			return;

		// Create descriptor pool sizes
		std::map<DescriptorType, std::uint32_t> descriptorTypes;
		for (const DrawInfo::Descriptor descriptor : descriptors)
		{
			std::uint32_t& poolSize = descriptorTypes[descriptor.descriptorType];
			poolSize++;
		}

		// Create vector of vk::DescriptorPoolSize
		std::vector<vk::DescriptorPoolSize> poolSizes;
		poolSizes.reserve(descriptorTypes.size());
		for (const std::pair<DescriptorType, std::uint32_t>& descriptorType : descriptorTypes)
		{
			vk::DescriptorPoolSize poolSize{
				DescriptorTypeToVkDescriptorType(descriptorType.first),
				descriptorType.second
			};

			poolSizes.emplace_back(poolSize);
		}

		rendererPipeline.descriptorSets.reset();
		rendererPipeline.descriptorPool.clear();
		rendererPipeline.descriptorPool = DescriptorPool{};
		vk::DescriptorPoolCreateInfo descriptorPoolCreateInfo = rendererPipeline.descriptorPool.createCreateInfo(poolSizes);
		rendererPipeline.descriptorPool.create(device, descriptorPoolCreateInfo);
	}

	void Renderer::createDescriptorSets()
	{
		if (rendererPipeline.descriptorPool == nullptr)
			return;

		const std::vector<vk::DescriptorSetLayout>& vkDescriptorSetLayouts = rendererPipeline.pipelineLayout.getVkDescriptorSetLayouts();
		vk::DescriptorSetAllocateInfo descriptorsSetsAllocateInfo = rendererPipeline.descriptorPool.createDescriptorSetAllocateInfo(vkDescriptorSetLayouts);
		rendererPipeline.descriptorSets = DescriptorSets{ device, descriptorsSetsAllocateInfo };
	}

	void Renderer::createWriteDescriptorSets(const DrawInfo& drawInfo)
	{
		rendererPipeline.writeDescriptorSets.clear();
		rendererPipeline.writeDescriptorSets.reserve(drawInfo.uniformBuffers.size() + drawInfo.images.size());
		createBufferWriteDescriptorSets(drawInfo.uniformBuffers);
		createImageWriteDescriptorSets(drawInfo.images);
	}

	void Renderer::createBufferWriteDescriptorSets(const std::span<UniformBuffer>& uniformBuffers)
	{
		rendererPipeline.descriptorBufferInfos.clear();
		for (const UniformBuffer& uniformBuffer : uniformBuffers)
		{
			vk::DescriptorBufferInfo& descriptorBufferInfo = rendererPipeline.descriptorBufferInfos.emplace_back(uniformBuffer.createDescriptorBufferInfo());
			vk::WriteDescriptorSet writeDescriptorSet = rendererPipeline.descriptorSets->createBufferWriteDescriptorSet(0u, descriptorBufferInfo);
			rendererPipeline.writeDescriptorSets.push_back(writeDescriptorSet);
		}
	}

	void Renderer::createImageWriteDescriptorSets(const std::span<DrawInfo::Image>& images)
	{
		rendererPipeline.descriptorImageInfos.clear();
		for (std::size_t index = 0u; index < images.size(); ++index)
		{
			const ImageBuffer& imageBuffer = images[index].buffer;
			const Sampler& sampler = images[index].sampler;
			const ImageView& imageView = images[index].view;
			vk::ImageLayout imageLayout = images[index].layout;
			vk::DescriptorImageInfo& descriptorImageInfo = rendererPipeline.descriptorImageInfos.emplace_back(imageBuffer.createDescriptorImageInfo(sampler, imageView, imageLayout));
			vk::WriteDescriptorSet writeDescriptorSet = rendererPipeline.descriptorSets->createImageWriteDescriptorSet(0u, descriptorImageInfo);
			rendererPipeline.writeDescriptorSets.push_back(writeDescriptorSet);
		}
	}

	void Renderer::informAboutWindowResize([[maybe_unused]] int width, [[maybe_unused]] int height)
	{
		while (window.isMinimized())
		{
			glfwWaitEvents();
		}

		device->waitIdle();

		framebuffers.clear();
		imageViews.clear();
		swapChain.clear();

		updateSwapChainSupportDetails();

		createSwapChain();
		createImageViews();
		createFramebuffers();
	}

	void Renderer::updateSwapChainSupportDetails()
	{
		swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);
		swapExtent = swapChainSupportDetails.pickSwapExtent(window);
	}

}