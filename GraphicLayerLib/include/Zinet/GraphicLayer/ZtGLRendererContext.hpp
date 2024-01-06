#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLContext.hpp"
#include "Zinet/GraphicLayer/ZtGLInstance.hpp"
#include "Zinet/GraphicLayer/ZtGLDebugUtilsMessenger.hpp"
#include "Zinet/GraphicLayer/ZtGLSurface.hpp"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLQueue.hpp"
#include "Zinet/GraphicLayer/ZtGLSwapChain.hpp"
#include "Zinet/GraphicLayer/ZtGLSwapChainSupportDetails.hpp"
#include "Zinet/GraphicLayer/ZtGLImageView.hpp"
#include "Zinet/GraphicLayer/ZtGLPipelineLayout.hpp"
#include "Zinet/GraphicLayer/ZtGLRenderPass.hpp"
#include "Zinet/GraphicLayer/ZtGLPipeline.hpp"
#include "Zinet/GraphicLayer/ZtGLFramebuffer.hpp"
#include "Zinet/GraphicLayer/ZtGLCommandPool.hpp"
#include "Zinet/GraphicLayer/ZtGLVma.hpp"
#include "Zinet/GraphicLayer/ZtGLShaderModule.hpp"
#include "Zinet/GraphicLayer/ZtGLDescriptorPool.hpp"
#include "Zinet/GraphicLayer/ZtGLDescriptorSets.hpp"
#include "Zinet/GraphicLayer/ZtGLDepthStencilBuffer.hpp"

#include "Zinet/GraphicLayer/ZtGLDrawInfo.hpp"
#include "Zinet/GraphicLayer/ZtGLSemaphore.hpp"
#include "Zinet/GraphicLayer/ZtGLFence.hpp"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.hpp"
#include "Zinet/GraphicLayer/ZtGLRendererPipeline.hpp"
#include "Zinet/GraphicLayer/ZtGLRenderTarget.hpp"
#include "Zinet/GraphicLayer/ZtGLCamera.hpp"
#include "Zinet/GraphicLayer/ZtGLSignalCommandBuffer.hpp"

#include "Zinet/Core/ZtLogger.hpp"

#include "Zinet/Window/ZtWindow.hpp"

#include <plf_colony.h>
#include <memory>

namespace zt::gl
{
	class ZINET_GRAPHIC_LAYER_API RendererContext
	{

	protected:

		inline static core::ConsoleLogger Logger = core::ConsoleLogger::Create("RendererContext");

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

		const wd::Window& getWindow() const { return window; }
		wd::Window& getWindow() { return window; }

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

		const vk::Extent2D& getSwapExtent() const { return swapExtent; }

		const DepthStencilBuffer& getDepthStencilBuffer() const { return depthStencilBuffer; }
		DepthStencilBuffer& getDepthStencilBuffer() { return depthStencilBuffer; }

		vk::Format getDepthStencilBufferFormat() { return depthStencilBufferFormat; }

		const RenderPass& getRenderPass() const { return renderPass; }
		RenderPass& getRenderPass() { return renderPass; }

		const std::vector<RenderTargetDisplay>& getRenderTargets() const { return renderTargets; }
		std::vector<RenderTargetDisplay>& getRenderTargets() { return renderTargets; }

		const Vma& getVma() const { return vma; }
		Vma& getVma() { return vma; }

		const CommandPool& getCommandPool() const { return commandPool; }
		CommandPool& getCommandPool() { return commandPool; }

		const SignalCommandBuffer& getTransferCommandBuffer() const { return transferCommandBuffer; }
		SignalCommandBuffer& getTransferCommandBuffer() { return transferCommandBuffer; }

		void informAboutWindowResize(const Vector2ui& size);

		typedef void (*SubmitCommandsWaitIdleFunction)(CommandBuffer& commandBuffer);
		void submitCommandsWaitIdle(SubmitCommandsWaitIdleFunction function);

	protected:

		void createInstance();
		void createDebugUtilsMessenger();
		void createWindow();
		bool createSurface();
		bool createPhysicalDevice();
		void createDevice();
		void createVma();
		void createQueue();
		void createSwapChain();
		void createDepthStencilBuffer();
		void createRenderPass();
		void createRenderTargets();

		void updateSwapChainSupportDetails();

		wd::GLFW glfw;
		Context context;
		Instance instance;
		DebugUtilsMessenger debugUtilsMessenger;
		wd::Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		std::uint32_t queueFamilyIndex;
		Device device;
		Vma vma;
		Queue queue;
		SwapChainSupportDetails swapChainSupportDetails;
		SwapChain swapChain;
		vk::Extent2D swapExtent;
		vk::Format swapFormat{};
		DepthStencilBuffer depthStencilBuffer;
		vk::Format depthStencilBufferFormat{};
		RenderPass renderPass;
		std::vector<RenderTargetDisplay> renderTargets;
		CommandPool commandPool;
		SignalCommandBuffer transferCommandBuffer;
	};

}