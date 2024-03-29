#include "Zinet/GraphicLayer/ZtGLRendererContext.hpp"

#include "Zinet/GraphicLayer/ZtGLInstance.hpp"
#include "Zinet/GraphicLayer/ZtGLDrawableBase.hpp"
#include "Zinet/GraphicLayer/ZtGLMVP.hpp"

#include "Zinet/Window/ZtGLFW.hpp"

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

		commandPool.create(device, queueFamilyIndex);

		transferCommandBuffer.allocateCommandBuffer(device, commandPool);

		updateSwapChainSupportDetails();

		createSwapChain();

		createDepthStencilBuffer();
		createRenderPass();
		createRenderTargets();
	}

	void RendererContext::createInstance()
	{
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		instance.populateRequiredExtensions();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);

		if (!instance.isValid())
			Logger->error("Failed to create Instance");
	}

	void RendererContext::createDebugUtilsMessenger()
	{
		bool canCreateDebugUtilsMessenger = instance.getEnableValidationLayers();
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
		vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(instance, physicalDevice, surface, deviceQueueCreateInfo);
		device.create(physicalDevice, deviceCreateInfo);

		if (!device.isValid())
			Logger->error("Failed to create Device");
	}

	void RendererContext::createQueue()
	{
		queue.create(device, queueFamilyIndex);

		if (!queue.isValid())
			Logger->error("Failed to create Queue");
	}

	void RendererContext::createSwapChain()
	{
		vk::SwapchainCreateInfoKHR creatInfo = swapChain.createCreateInfo(swapChainSupportDetails, surface, window);
		swapChain.create(device, creatInfo);

		if (!swapChain.isValid())
			Logger->error("Failed to create SwapChain");
	}

	void RendererContext::createDepthStencilBuffer()
	{
		bool foundFormat = depthStencilBuffer.findDepthFormat(physicalDevice, depthStencilBufferFormat);
		if (!foundFormat)
		{
			Logger->critical("findDepthFormat return false - can't create depth buffer");
			return;
		}

		depthStencilBuffer.create(*this, depthStencilBufferFormat);

		if (!depthStencilBuffer.isValid())
			Logger->error("Failed to create DepthStencilBuffer");
	}

	void RendererContext::createRenderPass()
	{
		renderPass.createColorAttachmentDescription(swapChainSupportDetails.pickFormat().format);
		renderPass.createColorAttachmentReference();
		renderPass.createDepthAttachmentDescription(depthStencilBufferFormat);
		renderPass.createDepthAttachmentReference();
		//renderPass.createStencilAttachmentDescription(stencilBufferFormat);
		renderPass.createSubpassDescription();
		renderPass.createSubpassDependency();

		vk::RenderPassCreateInfo createInfo = renderPass.createRenderPassCreateInfo();
		renderPass.create(device, createInfo);

		if (!renderPass.isValid())
			Logger->error("Failed to create RenderPass");
	}

	void RendererContext::createRenderTargets()
	{
		std::vector<vk::Image> swapChainImages = swapChain.getImages();
		renderTargets.reserve(swapChainImages.size());
		for (vk::Image swapChainImage : swapChainImages)
		{
			RenderTargetDisplay& renderTarget = renderTargets.emplace_back();

			RenderTargetDisplay::CreateInfo renderTargetCreateInfo
			{
				.device = device,
				.vma = vma,
				.renderPass = renderPass,
				.width = swapExtent.width,
				.height = swapExtent.height,
				.format = swapFormat,
				.swapChainImage = swapChainImage,
				.depthStencilBufferImageView = depthStencilBuffer.getImageView().getVk()
			};
			renderTarget.create(renderTargetCreateInfo);
		}
	}

	void RendererContext::createVma()
	{
		VmaAllocatorCreateInfo allocatorCreateInfo = vma.createAllocatorCreateInfo(instance, device, physicalDevice);
		vma.create(allocatorCreateInfo);

		if (vma.getInternal() == nullptr)
			Logger->error("Failed to create VMA");
	}

	void RendererContext::informAboutWindowResize(const Vector2ui& size)
	{
		depthStencilBuffer.clear();
		renderTargets.clear();
		swapChain.clear();

		updateSwapChainSupportDetails();

		createSwapChain();
		createDepthStencilBuffer();
		createRenderTargets();
	}

	void RendererContext::updateSwapChainSupportDetails()
	{
		swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);
		swapExtent = swapChainSupportDetails.pickSwapExtent(window);
		swapFormat = swapChainSupportDetails.pickFormat().format;
	}

	void RendererContext::submitCommandsWaitIdle(SubmitCommandsWaitIdleFunction function)
	{
		if (!transferCommandBuffer.isValid())
			transferCommandBuffer.allocateCommandBuffer(device, commandPool);

		queue.submitWaitIdle(transferCommandBuffer, function);
	}

}