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
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"
#include "Zinet/GraphicLayer/ZtGLIndexBuffer.h"
#include "Zinet/GraphicLayer/ZtGLUniformBuffer.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorPool.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorSetLayout.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorSets.h"

#include "Zinet/Core/ZtLogger.h"

#include <filesystem>

//#include "glm/mat4x4.hpp"
#include "glm/glm.hpp"
#include "glm/trigonometric.hpp"
#include "glm/matrix.hpp"
#include "glm/gtx/transform.hpp"

namespace zt::gl
{
	struct ZINET_GRAPHIC_LAYER_API MVP
	{
		glm::vec2 useless;
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};

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

		Context& getContext();
		Instance& getInstance();
		DebugUtilsMessenger& getDebugUtilsMessenger();
		Window& getWindow();
		Surface& getSurface();
		PhysicalDevice& getPhysicalDevice();
		Device& getDevice();
		Queue& getQueue();
		SwapChain& getSwapChain();
		PipelineLayout& getPipelineLayout();
		RenderPass& getRenderPass();
		Pipeline& getPipeline();
		std::vector<Framebuffer>& getFramebuffers();
		CommandPool& getCommandPool();
		CommandBuffer& getCommandBuffer();

		void prepare();

		void run();

		std::filesystem::path contentPath;

	protected:

		void prepareSwapChain();
		void prepareShaders();
		void prepareVertexBuffer();
		void prepareIndexBuffer();
		void prepareUniformBuffer();

		void drawFrame();

		void submit();
		void present(uint32_t image);

		void updateMVP();

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

		// TODO
		// Create something like draw(const RenderInfo& renderInfo)
		// RenderInfo.shaderStages
		// RenderInfo.vertices
		Shader vertexShader;
		Shader fragmentShader;

		ShaderModule vertexShaderModule;
		ShaderModule fragmentShaderModule;

		std::vector<vk::PipelineShaderStageCreateInfo> shaderStages;
		//

		PipelineLayout pipelineLayout;

		RenderPass renderPass;

		Pipeline pipeline;

		CommandPool commandPool;
		CommandBuffer commandBuffer;

		Fence drawFence;
		//Fence acquireNextImageFence;

		Semaphore imageAvailableSemaphore;
		Semaphore renderFinishedSemaphore;

		std::vector<Vertex> vertices;
		VertexBuffer vertexBuffer;
		DeviceMemory vertexBufferDeviceMemory;

		std::vector<std::uint16_t> indices;
		IndexBuffer indexBuffer;
		DeviceMemory indexBufferDeviceMemory;

		UniformBuffer uniformBuffer;
		DeviceMemory uniformBufferDeviceMemory;

		MVP mvp;

		DescriptorPool descriptorPool;

		std::optional<DescriptorSets> descriptorSets;
	};

}