#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLDebugUtilsMessenger.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLQueue.h"
#include "Zinet/GraphicLayer/ZtGLSwapChain.h"
#include "Zinet/GraphicLayer/ZtGLSwapChainSupportDetails.h"
#include "Zinet/GraphicLayer/ZtGLImageView.h"
#include "Zinet/GraphicLayer/ZtGLPipelineLayout.h"
#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLPipeline.h"
#include "Zinet/GraphicLayer/ZtGLFramebuffer.h"
#include "Zinet/GraphicLayer/ZtGLCommandPool.h"
#include "Zinet/GraphicLayer/ZtGLVma.h"
#include "Zinet/GraphicLayer/ZtGLShaderModule.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorPool.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorSets.h"
#include "Zinet/GraphicLayer/ZtGLDepthBuffer.h"

#include "Zinet/GraphicLayer/ZtGLDrawInfo.h"
#include "Zinet/GraphicLayer/ZtGLSemaphore.h"
#include "Zinet/GraphicLayer/ZtGLFence.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLRendererPipeline.h"
#include "Zinet/GraphicLayer/ZtGLRenderTarget.h"
#include "Zinet/GraphicLayer/ZtGLCamera.h"

#include "Zinet/Core/ZtLogger.h"

#include <plf_colony.h>
#include <memory>

namespace zt::gl
{
	class ZINET_GRAPHIC_LAYER_API RendererContext
	{

	protected:

		inline static ConsoleLogger Logger = ConsoleLogger::Create("RendererContext");

	public:

		RendererContext();
		RendererContext(const RendererContext& other) = default;
		RendererContext(RendererContext&& other) = default;

		RendererContext& operator = (const RendererContext& other) = default;
		RendererContext& operator = (RendererContext&& other) = default;

		~RendererContext() noexcept;

		void initialize();

		const Context& getContext() const { return context; }

		const Instance& getInstance() const { return instance; }
		Instance& getInstance() { return instance; }

		const DebugUtilsMessenger& getDebugUtilsMessenger() const { return debugUtilsMessenger; }
		DebugUtilsMessenger& getDebugUtilsMessenger() { return debugUtilsMessenger; }

		const Window& getWindow() const { return window; }
		Window& getWindow() { return window; }

		const Surface& getSurface() const { return surface; }
		Surface& getSurface() { return surface; }

		const PhysicalDevice& getPhysicalDevice() const { return physicalDevice; }
		PhysicalDevice& getPhysicalDevice() { return physicalDevice; }

		const Device& getDevice() const { return device; }
		Device& getDevice() { return device; }

		std::uint32_t getQueueFamilyIndex() const { return queueFamilyIndex; }

		const Queue& getQueue() const { return queue; }
		Queue& getQueue() { return queue; }

		const SwapChainSupportDetails& getSwapChainSupportDetails() const { return swapChainSupportDetails; }

		const SwapChain& getSwapChain() const { return swapChain; }
		SwapChain& getSwapChain() { return swapChain; }

		const std::vector<ImageView>& getImageViews() const { return imageViews; }
		std::vector<ImageView>& getImageViews() { return imageViews; }

		const vk::Extent2D& getSwapExtent() const { return swapExtent; }

		const DepthBuffer& getDepthBuffer() const { return depthBuffer; }
		DepthBuffer& getDepthBuffer() { return depthBuffer; }

		vk::Format getDepthBufferFormat() { return depthBufferFormat; }

		const RenderPass& getRenderPass() const { return renderPass; }
		RenderPass& getRenderPass() { return renderPass; }

		const std::vector<Framebuffer>& getFramebuffers() const { return framebuffers; }
		std::vector<Framebuffer>& getFramebuffers() { return framebuffers; }

		const Vma& getVma() const { return vma; }
		Vma& getVma() { return vma; }

		const CommandPool& getCommandPool() const { return commandPool; }
		CommandPool& getCommandPool() { return commandPool; }

		void informAboutWindowResize(int width, int height);

		typedef void (*SubmitCommandsWaitIdleFunction)(CommandBuffer& commandBuffer);
		void submitCommandsWaitIdle(SubmitCommandsWaitIdleFunction function);

	protected:

		void createInstance();
		void createDebugUtilsMessenger();
		void createWindow();
		bool createSurface();
		bool createPhysicalDevice();
		void createDevice();
		void createQueue();
		void createSwapChain();
		void createImageViews();
		void createDepthBuffer();
		void createRenderPass();
		void createFramebuffers();
		void createVma();

		void updateSwapChainSupportDetails();

		Context context;
		Instance instance;
		DebugUtilsMessenger debugUtilsMessenger;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		std::uint32_t queueFamilyIndex;
		Device device;
		Queue queue;
		SwapChainSupportDetails swapChainSupportDetails;
		SwapChain swapChain;
		std::vector<ImageView> imageViews;
		vk::Extent2D swapExtent;
		DepthBuffer depthBuffer;
		vk::Format depthBufferFormat{};
		RenderPass renderPass;
		std::vector<Framebuffer> framebuffers;
		Vma vma;
		CommandPool commandPool;
	};

}