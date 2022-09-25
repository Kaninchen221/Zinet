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
#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLImageBuffer.h"
#include "Zinet/GraphicLayer/ZtGLSampler.h"

#include "Zinet/Core/ZtLogger.h"

#include <filesystem>
#include <optional>

#include "glm/glm.hpp"
#include "glm/trigonometric.hpp"
#include "glm/matrix.hpp"
#include "glm/gtx/transform.hpp"

namespace zt::gl::tests
{
	struct MVP
	{
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};

	class RendererBuilder
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("RendererBuilder");

	public:

		RendererBuilder();
		RendererBuilder(const RendererBuilder& other) = default;
		RendererBuilder(RendererBuilder&& other) = default;

		RendererBuilder& operator = (const RendererBuilder& other) = default;
		RendererBuilder& operator = (RendererBuilder&& other) = default;

		~RendererBuilder() noexcept;

		void createAll();

		void run();

	public:

		void createInstance();
		void createDebugUtilsMessenger();
		void createWindow();
		void createSurface();
		void createPhysicalDevice();
		void createDevice();
		void createQueue();
		void createSwapChain();
		void createImageViews();
		void createVertexShader();
		void createFragmentShader();
		void createShaderStages();
		void createPipelineLayout();
		void createRenderPass();
		void createPipeline();
		void createFramebuffers();
		void createCommandPool();
		void createCommandBuffer();
		void createFences();
		void createSemaphores();
		void createVertexBuffer();
		void createIndexBuffer();
		void createUniformBuffer();
		void createTexture();
		void createDescrptorPool();
		void createDescriptorSets();
		void createDescriptorSetLayouts();

		void updateDescriptorSets();

		void drawFrame();

		void submit();
		void present(uint32_t image);

		void updateMVP();

		std::filesystem::path contentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

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
		std::array<DescriptorSetLayout, 1> descriptorSetLayouts;

		std::optional<DescriptorSets> descriptorSets;

		std::array<vk::WriteDescriptorSet, 2> writeDescriptorSets;

		Image image;
		ImageBuffer imageBuffer;
		DeviceMemory imageDeviceMemory;
		ImageView imageView;
		Sampler sampler;
	};

}