#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"

#include <map>

namespace zt::gl
{

	Renderer::Renderer()
		: queueFamilyIndex{ std::numeric_limits<uint32_t>::max() },
		pipelineLayout{ std::make_unique<PipelineLayout>() },
		pipeline{ std::make_unique<Pipeline>() },
		descriptorPool{ std::in_place_t{} }
	{
		GLFW::Init();
	}

	Renderer::~Renderer() noexcept
	{
		// TODO Fix errors when we close window

		if (queue != nullptr)
			queue->waitIdle();

		if (device != nullptr)
			device->waitIdle();

		if (drawFence != nullptr)
			device.waitForFence(drawFence);

		descriptorSets.reset();
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

		swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);
		
		createSwapChain();
		createImageViews();

		swapExtent = swapChainSupportDetails.pickSwapExtent(window);

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
		return *pipelineLayout;
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
		return *pipeline;
	}

	const Vma& Renderer::getVma() const
	{
		return vma;
	}

	const std::vector<ShaderModule>& Renderer::getShadersModules() const
	{
		return shadersModules;
	}

	const std::vector<vk::PipelineShaderStageCreateInfo>& Renderer::getShadersStages() const
	{
		return shadersStages;
	}

	const std::vector<DescriptorSetLayout>& Renderer::getDescriptorSetLayouts() const
	{
		return descriptorSetLayouts;
	}

	const DescriptorPool& Renderer::getDescriptorPool() const
	{
		return *descriptorPool;
	}

	const std::optional<DescriptorSets>& Renderer::getDescriptorSets() const
	{
		return descriptorSets;
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
		return writeDescriptorSets;
	}

	const std::vector<vk::DescriptorBufferInfo>& Renderer::getDescriptorBufferInfos() const
	{
		return descriptorBufferInfos;
	}

	const std::vector<vk::DescriptorImageInfo>& Renderer::getDescriptorImageInfos() const
	{
		return descriptorImageInfos;
	}

	void Renderer::prepareDraw(const DrawInfo& drawInfo)
	{
		device.waitForFence(drawFence);

		createPipeline(drawInfo);
		createDescriptorPool(drawInfo.descriptors);
		createDescriptorSets();
		createWriteDescriptorSets(drawInfo);

		if (!writeDescriptorSets.empty())
			device->updateDescriptorSets(writeDescriptorSets, {});
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
		pipelineLayout->setDescriptorSetLayouts(descriptorSetLayouts);

		pipelineLayout->setViewportSize(static_cast<float>(swapExtent.width), static_cast<float>(swapExtent.height));
		
		vk::Rect2D scissor;
		scissor.offset = vk::Offset2D{ 0, 0 };
		scissor.extent = swapExtent;
		pipelineLayout->setScissor(scissor);
		
		pipelineLayout->createColorBlendAttachmentState();
		
		vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo = pipelineLayout->createPipelineLayoutCreateInfo();
		pipelineLayout->create(device, pipelineLayoutCreateInfo);
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
		pipelineLayout.reset();
		pipelineLayout = std::make_unique<PipelineLayout>();

		pipeline.reset();
		pipeline = std::make_unique<Pipeline>();

		createShadersModules(drawInfo.shaders);
		createShadersStages();
		createDescriptorSetLayouts(drawInfo.descriptors);
		createPipelineLayout();
		
		vk::GraphicsPipelineCreateInfo createInfo = pipeline->createGraphicsPipelineCreateInfo(*pipelineLayout, renderPass, shadersStages);
		pipeline->create(device, createInfo);
	}

	void Renderer::createShadersModules(const std::span<Shader>& shaders)
	{
		shadersModules.clear();
		shadersModules.reserve(shaders.size());
		for (const Shader& shader : shaders)
		{
			ShaderModule& shaderModule = shadersModules.emplace_back();
			vk::ShaderModuleCreateInfo shaderModuleCreateInfo = shaderModule.createShaderModuleCreateInfo(shader);
			shaderModule.create(device, shader.getType(), shaderModuleCreateInfo);
		}
	}

	void Renderer::createShadersStages()
	{
		shadersStages.clear();
		shadersStages.reserve(shadersModules.size());
		for (ShaderModule& module : shadersModules)
		{
			shadersStages.push_back(pipelineLayout->createShaderStageCreateInfo(module));
		}
	}

	void Renderer::createDescriptorSetLayouts(const std::span<DrawInfo::Descriptor>& descriptors)
	{
		if (descriptors.empty())
			return;

		bindings.clear();
		bindings.reserve(descriptors.size());
		for (const DrawInfo::Descriptor& descriptor : descriptors)
		{
			vk::DescriptorSetLayoutBinding vkBinding = descriptor.toVkDescriptorSetLayoutBinding();
			bindings.push_back(vkBinding);
		}

		descriptorSetLayouts.clear();
		DescriptorSetLayout& descriptorSetLayout = descriptorSetLayouts.emplace_back();
		vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo = descriptorSetLayout.createDescriptorSetLayoutCreateInfo(bindings);
		descriptorSetLayout.create(device, descriptorSetLayoutCreateInfo);
	}

	void Renderer::draw(const DrawInfo& drawInfo)
	{
		device.waitForFence(drawFence);
		device.resetFence(drawFence);

		std::uint16_t nextImageTimeout = std::numeric_limits<std::uint16_t>::max();
		Fence acquireNextImageFence;
		nextImageToDraw = swapChain.acquireNextImage(nextImageTimeout, imageAvailableSemaphore, acquireNextImageFence);
		if (nextImageToDraw.first != vk::Result::eSuccess)
			Logger->error("Failed to acquire next image from swap chain");

		commandBuffer.reset();
		commandBuffer.begin();

		vk::Rect2D renderArea;
		renderArea.offset = vk::Offset2D{ 0, 0 };
		renderArea.extent = swapExtent;

		commandBuffer.beginRenderPass(renderPass, framebuffers[nextImageToDraw.second], renderArea);
		commandBuffer.bindPipeline(*pipeline);
		commandBuffer.bindVertexBuffer(0u, drawInfo.vertexBuffer, vk::DeviceSize{ 0 });

		vk::DeviceSize indexBufferOffset{ 0 };
		commandBuffer.bindIndexBuffer(drawInfo.indexBuffer, indexBufferOffset, vk::IndexType::eUint16);

		if (descriptorSets.has_value())
		{
			std::vector<vk::DescriptorSet> tempDescriptorSets;
			for (auto& set : *descriptorSets)
			{
				tempDescriptorSets.push_back(*set);
			}
			commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, *pipelineLayout, 0, tempDescriptorSets, {});
		}

		commandBuffer->drawIndexed(static_cast<std::uint32_t>(drawInfo.indices.size()), 1, 0, 0, 0);
		commandBuffer.endRenderPass();
		commandBuffer.end();

		submit();
		present(nextImageToDraw.second);

		//Logger->info("Post draw");
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

		descriptorSets.reset();
		descriptorPool.reset();
		descriptorPool = DescriptorPool{};
		vk::DescriptorPoolCreateInfo descriptorPoolCreateInfo = descriptorPool->createCreateInfo(poolSizes);
		descriptorPool->create(device, descriptorPoolCreateInfo);
	}

	void Renderer::createDescriptorSets()
	{
		if (descriptorPool == nullptr)
			return;

		const std::vector<vk::DescriptorSetLayout>& vkDescriptorSetLayouts = pipelineLayout->getVkDescriptorSetLayouts();
		vk::DescriptorSetAllocateInfo descriptorsSetsAllocateInfo = descriptorPool->createDescriptorSetAllocateInfo(vkDescriptorSetLayouts);
		descriptorSets = DescriptorSets{ device, descriptorsSetsAllocateInfo };
	}

	void Renderer::createWriteDescriptorSets(const DrawInfo& drawInfo)
	{
		writeDescriptorSets.clear();
		writeDescriptorSets.reserve(drawInfo.uniformBuffers.size() + drawInfo.images.size());
		createBufferWriteDescriptorSets(drawInfo.uniformBuffers);
		createImageWriteDescriptorSets(drawInfo.images);
	}

	void Renderer::createBufferWriteDescriptorSets(const std::span<UniformBuffer>& uniformBuffers)
	{
		descriptorBufferInfos.clear();
		for (const UniformBuffer& uniformBuffer : uniformBuffers)
		{
			vk::DescriptorBufferInfo& descriptorBufferInfo = descriptorBufferInfos.emplace_back(uniformBuffer.createDescriptorBufferInfo());
			vk::WriteDescriptorSet writeDescriptorSet = descriptorSets->createBufferWriteDescriptorSet(0u, descriptorBufferInfo);
			writeDescriptorSets.push_back(writeDescriptorSet);
		}
	}

	void Renderer::createImageWriteDescriptorSets(const std::span<DrawInfo::Image>& images)
	{
		descriptorImageInfos.clear();
		for (std::size_t index = 0u; index < images.size(); ++index)
		{
			const ImageBuffer& imageBuffer = images[index].buffer;
			const Sampler& sampler = images[index].sampler;
			const ImageView& imageView = images[index].view;
			vk::ImageLayout imageLayout = images[index].layout;
			vk::DescriptorImageInfo& descriptorImageInfo = descriptorImageInfos.emplace_back(imageBuffer.createDescriptorImageInfo(sampler, imageView, imageLayout));
			vk::WriteDescriptorSet writeDescriptorSet = descriptorSets->createImageWriteDescriptorSet(0u, descriptorImageInfo);
			writeDescriptorSets.push_back(writeDescriptorSet);
		}
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

}