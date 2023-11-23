#pragma once

#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLFence.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{;
	class RendererContext;

	class ZINET_GRAPHIC_LAYER_API SignalCommandBuffer
	{

	public:

		SignalCommandBuffer() = default;
		SignalCommandBuffer(const SignalCommandBuffer& other) = default;
		SignalCommandBuffer(SignalCommandBuffer&& other) = default;

		SignalCommandBuffer& operator = (const SignalCommandBuffer& other) = default;
		SignalCommandBuffer& operator = (SignalCommandBuffer&& other) = default;

		~SignalCommandBuffer() noexcept = default;

		const CommandBuffer& getCommandBuffer() const { return commandBuffer; }

		const Fence& getFence() const { return fence; }

		void create(const RendererContext& rendererContext);

	protected:

		CommandBuffer commandBuffer;
		Fence fence;

	};

}
