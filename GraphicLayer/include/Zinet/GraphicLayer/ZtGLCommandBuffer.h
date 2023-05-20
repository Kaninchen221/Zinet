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
	class PipelineLayout;
	class Buffer;
	class Queue;
	class Image;
	class StagingBuffer;
	class Image;
	class VertexBuffer;
	class IndexBuffer;
	class DescriptorSets;

	class ZINET_GRAPHIC_LAYER_API CommandBuffer : public VulkanObject<vk::raii::CommandBuffer>
	{

	public:

		struct ZINET_GRAPHIC_LAYER_API BeginRenderPassInfo
		{
			RenderPass& renderPass;
			Framebuffer& framebuffer;
			const vk::Rect2D& renderArea;
			const vk::ClearValue& clearValue;
		};

	protected:

		inline static ConsoleLogger Logger = ConsoleLogger::Create("CommandBuffer");

	public:

		CommandBuffer();
		CommandBuffer(const CommandBuffer& other) = default;
		CommandBuffer(CommandBuffer&& other) = default;

		CommandBuffer& operator = (const CommandBuffer& other) = default;
		CommandBuffer& operator = (CommandBuffer&& other) = default;

		~CommandBuffer() noexcept = default;

		vk::CommandBufferAllocateInfo createCommandBufferAllocateInfo(const CommandPool& commandPool) const;

		void allocateCommandBuffer(const Device& device, const CommandPool& commandPool);

		void begin();

		void end();

		void beginRenderPass(BeginRenderPassInfo& info);

		void endRenderPass();

		void bindPipeline(Pipeline& pipeline);

		void reset();

		vk::ImageMemoryBarrier createImageMemoryBarrier(Image& image, vk::ImageLayout oldLayout, vk::ImageLayout newLayout);
		
		void copyBufferToImage(const Buffer& buffer, Image& image, vk::ImageLayout newLayout, vk::BufferImageCopy imageRegion);

		void bindVertexBuffer(uint32_t firstBinding, const VertexBuffer& vertexBuffer, vk::DeviceSize offset);

		void bindIndexBuffer(const IndexBuffer& indexBuffer, vk::DeviceSize deviceSize, vk::IndexType indexType);

		void bindDescriptorSets(
			vk::PipelineBindPoint bindPoint,
			const PipelineLayout& pipelineLayout,
			std::uint32_t firstSet,
			const DescriptorSets& descriptorSets,
			const vk::ArrayProxy<const uint32_t>& dynamicOffsets);

		// TODO Add test
		void setIsCommandBufferInvalid(bool value) { isCommandBufferInvalid = value; }
		bool getIsCommandBufferInvalid() const { return isCommandBufferInvalid; }

	protected:

		bool isCommandBufferInvalid = false;
		std::vector<vk::DescriptorSet> vkDescriptorSets;

	};

}
