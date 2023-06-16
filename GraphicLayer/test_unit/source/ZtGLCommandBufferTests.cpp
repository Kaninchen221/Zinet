#pragma once

#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLStagingBuffer.h"
#include "Zinet/GraphicLayer/ZtGLVma.h"
#include "ZtGLRendererBuilder.h"

#include <gtest/gtest.h>

#include <vector>

namespace zt::gl::tests
{
	class CommandBufferSimpleTests : public ::testing::Test
	{
		static_assert(std::derived_from<CommandBuffer, VulkanObject<vk::raii::CommandBuffer>>);

	protected:

		CommandBuffer commandBuffer;
	};

	TEST_F(CommandBufferSimpleTests, CreateCommandBufferAllocateInfoTest)
	{
		typedef vk::CommandBufferAllocateInfo(CommandBuffer::* ExpectedFunctionDeclaration)(const CommandPool&) const;
		using FunctionDeclaration = decltype(&CommandBuffer::createCommandBufferAllocateInfo);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		CommandPool commandPool;
		vk::CommandBufferAllocateInfo allocateInfo = commandBuffer.createCommandBufferAllocateInfo(commandPool);

		ASSERT_NE(allocateInfo, vk::CommandBufferAllocateInfo{});
	}

	TEST_F(CommandBufferSimpleTests, IsCommandBufferInvalid)
	{
		bool isInvalid = commandBuffer.getIsCommandBufferInvalid();
		ASSERT_FALSE(isInvalid);

		commandBuffer.setIsCommandBufferInvalid(true);
		isInvalid = commandBuffer.getIsCommandBufferInvalid();
		ASSERT_TRUE(isInvalid);
	}

	TEST_F(CommandBufferSimpleTests, CreateImageMemoryBarrier)
	{
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

	class CommandBufferTests : public ::testing::Test
	{
	protected:

		RendererContext rendererContext;
		CommandBuffer commandBuffer;

		void SetUp() override
		{
			GLFW::Init();

			rendererContext.initialize();

			commandBuffer.allocateCommandBuffer(rendererContext.getDevice(), rendererContext.getCommandPool());
			ASSERT_TRUE(commandBuffer.isValid());
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST_F(CommandBufferTests, CopyBufferToImage)
	{
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

		commandBuffer.allocateCommandBuffer(rendererContext.getDevice(), commandPool);

		commandBuffer.begin();
		commandBuffer.copyBufferToImage(stagingBuffer, image, newLayout, imageRegion);

		commandBuffer.~CommandBuffer();
	}

	TEST_F(CommandBufferTests, BindVertexBuffer)
	{
		VertexBuffer vertexBuffer;
		vk::BufferCreateInfo vkBufferCreateInfo = vertexBuffer.createCreateInfo(1u);
		vkBufferCreateInfo.usage = vk::BufferUsageFlagBits::eVertexBuffer;
		VmaAllocationCreateInfo allocationCreateInfo = vertexBuffer.createVmaAllocationCreateInfo(false, true);

		BufferCreateInfo bufferCreateInfo{ .device = rendererContext.getDevice(), .vma = rendererContext.getVma()};
		bufferCreateInfo.vkBufferCreateInfo = vkBufferCreateInfo;
		bufferCreateInfo.allocationCreateInfo = allocationCreateInfo;

		vertexBuffer.create(bufferCreateInfo);

		commandBuffer.begin();
		commandBuffer.bindVertexBuffer(0u, vertexBuffer, vk::DeviceSize{ 0 });
	}

	TEST_F(CommandBufferTests, BindIndexBuffer)
	{
		IndexBuffer indexBuffer;
		vk::BufferCreateInfo vkBufferCreateInfo = indexBuffer.createCreateInfo(1u);
		vkBufferCreateInfo.usage = vk::BufferUsageFlagBits::eIndexBuffer;
		VmaAllocationCreateInfo allocationCreateInfo = indexBuffer.createVmaAllocationCreateInfo(false, true);

		BufferCreateInfo bufferCreateInfo{ .device = rendererContext.getDevice(), .vma = rendererContext.getVma() };
		bufferCreateInfo.vkBufferCreateInfo = vkBufferCreateInfo;
		bufferCreateInfo.allocationCreateInfo = allocationCreateInfo;

		indexBuffer.create(bufferCreateInfo);

		commandBuffer.begin();
		vk::DeviceSize offset = 0u;
		vk::IndexType indexType = vk::IndexType::eUint16;
		commandBuffer.bindIndexBuffer(indexBuffer, offset, indexType);
	}

	TEST_F(CommandBufferTests, RenderPassTest)
	{
		ImageView imageView;
		std::vector<vk::Image> images = rendererContext.getSwapChain().getImages();
		vk::SurfaceFormatKHR surfaceFormat = rendererContext.getSwapChainSupportDetails().pickFormat();
		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(images[0], surfaceFormat.format);
		imageView.create(rendererContext.getDevice(), imageViewCreateInfo);

		RenderPass renderPass;
		renderPass.createColorAttachmentDescription(surfaceFormat.format);
		renderPass.createColorAttachmentReference();
		renderPass.createDepthAttachmentDescription(rendererContext.getDepthBufferFormat());
		renderPass.createDepthAttachmentReference();
		renderPass.createSubpassDescription();
		renderPass.createSubpassDependency();

		vk::RenderPassCreateInfo createInfo = renderPass.createRenderPassCreateInfo();
		renderPass.create(rendererContext.getDevice(), createInfo);

		Framebuffer framebuffer;
		vk::FramebufferCreateInfo framebufferCreateInfo = framebuffer.createCreateInfo(imageView, renderPass, rendererContext.getSwapExtent());
		
		std::array<vk::ImageView, 2u> framebufferAttachments = { imageView.getVk(), rendererContext.getDepthBuffer().getImageView().getVk() };
		framebufferCreateInfo.pAttachments = framebufferAttachments.data();
		framebufferCreateInfo.attachmentCount = static_cast<std::uint32_t>(framebufferAttachments.size());
		
		framebuffer.create(rendererContext.getDevice(), framebufferCreateInfo);

		vk::Rect2D renderArea;
		vk::ClearValue colorClearValue;
		vk::ClearValue depthBufferClearValue;

		commandBuffer.begin();

		std::array<vk::ClearValue, 2u> clearValues;

		CommandBuffer::BeginRenderPassInfo beginRenderPassInfo
		{
			.renderPass = renderPass,
			.framebuffer = framebuffer,
			.renderArea = renderArea,
			.clearValues = clearValues
		};
		commandBuffer.beginRenderPass(beginRenderPassInfo);
		commandBuffer.endRenderPass();
	}
	
}
