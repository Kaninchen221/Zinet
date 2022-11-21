#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Device;
	class CommandPool;
	class Framebuffer;
	class RenderPass;
	class Pipeline;
	class Buffer;
	class Queue;
	class Image;
	class StagingBuffer;
	class Image;
	class VertexBuffer;
	class IndexBuffer;

	class ZINET_GRAPHIC_LAYER_API CommandBuffer : public VulkanObject<vk::raii::CommandBuffer>
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("CommandBuffer");

	public:

		CommandBuffer();
		CommandBuffer(const CommandBuffer& other) = default;
		CommandBuffer(CommandBuffer&& other) = default;

		CommandBuffer& operator = (const CommandBuffer& other) = default;
		CommandBuffer& operator = (CommandBuffer&& other) = default;

		~CommandBuffer() noexcept = default;

		vk::CommandBufferAllocateInfo createCommandBufferAllocateInfo(CommandPool& commandPool) const;

		void allocateCommandBuffer(const Device& device, CommandPool& commandPool);

		void begin();

		void end();

		void beginRenderPass(RenderPass& renderPass, Framebuffer& framebuffer, const vk::Rect2D& renderArea);

		void endRenderPass();

		void bindPipeline(Pipeline& pipeline);

		void reset();

		vk::ImageMemoryBarrier createImageMemoryBarrier(Image& image, vk::ImageLayout oldLayout, vk::ImageLayout newLayout);
		
		void copyBufferToImage(const Buffer& buffer, Image& image, vk::ImageLayout newLayout, vk::BufferImageCopy imageRegion);

		void bindVertexBuffer(uint32_t firstBinding, const VertexBuffer& vertexBuffer, vk::DeviceSize offset);

		void bindIndexBuffer(const IndexBuffer& indexBuffer, vk::DeviceSize deviceSize, vk::IndexType indexType);

	protected:

		vk::ClearValue clearValue{};

	};

}
