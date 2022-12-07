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

#include "Zinet/Core/ZtLogger.h"

//////////////////////////////////////////////////////////////////////////
// TODO
// Plan for the renderer
// Instance - done
// Messenger - done
// Window - done
// Surface - done
// PhysicalDevice - done
// Device - done
// Queue - done
// SwapChain - done
// ImageViews - done
// Framebuffers - done
// PipelineLayout - done
// RenderPass - done
// 
//// Must be passed from outside
// VertexShader // Only code & created inside
// FragmentShader // Only code & created inside
// ShaderStages /// Created inside
// 
// VertexBuffer // Data must be passed from outside
// IndexBuffer // Data must be passed from outside
// UniformBuffer // Data must be passed from outside
// ImageBuffer(Texture) // Data must be passed from outside
// 
//// Must be created before pipeline
// DescriptorPool
// DescriptorSets
// DescriptorSetLayouts
// updateDescriptorSets
// updateMVP
// 
// Pipeline // Must be created after shaders, buffers and descriptors
// CommandPool
// CommandBuffers
// Fences
// Semaphores
// 
//// Final functions
// drawFrame
// submit
// present
// 
// TODO: Recreate swap chain
// TODO: Batch rendering

namespace zt::gl
{

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

		const std::optional<PipelineLayout>& getPipelineLayout() const;

		const RenderPass& getRenderPass() const;

		const std::vector<Framebuffer>& getFramebuffers() const;

		const std::optional<Pipeline>& getPipeline() const;

		const Vma& getVma() const;

		const std::vector<ShaderModule>& getShadersModules() const;

		const std::vector<vk::PipelineShaderStageCreateInfo>& getShadersStages() const;

		const std::vector<DescriptorSetLayout>& getDescriptorSetLayouts() const;

		const std::optional<DescriptorPool>& getDescriptorPool() const;

		const std::optional<DescriptorSets>& getDescriptorSets() const;

		void prepareDraw(const DrawInfo& drawInfo);

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

		void createPipeline(const DrawInfo& drawInfo);
		void createShadersModules(const std::span<Shader>& shaders);
		void createShadersStages();
		void createDescriptorSetLayouts(const std::span<DrawInfo::Descriptor>& descriptors);


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

		std::vector<ShaderModule> shadersModules;
		std::vector<vk::PipelineShaderStageCreateInfo> shadersStages;
		std::vector<vk::DescriptorSetLayoutBinding> bindings;
		std::vector<DescriptorSetLayout> descriptorSetLayouts;
		std::optional<DescriptorSets> descriptorSets;
		std::optional<DescriptorPool> descriptorPool;
		std::optional<PipelineLayout> pipelineLayout;
		std::optional<Pipeline> pipeline;
	};

}