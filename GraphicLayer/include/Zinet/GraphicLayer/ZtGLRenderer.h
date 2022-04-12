#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLDebugUtilsMessenger.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLSwapChain.h"
#include "Zinet/GraphicLayer/ZtGLImageView.h"
#include "Zinet/GraphicLayer/ZtGLShader.h"
#include "Zinet/GraphicLayer/ZtGLShaderModule.h"
#include "Zinet/GraphicLayer/ZtGLPipelineLayout.h"
#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLPipeline.h"
#include "Zinet/GraphicLayer/ZtGLFramebuffer.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLCommandPool.h"
#include "Zinet/GraphicLayer/ZtGLQueue.h"
#include "Zinet/GraphicLayer/ZtGLSemaphore.h"
#include "Zinet/GraphicLayer/ZtGLFence.h"

#include "Zinet/Core/ZtLogger.h"

#include <filesystem>

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Renderer
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Renderer");

	public:

		Renderer() = default;
		Renderer(const Renderer& other) = default;
		Renderer(Renderer&& other) = default;

		Renderer& operator = (const Renderer& other) = default;
		Renderer& operator = (Renderer&& other) = default;

		~Renderer() noexcept;

		void prepare();

		void run();

		std::filesystem::path contentPath;

	protected:

		void prepareSwapChain();
		void prepareShaders();

		void drawFrame();

		void submit();
		void present(uint32_t image);

		Instance instance;

		Device device;

		Surface surface;

		SwapChain swapChain;
		SwapChainSupportDetails swapChainSupportDetails;
		vk::Extent2D swapExtent;

		std::vector<vk::Image> swapChainImages;

		std::vector<ImageView> imageViews;

		std::vector<Framebuffer> framebuffers;

		Queue queue;

		uint32_t queueFamilyIndex{};

		Window window;

		PhysicalDevice physicalDevice;

		DebugUtilsMessenger debugUtilsMessenger;

		Context context;

		Shader vertexShader;
		Shader fragmentShader;

		ShaderModule vertexShaderModule;
		ShaderModule fragmentShaderModule;

		std::vector<vk::PipelineShaderStageCreateInfo> shaderStages;

		PipelineLayout pipelineLayout;

		RenderPass renderPass;

		Pipeline pipeline;

		CommandPool commandPool;
		CommandBuffer commandBuffer;

		Fence drawFence;
		//Fence acquireNextImageFence;

		Semaphore imageAvailableSemaphore;
		Semaphore renderFinishedSemaphore;
	};

}