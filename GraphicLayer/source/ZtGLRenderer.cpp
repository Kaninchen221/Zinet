#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"

namespace zt::gl
{

	Renderer::Renderer()
		: queueFamilyIndex{ std::numeric_limits<uint32_t>::max() }
	{
		GLFW::Init();
	}

	Renderer::~Renderer() noexcept
	{
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

		createPipelineLayout();
		createRenderPass();
		createFramebuffers();

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
		return pipelineLayout;
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
		return pipeline;
	}

	const Vma& Renderer::getVma() const
	{
		return vma;
	}

	void Renderer::createInstance()
	{
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		instance.getRequiredExtensions();
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
		pipelineLayout.setViewportSize(swapExtent.width, swapExtent.height);

		vk::Rect2D scissor;
		scissor.offset = vk::Offset2D{ 0, 0 };
		scissor.extent = swapExtent;
		pipelineLayout.setScissor(scissor);

		pipelineLayout.createColorBlendAttachmentState();

		vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo = pipelineLayout.createPipelineLayoutCreateInfo();
		pipelineLayout.create(device, pipelineLayoutCreateInfo);
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
		VmaAllocatorCreateInfo allocatorCreateInfo = vma.createAllocatorCreateInfo(*this);
		vma.create(allocatorCreateInfo);
	}

}