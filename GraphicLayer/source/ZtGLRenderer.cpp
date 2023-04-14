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

		if (drawFence != nullptr && drawFence.getStatus() != vk::Result::eNotReady)
			device.waitForFence(drawFence);

		//rendererPipeline = RendererPipeline{};
		rendererPipelines.clear();
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
		return rendererPipeline.getPipelineLayout();
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
		return rendererPipeline.getPipeline();
	}

	const Vma& Renderer::getVma() const
	{
		return vma;
	}

	const std::vector<ShaderModule>& Renderer::getShadersModules() const
	{
		return rendererPipeline.getShadersModules();
	}

	const std::vector<vk::PipelineShaderStageCreateInfo>& Renderer::getShadersStages() const
	{
		return rendererPipeline.getShadersStages();
	}

	const std::vector<DescriptorSetLayout>& Renderer::getDescriptorSetLayouts() const
	{
		return rendererPipeline.getDescriptorSetLayouts();
	}

	const DescriptorPool& Renderer::getDescriptorPool() const
	{
		return rendererPipeline.getDescriptorPool();
	}

	const std::optional<DescriptorSets>& Renderer::getDescriptorSets() const
	{
		return rendererPipeline.getDescriptorSets();
	}

	const CommandPool& Renderer::getCommandPool() const
	{
		return commandPool;
	}

	const std::vector<vk::WriteDescriptorSet>& Renderer::getWriteDescriptorSets() const
	{
		return rendererPipeline.getWriteDescriptorSets();
	}

	const std::vector<vk::DescriptorBufferInfo>& Renderer::getDescriptorBufferInfos() const
	{
		return rendererPipeline.getDescriptorBufferInfos();
	}

	const std::vector<vk::DescriptorImageInfo>& Renderer::getDescriptorImageInfos() const
	{
		return rendererPipeline.getDescriptorImageInfos();
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

	void Renderer::preDraw()
	{
		device.waitForFence(drawFence);
		device.resetFence(drawFence);

		std::uint16_t nextImageTimeout = std::numeric_limits<std::uint16_t>::max();
		Fence acquireNextImageFence;
		nextImageToDraw = swapChain.acquireNextImage(nextImageTimeout, imageAvailableSemaphore, acquireNextImageFence);
		if (nextImageToDraw.first != vk::Result::eSuccess)
			Logger->error("Failed to acquire next image from swap chain");

		rendererPipelines.clear();
		//commandBuffers.clear();
	}

	void Renderer::draw(const DrawInfo& drawInfo)
	{
		createRendererPipeline(drawInfo);

		commandBuffer.allocateCommandBuffer(device, commandPool);
		commandBuffer.reset();
		commandBuffer.begin();

		vk::Rect2D renderArea;
		renderArea.offset = vk::Offset2D{ 0, 0 };
		renderArea.extent = swapExtent;

		vk::ClearValue clearColor = vk::ClearColorValue{ std::array<float, 4>{ 0.5f, 0.5f, 0.5f, 1.f } };
		commandBuffer.beginRenderPass(renderPass, framebuffers[nextImageToDraw.second], renderArea, clearColor);
		commandBuffer.bindPipeline(rendererPipelines.back().getPipeline());
		commandBuffer.bindVertexBuffer(0u, drawInfo.vertexBuffer, vk::DeviceSize{ 0 });

		vk::DeviceSize indexBufferOffset{ 0 };
		commandBuffer.bindIndexBuffer(drawInfo.indexBuffer, indexBufferOffset, vk::IndexType::eUint16);

		if (rendererPipelines.back().getDescriptorSets().has_value())
		{
			std::vector<vk::DescriptorSet> tempDescriptorSets;
			for (auto& set : *rendererPipelines.back().getDescriptorSets())
			{
				tempDescriptorSets.push_back(*set);
			}
			commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, rendererPipelines.back().getPipelineLayout(), 0, tempDescriptorSets, {});
		}

		commandBuffer->drawIndexed(static_cast<std::uint32_t>(drawInfo.indices.size()), 1, 0, 0, 0);
		commandBuffer.endRenderPass();
		commandBuffer.end();
	}

	void Renderer::postDraw()
	{
		submit();
		present(nextImageToDraw.second);
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

	void Renderer::createRendererPipeline(const DrawInfo& drawInfo)
	{
		//rendererPipeline = RendererPipeline{};
		RendererPipeline& newRendererPipeline = rendererPipelines.emplace_back();
		RendererPipeline::CreateInfo rendererPipelineCreateInfo
		{
			.drawInfo = drawInfo,
			.device = device,
			.renderPass = renderPass,
			.swapExtent = swapExtent
		};
		newRendererPipeline.create(rendererPipelineCreateInfo);

		newRendererPipeline.updateDescriptorSets(device);
	}

}