#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Device;
	class CommandPool;
	class Framebuffer;
	class RenderPass;
	class Pipeline;

	class ZINET_GRAPHIC_LAYER_API CommandBuffer
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

		vk::raii::CommandBuffer& getInternal();

		vk::raii::CommandBuffer* operator -> ();

		vk::CommandBufferAllocateInfo createCommandBufferAllocateInfo(CommandPool& commandPool) const;

		void allocateCommandBuffer(Device& device, CommandPool& commandPool);

		void begin();

		void end();

		void beginRenderPass(RenderPass& renderPass, Framebuffer& framebuffer, const vk::Rect2D& renderArea);

		void endRenderPass();

		void bindPipeline(Pipeline& pipeline);

	protected:

		vk::raii::CommandBuffer internal;
		vk::ClearValue clearValue{};

	};

}
