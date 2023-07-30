#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"

#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLCommandPool.h"
#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLFramebuffer.h"
#include "Zinet/GraphicLayer/ZtGLPipeline.h"
#include "Zinet/GraphicLayer/ZtGLPipelineLayout.h"
#include "Zinet/GraphicLayer/ZtGLQueue.h"
#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLBuffer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLStagingBuffer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLIndexBuffer.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorSets.h"

namespace zt::gl
{
	vk::CommandBufferAllocateInfo CommandBuffer::createCommandBufferAllocateInfo(const CommandPool& commandPool) const
	{
		vk::CommandBufferAllocateInfo allocateInfo;
		allocateInfo.commandPool = *commandPool.getInternal();
		allocateInfo.level = vk::CommandBufferLevel::ePrimary;
		allocateInfo.commandBufferCount = 1;

		return allocateInfo;
	}

	void CommandBuffer::allocateCommandBuffer(const Device& device, const CommandPool& commandPool)
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

	void CommandBuffer::beginRenderPass(BeginRenderPassInfo& info)
	{
		vk::RenderPassBeginInfo renderPassInfo{};
		renderPassInfo.renderPass = *info.renderPass.getInternal();
		renderPassInfo.framebuffer = *info.framebuffer.getInternal();
		renderPassInfo.renderArea = info.renderArea;
		renderPassInfo.clearValueCount = static_cast<std::uint32_t>(info.clearValues.size());
		renderPassInfo.pClearValues = info.clearValues.data();

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

	vk::ImageMemoryBarrier CommandBuffer::createImageMemoryBarrier(const CreateImageMemoryBarrierInfo& createImageMemoryBarrierInfo)
	{
		vk::ImageMemoryBarrier barrier;

		barrier.oldLayout = createImageMemoryBarrierInfo.oldLayout;
		barrier.newLayout = createImageMemoryBarrierInfo.newLayout;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED; 
		barrier.image = *createImageMemoryBarrierInfo.image.getInternal();
		barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
		barrier.subresourceRange.baseMipLevel = createImageMemoryBarrierInfo.mipmapLevel;
		barrier.subresourceRange.levelCount = createImageMemoryBarrierInfo.mipmapLevels;
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.subresourceRange.layerCount = 1;
		barrier.srcAccessMask = vk::AccessFlagBits{};
		barrier.dstAccessMask = vk::AccessFlagBits{};

		return barrier;
	}

	void CommandBuffer::copyBufferToImage(const CopyBufferToImageInfo& copyBufferToImageInfo)
	{
		internal.copyBufferToImage(
			*copyBufferToImageInfo.buffer.getInternal(), 
			*copyBufferToImageInfo.image.getInternal(), 
			copyBufferToImageInfo.newLayout, 
			copyBufferToImageInfo.imageRegion);
	}

	void CommandBuffer::bindVertexBuffer(uint32_t firstBinding, const VertexBuffer& vertexBuffer, vk::DeviceSize offset)
	{
		internal.bindVertexBuffers(firstBinding, { *vertexBuffer.getInternal() }, offset);
	}

	void CommandBuffer::bindIndexBuffer(const IndexBuffer& indexBuffer, vk::DeviceSize deviceSize, vk::IndexType indexType)
	{
		internal.bindIndexBuffer(*indexBuffer.getInternal(), deviceSize, indexType);
	}

	void CommandBuffer::bindDescriptorSets(const BindDescriptorSetsInfo& info)
	{
		vkDescriptorSets.clear();
		for (auto& set : info.descriptorSets)
		{
			vkDescriptorSets.push_back(*set);
		}

		internal.bindDescriptorSets(info.bindPoint, *info.pipelineLayout.getInternal(), info.firstSet, vkDescriptorSets, info.dynamicOffsets);
	}

}
