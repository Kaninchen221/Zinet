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
	class DrawableObject;

	// TODO Instanced rendering/
	// TODO Fix memory leak: The problem is probably Pipeline, PipelineLayout or/and validation layers. We should compile Vulkan API/Validation layers by the hand
	// TODO Add RendererContext a structure that will hold mainly data
	// TODO Cleanup getters. They should be in .h or .cpp
	class ZINET_GRAPHIC_LAYER_API Renderer
	{

	protected:

		inline static ConsoleLogger Logger = ConsoleLogger::Create("Renderer");

	public:

		Renderer();
		Renderer(const Renderer& other) = default;
		Renderer(Renderer&& other) = default;

		Renderer& operator = (const Renderer& other) = default;
		Renderer& operator = (Renderer&& other) = default;

		~Renderer() noexcept;

		void initialize();

		const Context& getContext() const;

		const Instance& getInstance() const;
		Instance& getInstance() { return instance; }

		const DebugUtilsMessenger& getDebugUtilsMessenger() const;

		const Window& getWindow() const;
		Window& getWindow() { return window; }

		const Surface& getSurface() const;
		Surface& getSurface() { return surface; }

		const PhysicalDevice& getPhysicalDevice() const;
		PhysicalDevice& getPhysicalDevice() { return physicalDevice; }

		const Device& getDevice() const;
		Device& getDevice() { return device; }

		std::uint32_t getQueueFamilyIndex() const;

		const Queue& getQueue() const;
		Queue& getQueue() { return queue; }

		const SwapChainSupportDetails& getSwapChainSupportDetails() const;

		const SwapChain& getSwapChain() const;

		const std::vector<ImageView>& getImageViews() const;

		const vk::Extent2D& getSwapExtent() const;

		const RenderPass& getRenderPass() const;
		RenderPass& getRenderPass() { return renderPass; }

		const std::vector<Framebuffer>& getFramebuffers() const;

		const Vma& getVma() const;

		const CommandPool& getCommandPool() const;

		// TODO Refactor it. Remove it after imgui will be inside renderer.
		CommandBuffer& getCommandBuffer() { return commandBuffer; }

		void preDraw();

		void draw(DrawableObject& drawableObject, const Camera& camera);

		void postDraw();

		void informAboutWindowResize(int width, int height);

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
		void createPipelineLayout();
		void createRenderPass();
		void createFramebuffers();
		void createVma();

		void updateSwapChainSupportDetails();

		void submit();
		void present(uint32_t& image);

		void createRendererPipeline(const DrawInfo & drawInfo);

		void updateMVPUniformBuffer(DrawableObject& drawableObject, const Camera& camera);

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
		RenderPass renderPass;
		std::vector<Framebuffer> framebuffers;
		Vma vma;
		std::pair<vk::Result, uint32_t> nextImageToDraw;

		Semaphore imageAvailableSemaphore;
		Semaphore renderingFinishedSemaphore;
		Fence drawFence;
		CommandPool commandPool;

		std::vector<RendererPipeline> rendererPipelines;
		CommandBuffer commandBuffer; // TODO Rename it to drawCommandBuffer

		// Submit info
		std::array<Semaphore*, 1> submitWaitSemaphores;
		vk::PipelineStageFlags submitWaitPipelineStageFlags;
		std::vector<vk::CommandBuffer> submitCommandBuffers;
		std::array<Semaphore*, 1> submitSignalSemaphores;
		vk::SubmitInfo submitInfo;

		// Present info
		std::array<Semaphore*, 1> presentWaitSemaphores = { &renderingFinishedSemaphore };
		std::array<SwapChain*, 1> presentSwapChains = { &swapChain };
		vk::PresentInfoKHR presentInfo;

		bool invalidCommandBuffer = false;
	};

}