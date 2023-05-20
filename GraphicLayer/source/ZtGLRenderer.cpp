#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLDrawableObject.h"
#include "Zinet/GraphicLayer/ZtGLMVP.h"

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
		
		drawCommandBuffer.allocateCommandBuffer(device, commandPool);
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

	const RenderPass& Renderer::getRenderPass() const
	{
		return renderPass;
	}

	const std::vector<Framebuffer>& Renderer::getFramebuffers() const
	{
		return framebuffers;
	}

	const Vma& Renderer::getVma() const
	{
		return vma;
	}

	const CommandPool& Renderer::getCommandPool() const
	{
		return commandPool;
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
			vk::FramebufferCreateInfo framebufferCreateInfo = framebuffer.createCreateInfo(imageView, renderPass, swapExtent);
			framebuffer.create(device, framebufferCreateInfo);
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
		submitCommandBuffers.clear();

		drawCommandBuffer.reset();
		drawCommandBuffer.begin();

		vk::Rect2D renderArea;
		renderArea.offset = vk::Offset2D{ 0, 0 };
		renderArea.extent = swapExtent;
		vk::ClearValue clearColor = vk::ClearColorValue{ std::array<float, 4>{ 0.5f, 0.5f, 0.5f, 0.f } };
		CommandBuffer::BeginRenderPassInfo beginRenderPassInfo
		{
			.renderPass = renderPass,
			.framebuffer = framebuffers[nextImageToDraw.second],
			.renderArea = renderArea,
			.clearValue = clearColor
		};
		drawCommandBuffer.beginRenderPass(beginRenderPassInfo);
	}

	void Renderer::draw(DrawableObject& drawableObject, const Camera& camera)
	{
		const DrawInfo& drawInfo = drawableObject.getDrawInfo();
		createRendererPipeline(drawInfo);

		updateMVPUniformBuffer(drawableObject, camera);

		drawCommandBuffer.bindPipeline(rendererPipelines.back().getPipeline());
		drawCommandBuffer.bindVertexBuffer(0u, drawInfo.vertexBuffer, vk::DeviceSize{ 0 });

		vk::DeviceSize indexBufferOffset{ 0 };
		drawCommandBuffer.bindIndexBuffer(drawInfo.indexBuffer, indexBufferOffset, vk::IndexType::eUint16);

		if (rendererPipelines.back().getDescriptorSets().has_value())
		{
			drawCommandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, rendererPipelines.back().getPipelineLayout(), 0, rendererPipelines.back().getDescriptorSets().value(), {});
		}

		drawCommandBuffer->drawIndexed(static_cast<std::uint32_t>(drawInfo.indices.size()), 1, 0, 0, 0);
	}

	void Renderer::postDraw()
	{
		if (invalidCommandBuffer)
		{
			drawCommandBuffer.clear();
			drawCommandBuffer.allocateCommandBuffer(device, commandPool);
			invalidCommandBuffer = false;
			return;
		}

		drawCommandBuffer.endRenderPass();
		drawCommandBuffer.end();

		submit();
		present(nextImageToDraw.second);
	}

	void Renderer::submit()
	{
		submitCommandBuffers.push_back(*drawCommandBuffer.getInternal());

		submitWaitSemaphores = { &imageAvailableSemaphore };
		submitWaitPipelineStageFlags = vk::PipelineStageFlagBits::eColorAttachmentOutput;
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
		drawFence.clear();
		drawFence.createSignaled(device);

		imageAvailableSemaphore.clear();
		imageAvailableSemaphore.create(device);

		renderingFinishedSemaphore.clear();
		renderingFinishedSemaphore.create(device);

		framebuffers.clear();
		imageViews.clear();
		swapChain.clear();

		invalidCommandBuffer = true;

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
		RendererPipeline& newRendererPipeline = rendererPipelines.emplace_back();
		RendererPipeline::CreateInfo rendererPipelineCreateInfo
		{
			.drawInfo = drawInfo,
			.device = device,
			.renderPass = renderPass,
			.commandPool = commandPool,
			.swapExtent = swapExtent
		};
		newRendererPipeline.create(rendererPipelineCreateInfo);

		newRendererPipeline.updateDescriptorSets(device);
	}

	void Renderer::updateMVPUniformBuffer(DrawableObject& drawableObject, const Camera& camera)
	{
		UniformBuffer* MVPUniformBuffer = drawableObject.getMVPUniformBuffer();
		if (MVPUniformBuffer != nullptr)
		{
			MVP mvp;
			mvp.model = drawableObject.getDrawInfo().modelMatrix;
			mvp.view = camera.viewMatrix();
			mvp.proj = camera.projectionMatrix();
			MVPUniformBuffer->fillWithObject(mvp);
		}
	}

	void Renderer::submitCommandsWaitIdle(SubmitCommandsWaitIdleFunction function)
	{
		CommandBuffer commandBuffer;
		commandBuffer.allocateCommandBuffer(device, commandPool);

		queue.submitWaitIdle(commandBuffer, function);
	}

}