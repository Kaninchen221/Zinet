#pragma once

#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLCommandPool.h"
#include "Zinet/GraphicLayer/ZtGLFramebuffer.h"
#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLImageView.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLPipeline.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLPipelineLayout.h"
#include "Zinet/GraphicLayer/ZtGLShaderModule.h"
#include "Zinet/GraphicLayer/ZtGLShader.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLSwapChain.h"
#include "Zinet/GraphicLayer/ZtGLStagingBuffer.h"
#include "Zinet/GraphicLayer/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLQueue.h"

#include "gtest/gtest.h"

#include <vector>

namespace zt::gl::tests
{

	class CommandBufferTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		CommandPool commandPool;
		CommandBuffer commandBuffer;

		void SetUp() override
		{
			GLFW::InitGLFW();

			instance.createInstanceCreateInfo();
			instance.create(context);

			window.create();

			surface.create(instance, window);

			physicalDevice.create(instance);

			device.create(physicalDevice, surface);

			uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
			commandPool.create(device, queueFamilyIndex);

			commandBuffer.allocateCommandBuffer(device, commandPool);
		}

		void TearDown() override
		{
			GLFW::DeinitGLFW();
		}
	};

	TEST(CommandBuffer, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<CommandBuffer, VulkanObject<vk::raii::CommandBuffer>>);
	}

	TEST(CommandBuffer, CreateCommandBufferAllocateInfoTest)
	{
		CommandBuffer commandBuffer;
		CommandPool commandPool;
		vk::CommandBufferAllocateInfo allocateInfo = commandBuffer.createCommandBufferAllocateInfo(commandPool);

		ASSERT_NE(allocateInfo, vk::CommandBufferAllocateInfo{});
	}

	TEST(CommandBuffer, ArrowOperatorTest)
	{
		CommandBuffer commandBuffer;
		vk::raii::CommandBuffer* internal = commandBuffer.operator->();

		ASSERT_EQ(**internal, *vk::raii::CommandBuffer{ std::nullptr_t{} });
	}

	TEST_F(CommandBufferTests, AllocateCommandBufferTest)
	{
		ASSERT_NE(*commandBuffer.getInternal(), *vk::raii::CommandBuffer{ std::nullptr_t{} });
	}

	TEST_F(CommandBufferTests, BeginTest)
	{
		commandBuffer.begin();
	}

	TEST_F(CommandBufferTests, EndTest)
	{
		commandBuffer.begin();
		commandBuffer.end();
	}

	TEST_F(CommandBufferTests, RenderPassTest)
	{
		SwapChainSupportDetails swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);
		vk::Extent2D swapExtent = swapChainSupportDetails.pickSwapExtent(window);

		SwapChain swapChain;
		swapChain.create(device, swapChainSupportDetails, surface, window);

		ImageView imageView;
		std::vector<vk::Image> images = swapChain.getImages();
		vk::SurfaceFormatKHR surfaceFormat = swapChainSupportDetails.pickFormat();
		imageView.create(device, images[0], surfaceFormat.format);

		RenderPass renderPass;
		renderPass.createAttachmentDescription(surfaceFormat.format);
		renderPass.createAttachmentReference();
		renderPass.createSubpassDescription();
		renderPass.createSubpassDependency();
		renderPass.create(device);

		Framebuffer framebuffer;
		framebuffer.create(
			device,
			imageView,
			renderPass,
			swapExtent);

		vk::Rect2D renderArea;

		commandBuffer.begin();
		commandBuffer.beginRenderPass(renderPass, framebuffer, renderArea);
		commandBuffer.endRenderPass();
	}

	TEST_F(CommandBufferTests, PipelineTest)
	{
		RenderPass renderPass;
		renderPass.createAttachmentDescription(vk::Format::eR8G8Unorm);
		renderPass.createAttachmentReference();
		renderPass.createSubpassDescription();
		renderPass.createSubpassDependency();
		renderPass.create(device);

		PipelineLayout pipelineLayout;
		pipelineLayout.create(device);

		Shader vertexShader;
		vertexShader.setType(ShaderType::Vertex);
		vertexShader.loadFromFile(ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files/shaderStaticVertices.vert");
		vertexShader.compile();

		Shader fragmentShader;
		fragmentShader.setType(ShaderType::Fragment);
		fragmentShader.loadFromFile(ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files/shader.frag");
		fragmentShader.compile();

		ShaderModule vertexShaderModule;
		vertexShaderModule.create(device, vertexShader);

		ShaderModule fragmentShaderModule;
		fragmentShaderModule.create(device, fragmentShader);

		vk::PipelineShaderStageCreateInfo vertexShaderStage = pipelineLayout.createShaderStageCreateInfo(vertexShaderModule);
		vk::PipelineShaderStageCreateInfo fragmentShaderStage = pipelineLayout.createShaderStageCreateInfo(fragmentShaderModule);

		std::vector<vk::PipelineShaderStageCreateInfo> stages = { vertexShaderStage, fragmentShaderStage };

		Pipeline pipeline;
		vk::GraphicsPipelineCreateInfo createInfo = pipeline.createGraphicsPipelineCreateInfo(pipelineLayout, renderPass, stages);
		pipeline.create(device, createInfo);

		commandBuffer.begin();
		commandBuffer.bindPipeline(pipeline);
	}

	TEST_F(CommandBufferTests, Reset)
	{
		commandBuffer.reset();
	}

	TEST_F(CommandBufferTests, RecordCommandBuffer)
	{
		commandBuffer.reset();
	}

	TEST_F(CommandBufferTests, CopyBuffer)
	{
		Queue queue;
		uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
		queue.create(device, queueFamilyIndex);

		std::vector<Vertex> vertices{ {}, {} };

		// Staging Buffer
		StagingBuffer sourceBuffer;
		DeviceMemory sourceBufferDeviceMemory;

		sourceBuffer.setSize(sizeof(Vertex) * vertices.size());
		vk::BufferCreateInfo sourceBufferCreateInfo = sourceBuffer.createCreateInfo();
		sourceBuffer.create(device, sourceBufferCreateInfo);

		vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
		vk::MemoryPropertyFlags sourceBufferMemoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
		vk::MemoryAllocateInfo sourceBufferMemoryAllocateInfo = sourceBuffer.createMemoryAllocateInfo(physicalDeviceMemoryProperties, sourceBufferMemoryPropertyFlags);

		sourceBufferDeviceMemory.create(device, sourceBufferMemoryAllocateInfo);

		sourceBuffer.bindMemory(sourceBufferDeviceMemory);

		sourceBufferDeviceMemory.fillWithData(vertices);
		
		// Vertex Buffer 
		VertexBuffer destinationBuffer;
		DeviceMemory destinationBufferDeviceMemory;

		destinationBuffer.setSize(sizeof(Vertex) * vertices.size());
		vk::BufferCreateInfo destinationBufferCreateInfo = destinationBuffer.createCreateInfo();
		destinationBuffer.create(device, destinationBufferCreateInfo);

		vk::MemoryPropertyFlags destinationBufferMemoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eDeviceLocal;
		vk::MemoryAllocateInfo destinationBufferrMemoryAllocateInfo = destinationBuffer.createMemoryAllocateInfo(
																							physicalDeviceMemoryProperties, 
																							destinationBufferMemoryPropertyFlags);

		destinationBufferDeviceMemory.create(device, destinationBufferrMemoryAllocateInfo);
		destinationBuffer.bindMemory(destinationBufferDeviceMemory);

		vk::CommandBufferAllocateInfo allocateInfo = commandBuffer.createCommandBufferAllocateInfo(commandPool);
		commandBuffer.allocateCommandBuffer(device, commandPool);

		commandBuffer.copyBuffer(sourceBuffer, destinationBuffer);

		// TODO: Create own submit info
		vk::SubmitInfo submitInfo{};
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

		queue->submit(submitInfo);
		queue->waitIdle();

		std::pair<void*, std::uint64_t> data = destinationBufferDeviceMemory.getData(destinationBuffer.getSize());
		std::size_t expectedSize = sizeof(Vertex) * vertices.size();

		ASSERT_EQ(data.second, expectedSize);

		int result = std::memcmp(data.first, vertices.data(), expectedSize);

		ASSERT_EQ(result, 0);

		std::free(data.first);
	}
}
