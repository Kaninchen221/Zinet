#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"

#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLCommandPool.h"
#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLFramebuffer.h"
#include "Zinet/GraphicLayer/ZtGLPipeline.h"
#include "Zinet/GraphicLayer/ZtGLBufferCopy.h"
#include "Zinet/GraphicLayer/ZtGLBuffer.h"

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

	void CommandBuffer::copyBuffer(Buffer& sourceBuffer, Buffer& destinationBuffer)
	{
		begin();

		BufferCopy bufferCopy;
		bufferCopy.srcOffset = 0;
		bufferCopy.dstOffset = 0;
		bufferCopy.size = sourceBuffer.getSize();

		internal.copyBuffer(*sourceBuffer.getInternal(), *destinationBuffer.getInternal(), bufferCopy);

		destinationBuffer.setSize(sourceBuffer.getSize());

		end();
	}

}
