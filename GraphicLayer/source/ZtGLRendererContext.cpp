#include "Zinet/GraphicLayer/ZtGLRendererContext.h"

#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLDrawableObject.h"
#include "Zinet/GraphicLayer/ZtGLMVP.h"

#include <map>

namespace zt::gl
{

	RendererContext::RendererContext()
		: queueFamilyIndex{ std::numeric_limits<uint32_t>::max() }
	{

	}

	RendererContext::~RendererContext() noexcept
	{
		if (queue != nullptr)
			queue->waitIdle();

		if (device != nullptr)
			device->waitIdle();
	}

	void RendererContext::initialize()
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

		createDepthBuffer();
		createImageViews();
		createRenderPass();
		createFramebuffers();
		
		commandPool.create(device, queueFamilyIndex);
	}

	void RendererContext::createInstance()
	{
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		instance.populateRequiredExtensions();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);
	}

	void RendererContext::createDebugUtilsMessenger()
	{
		bool canCreateDebugUtilsMessenger = Instance::GetEnabledValidationLayers();
		if (!canCreateDebugUtilsMessenger)
		{
			Logger->error("Can't create debug utils messenger");
			return;
		}

		debugUtilsMessenger.create(instance);
	}

	void RendererContext::createWindow()
	{
		window.create();
	}

	bool RendererContext::createSurface()
	{
		bool createSurfaceResult = surface.create(instance, window);
		if (!createSurfaceResult)
		{
			Logger->error("Can't create surface");
		}

		return createSurfaceResult;
	}

	bool RendererContext::createPhysicalDevice()
	{
		bool createPhysicalDeviceResult = physicalDevice.create(instance);
		if (!createPhysicalDeviceResult)
		{
			Logger->error("Can't create physical device");
		}

		return createPhysicalDeviceResult;
	}

	void RendererContext::createDevice()
	{
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
		vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice, surface, deviceQueueCreateInfo);
		device.create(physicalDevice, deviceCreateInfo);
	}

	void RendererContext::createQueue()
	{
		queue.create(device, queueFamilyIndex);
	}

	void RendererContext::createSwapChain()
	{
		vk::SwapchainCreateInfoKHR creatInfo = swapChain.createCreateInfo(swapChainSupportDetails, surface, window);
		swapChain.create(device, creatInfo);
	}

	void RendererContext::createImageViews()
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

	void RendererContext::createDepthBuffer()
	{
		bool foundFormat = depthBuffer.findDepthFormat(physicalDevice, depthBufferFormat);
		if (!foundFormat)
		{
			Logger->critical("findDepthFormat return false - can't create depth buffer");
			return;
		}

		depthBuffer.create(*this, depthBufferFormat);
	}

	void RendererContext::createRenderPass()
	{
		renderPass.createAttachmentDescription(swapChainSupportDetails.pickFormat().format);
		renderPass.createAttachmentReference();
		renderPass.createDepthAttachmentDescription(depthBufferFormat);
		renderPass.createDepthAttachmentReference();
		renderPass.createSubpassDescription();
		renderPass.createSubpassDependency();

		renderPass.create(device);
	}

	void RendererContext::createFramebuffers()
	{
		for (ImageView& imageView : imageViews)
		{
			std::array<vk::ImageView, 2u> attachments{ imageView.getVk(), depthBuffer.getImageView().getVk() };

			Framebuffer framebuffer;
			vk::FramebufferCreateInfo framebufferCreateInfo = framebuffer.createCreateInfo(imageView, renderPass, swapExtent);
			framebufferCreateInfo.attachmentCount = static_cast<std::uint32_t>(attachments.size());
			framebufferCreateInfo.pAttachments = attachments.data();

			framebuffer.create(device, framebufferCreateInfo);
			framebuffers.push_back(std::move(framebuffer));
		}
	}

	void RendererContext::createVma()
	{
		VmaAllocatorCreateInfo allocatorCreateInfo = vma.createAllocatorCreateInfo(instance, device, physicalDevice);
		vma.create(allocatorCreateInfo);
	}

	void RendererContext::informAboutWindowResize([[maybe_unused]] int width, [[maybe_unused]] int height)
	{
		framebuffers.clear();
		imageViews.clear();
		swapChain.clear();

		updateSwapChainSupportDetails();

		createSwapChain();
		createImageViews();
		createFramebuffers();
	}

	void RendererContext::updateSwapChainSupportDetails()
	{
		swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);
		swapExtent = swapChainSupportDetails.pickSwapExtent(window);
	}

	void RendererContext::submitCommandsWaitIdle(SubmitCommandsWaitIdleFunction function)
	{
		CommandBuffer commandBuffer;
		commandBuffer.allocateCommandBuffer(device, commandPool);

		queue.submitWaitIdle(commandBuffer, function);
	}

}