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
#include "Zinet/GraphicLayer/ZtGLSwapChain.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLStagingBuffer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLQueue.h"
#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLImageBuffer.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLVma.h"
#include "ZtGLRendererBuilder.h"

#include <gtest/gtest.h>

#include <vector>

namespace zt::gl::tests
{
	class CommandBufferSimpleTests : public ::testing::Test
	{
		static_assert(std::derived_from<CommandBuffer, VulkanObject<vk::raii::CommandBuffer>>);
	};

	TEST_F(CommandBufferSimpleTests, CreateCommandBufferAllocateInfoTest)
	{
		typedef vk::CommandBufferAllocateInfo(CommandBuffer::* ExpectedFunctionDeclaration)(const CommandPool&) const;
		using FunctionDeclaration = decltype(&CommandBuffer::createCommandBufferAllocateInfo);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		CommandBuffer commandBuffer;
		CommandPool commandPool;
		vk::CommandBufferAllocateInfo allocateInfo = commandBuffer.createCommandBufferAllocateInfo(commandPool);

		ASSERT_NE(allocateInfo, vk::CommandBufferAllocateInfo{});
	}

	TEST_F(CommandBufferSimpleTests, ArrowOperatorTest)
	{
		CommandBuffer commandBuffer;
		vk::raii::CommandBuffer* internal = commandBuffer.operator->();

		ASSERT_EQ(**internal, *vk::raii::CommandBuffer{ std::nullptr_t{} });
	}

	TEST_F(CommandBufferSimpleTests, IsCommandBufferInvalid)
	{
		CommandBuffer commandBuffer;
		bool isInvalid = commandBuffer.getIsCommandBufferInvalid();
		ASSERT_FALSE(isInvalid);

		commandBuffer.setIsCommandBufferInvalid(true);
		isInvalid = commandBuffer.getIsCommandBufferInvalid();
		ASSERT_TRUE(isInvalid);
	}

	TEST_F(CommandBufferSimpleTests, CopyBufferToImage)
	{
		Renderer renderer;
		renderer.initialize();
		RendererContext& rendererContext = renderer.getRendererContext();

		StagingBuffer stagingBuffer;

		BufferCreateInfo stagingBufferCreateInfo{ .device = rendererContext.getDevice(), .vma = rendererContext.getVma() };
		stagingBufferCreateInfo.vkBufferCreateInfo = stagingBuffer.createCreateInfo(8u);
		stagingBufferCreateInfo.allocationCreateInfo = stagingBuffer.createVmaAllocationCreateInfo(false, true);

		stagingBuffer.create(stagingBufferCreateInfo);

		std::uint32_t expectedWidth = 1u;
		std::uint32_t expectedHeight = 1u;

		Image image;
		Image::CreateInfo imageCreateInfo{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkImageCreateInfo = image.createCreateInfo(expectedWidth, expectedHeight),
			.allocationCreateInfo = image.createAllocationCreateInfo()
		};

		image.create(imageCreateInfo);

		vk::ImageLayout newLayout = vk::ImageLayout::eTransferDstOptimal;

		vk::BufferImageCopy imageRegion{};
		imageRegion.bufferOffset = 0;
		imageRegion.bufferRowLength = 0;
		imageRegion.bufferImageHeight = 0;

		imageRegion.imageSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
		imageRegion.imageSubresource.mipLevel = 0;
		imageRegion.imageSubresource.baseArrayLayer = 0;
		imageRegion.imageSubresource.layerCount = 1;

		imageRegion.imageOffset = vk::Offset3D{ 0, 0, 0 };
		imageRegion.imageExtent = vk::Extent3D{
			1, // width
			1, // height
			1
		};

		ImageBuffer imageBuffer;

		BufferCreateInfo imageBufferCreateInfo{ .device = rendererContext.getDevice(), .vma = rendererContext.getVma() };
		imageBufferCreateInfo.vkBufferCreateInfo = imageBuffer.createCreateInfo(1u);
		imageBufferCreateInfo.allocationCreateInfo = imageBuffer.createVmaAllocationCreateInfo(false, false);

		imageBuffer.create(imageBufferCreateInfo);

		uint32_t queueFamilyIndex = rendererContext.getPhysicalDevice().pickQueueFamilyIndex(rendererContext.getSurface());
		CommandPool commandPool;
		commandPool.create(rendererContext.getDevice(), queueFamilyIndex);

		CommandBuffer commandBuffer;
		commandBuffer.allocateCommandBuffer(rendererContext.getDevice(), commandPool);

		commandBuffer.begin();
		commandBuffer.copyBufferToImage(stagingBuffer, image, newLayout, imageRegion);
	}

	TEST_F(CommandBufferSimpleTests, BindVertexBuffer)
	{
		RendererBuilder rendererBuilder;
		rendererBuilder.createAll();

		VertexBuffer vertexBuffer;
		vk::BufferCreateInfo vkBufferCreateInfo = vertexBuffer.createCreateInfo(1u);
		vkBufferCreateInfo.usage = vk::BufferUsageFlagBits::eVertexBuffer;
		VmaAllocationCreateInfo allocationCreateInfo = vertexBuffer.createVmaAllocationCreateInfo(false, true);

		BufferCreateInfo bufferCreateInfo{ .device = rendererBuilder.device, .vma = rendererBuilder.vma };
		bufferCreateInfo.vkBufferCreateInfo = vkBufferCreateInfo;
		bufferCreateInfo.allocationCreateInfo = allocationCreateInfo;

		vertexBuffer.create(bufferCreateInfo);

		rendererBuilder.commandBuffer.begin();
		rendererBuilder.commandBuffer.bindVertexBuffer(0u, vertexBuffer, vk::DeviceSize{ 0 });
	}

	TEST_F(CommandBufferSimpleTests, BindIndexBuffer)
	{
		RendererBuilder rendererBuilder;
		rendererBuilder.createAll();

		IndexBuffer indexBuffer;
		vk::BufferCreateInfo vkBufferCreateInfo = indexBuffer.createCreateInfo(1u);
		vkBufferCreateInfo.usage = vk::BufferUsageFlagBits::eIndexBuffer;
		VmaAllocationCreateInfo allocationCreateInfo = indexBuffer.createVmaAllocationCreateInfo(false, true);

		BufferCreateInfo bufferCreateInfo{ .device = rendererBuilder.device, .vma = rendererBuilder.vma };
		bufferCreateInfo.vkBufferCreateInfo = vkBufferCreateInfo;
		bufferCreateInfo.allocationCreateInfo = allocationCreateInfo;

		indexBuffer.create(bufferCreateInfo);

		rendererBuilder.commandBuffer.begin();
		vk::DeviceSize offset = 0u;
		vk::IndexType indexType = vk::IndexType::eUint16;
		rendererBuilder.commandBuffer.bindIndexBuffer(indexBuffer, offset, indexType);
	}

	TEST_F(CommandBufferSimpleTests, BindDescriptorSets)
	{
		RendererBuilder rendererBuilder;
		rendererBuilder.createAll();

		vk::PipelineBindPoint bindPoint = vk::PipelineBindPoint::eGraphics;
		std::uint32_t firstSet = 0u;
		std::array<std::uint32_t, 0> dynamicOffsets;
		rendererBuilder.commandBuffer.begin();
		rendererBuilder.commandBuffer.bindDescriptorSets(bindPoint, rendererBuilder.pipelineLayout, firstSet, *rendererBuilder.descriptorSets, dynamicOffsets);
	}

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
			GLFW::Init();

			vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
			instance.populateRequiredExtensions();
			vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
			instance.create(context, instanceCreateInfo);
			window.create();
			surface.create(instance, window);
			physicalDevice.create(instance);

			vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
			vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice, surface, deviceQueueCreateInfo);
			device.create(physicalDevice, deviceCreateInfo);

			uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
			commandPool.create(device, queueFamilyIndex);

			commandBuffer.allocateCommandBuffer(device, commandPool);
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST_F(CommandBufferTests, AllocateCommandBufferTest)
	{
		typedef void(CommandBuffer::* ExpectedFunctionDeclaration)(const Device&, const CommandPool&);
		using FunctionDeclaration = decltype(&CommandBuffer::allocateCommandBuffer);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

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
		vk::SwapchainCreateInfoKHR creatInfo = swapChain.createCreateInfo(swapChainSupportDetails, surface, window);
		swapChain.create(device, creatInfo);

		ImageView imageView;
		std::vector<vk::Image> images = swapChain.getImages();
		vk::SurfaceFormatKHR surfaceFormat = swapChainSupportDetails.pickFormat();
		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(images[0], surfaceFormat.format);
		imageView.create(device, imageViewCreateInfo);

		RenderPass renderPass;
		renderPass.createAttachmentDescription(surfaceFormat.format);
		renderPass.createAttachmentReference();
		renderPass.createSubpassDescription();
		renderPass.createSubpassDependency();
		renderPass.create(device);

		Framebuffer framebuffer;
		vk::FramebufferCreateInfo framebufferCreateInfo = framebuffer.createCreateInfo(imageView, renderPass, swapExtent);
		framebuffer.create(device, framebufferCreateInfo);

		vk::Rect2D renderArea;
		vk::ClearValue clearValue;

		commandBuffer.begin();

		CommandBuffer::BeginRenderPassInfo beginRenderPassInfo
		{
			.renderPass = renderPass,
			.framebuffer = framebuffer,
			.renderArea = renderArea,
			.clearValue = clearValue
		};
		commandBuffer.beginRenderPass(beginRenderPassInfo);
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
		vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo = pipelineLayout.createPipelineLayoutCreateInfo();
		pipelineLayout.create(device, pipelineLayoutCreateInfo);

		Shader vertexShader;
		vertexShader.setType(ShaderType::Vertex);
		vertexShader.loadFromFile(ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files/shaderStaticVertices.vert");
		vertexShader.compile();

		Shader fragmentShader;
		fragmentShader.setType(ShaderType::Fragment);
		fragmentShader.loadFromFile(ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files/shaderStaticVertices.frag");
		fragmentShader.compile();

		ShaderModule vertexShaderModule;
		vk::ShaderModuleCreateInfo vertexShaderCreateInfo = vertexShaderModule.createShaderModuleCreateInfo(vertexShader);
		vertexShaderModule.create(device, ShaderType::Vertex, vertexShaderCreateInfo);

		ShaderModule fragmentShaderModule;
		vk::ShaderModuleCreateInfo fragmentShaderCreateInfo = fragmentShaderModule.createShaderModuleCreateInfo(fragmentShader);
		fragmentShaderModule.create(device, ShaderType::Fragment, fragmentShaderCreateInfo);

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

	TEST_F(CommandBufferSimpleTests, CreateImageMemoryBarrier)
	{
		CommandBuffer commandBuffer;
		vk::ImageLayout oldLayout = vk::ImageLayout::eUndefined;
		vk::ImageLayout newLayout = vk::ImageLayout::eTransferDstOptimal;
		Image image;
		vk::ImageMemoryBarrier barrier = commandBuffer.createImageMemoryBarrier(image, oldLayout, newLayout);

		ASSERT_EQ(barrier.oldLayout, oldLayout);
		ASSERT_EQ(barrier.newLayout, newLayout);
		ASSERT_EQ(barrier.srcQueueFamilyIndex, VK_QUEUE_FAMILY_IGNORED);  // TODO (Low) Fix it
		ASSERT_EQ(barrier.dstQueueFamilyIndex, VK_QUEUE_FAMILY_IGNORED);  // TODO (Low) Fix it
		ASSERT_EQ(barrier.image, *image.getInternal());
		ASSERT_EQ(barrier.subresourceRange.aspectMask, vk::ImageAspectFlagBits::eColor);
		ASSERT_EQ(barrier.subresourceRange.baseMipLevel, 0);
		ASSERT_EQ(barrier.subresourceRange.levelCount, 1);
		ASSERT_EQ(barrier.subresourceRange.baseArrayLayer, 0);
		ASSERT_EQ(barrier.subresourceRange.layerCount, 1);
		ASSERT_EQ(barrier.srcAccessMask, vk::AccessFlagBits{});
		ASSERT_EQ(barrier.dstAccessMask, vk::AccessFlagBits{});
	}
}
