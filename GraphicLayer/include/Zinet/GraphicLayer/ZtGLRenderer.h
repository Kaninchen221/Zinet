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

#include "Zinet/Core/ZtLogger.h"

#include <memory>

namespace zt::gl
{
	// TODO Draw multiple objects
	// TODO Batch renderer
	class ZINET_GRAPHIC_LAYER_API Renderer
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Renderer");

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

		const DebugUtilsMessenger& getDebugUtilsMessenger() const;

		const Window& getWindow() const;

		const Surface& getSurface() const;

		const PhysicalDevice& getPhysicalDevice() const;

		const Device& getDevice() const;

		std::uint32_t getQueueFamilyIndex() const;

		const Queue& getQueue() const;

		const SwapChainSupportDetails& getSwapChainSupportDetails() const;

		const SwapChain& getSwapChain() const;

		const std::vector<ImageView>& getImageViews() const;

		const vk::Extent2D& getSwapExtent() const;

		const PipelineLayout& getPipelineLayout() const;

		const RenderPass& getRenderPass() const;

		const std::vector<Framebuffer>& getFramebuffers() const;

		const Pipeline& getPipeline() const;

		const Vma& getVma() const;

		const std::vector<ShaderModule>& getShadersModules() const;

		const std::vector<vk::PipelineShaderStageCreateInfo>& getShadersStages() const;

		const std::vector<DescriptorSetLayout>& getDescriptorSetLayouts() const;

		const DescriptorPool& getDescriptorPool() const;

		const std::optional<DescriptorSets>& getDescriptorSets() const;

		const CommandPool& getCommandPool() const;

		const CommandBuffer& getCommandBuffer() const;

		const std::vector<vk::WriteDescriptorSet>& getWriteDescriptorSets() const;

		const std::vector<vk::DescriptorBufferInfo>& getDescriptorBufferInfos() const;

		const std::vector<vk::DescriptorImageInfo>& getDescriptorImageInfos() const;

		void prepareDraw(const DrawInfo& drawInfo);

		void draw(const DrawInfo& drawInfo);

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

		RendererPipeline rendererPipeline;

		Semaphore imageAvailableSemaphore;
		Semaphore renderingFinishedSemaphore;
		Fence drawFence;
		CommandPool commandPool;
		CommandBuffer commandBuffer;

		// Submit info
		std::array<Semaphore*, 1> submitWaitSemaphores;
		vk::PipelineStageFlags submitWaitPipelineStageFlags;
		std::array<CommandBuffer*, 1> submitCommandBuffers;
		std::array<Semaphore*, 1> submitSignalSemaphores;
		vk::SubmitInfo submitInfo;

		// Present info
		std::array<Semaphore*, 1> presentWaitSemaphores = { &renderingFinishedSemaphore };
		std::array<SwapChain*, 1> presentSwapChains = { &swapChain };
		vk::PresentInfoKHR presentInfo;

		void submit();
		void present(uint32_t& image);
	};

}