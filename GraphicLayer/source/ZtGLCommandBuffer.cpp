#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"

#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLCommandPool.h"
#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLFramebuffer.h"
#include "Zinet/GraphicLayer/ZtGLPipeline.h"
#include "Zinet/GraphicLayer/ZtGLBufferCopy.h"
#include "Zinet/GraphicLayer/ZtGLBuffer.h"
#include "Zinet/GraphicLayer/ZtGLQueue.h"
#include "Zinet/GraphicLayer/ZtGLImage.h"

namespace zt::gl
{
	CommandBuffer::CommandBuffer()
	{
		clearValue = vk::ClearColorValue{ std::array<float, 4>{ 0.5f, 0.5f, 0.5f, 1.f } };
	}

	vk::CommandBufferAllocateInfo CommandBuffer::createCommandBufferAllocateInfo(CommandPool& commandPool) const
	{
		vk::CommandBufferAllocateInfo allocateInfo;
		allocateInfo.commandPool = *commandPool.getInternal();
		allocateInfo.level = vk::CommandBufferLevel::ePrimary;
		allocateInfo.commandBufferCount = 1;

		return allocateInfo;
	}

	void CommandBuffer::allocateCommandBuffer(Device& device, CommandPool& commandPool)
	{
		vk::CommandBufferAllocateInfo allocateInfo = createCommandBufferAllocateInfo(commandPool);
		internal = std::move(vk::raii::CommandBuffers(device.getInternal(), allocateInfo).front());
	}

	void CommandBuffer::begin()
	{
		vk::CommandBufferBeginInfo beginInfo{};
		beginInfo.flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit;
		beginInfo.pInheritanceInfo = nullptr;

		internal.begin(beginInfo);
	}

	void CommandBuffer::end()
	{
		internal.end();
	}

	void CommandBuffer::beginRenderPass(RenderPass& renderPass, Framebuffer& framebuffer, const vk::Rect2D& renderArea)
	{
		vk::RenderPassBeginInfo renderPassInfo{};
		renderPassInfo.renderPass = *renderPass.getInternal();
		renderPassInfo.framebuffer = *framebuffer.getInternal(); 
		renderPassInfo.renderArea = renderArea;
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearValue;

		internal.beginRenderPass(renderPassInfo, {});
	}

	void CommandBuffer::endRenderPass()
	{
		internal.endRenderPass();
	}

	void CommandBuffer::bindPipeline(Pipeline& pipeline)
	{
		vk::PipelineBindPoint bindPoint = vk::PipelineBindPoint::eGraphics;
		internal.bindPipeline(bindPoint, *pipeline.getInternal());
	}

	void CommandBuffer::reset()
	{
		vk::CommandBufferResetFlagBits flags = vk::CommandBufferResetFlagBits::eReleaseResources;
		internal.reset(flags);
	}

	void CommandBuffer::copyBuffer(Buffer& sourceBuffer, Buffer& destinationBuffer, Queue& queue)
	{
		begin();

		BufferCopy bufferCopy;
		bufferCopy.srcOffset = 0;
		bufferCopy.dstOffset = 0;
		bufferCopy.size = sourceBuffer.getSize();

		internal.copyBuffer(*sourceBuffer.getInternal(), *destinationBuffer.getInternal(), bufferCopy);

		end();

		SubmitInfo submitInfo{};
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*getInternal();

		queue.submit(submitInfo);
		queue->waitIdle();
	}

	vk::ImageMemoryBarrier CommandBuffer::createImageMemoryBarrier(Image& image, vk::ImageLayout oldLayout, vk::ImageLayout newLayout)
	{
		vk::ImageMemoryBarrier barrier;

		barrier.oldLayout = oldLayout;
		barrier.newLayout = newLayout;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED; 
		barrier.image = *image.getInternal();
		barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
		barrier.subresourceRange.baseMipLevel = 0;
		barrier.subresourceRange.levelCount = 1;
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.subresourceRange.layerCount = 1;
		barrier.srcAccessMask = vk::AccessFlagBits{};
		barrier.dstAccessMask = vk::AccessFlagBits{};

		return barrier;
	}

}
