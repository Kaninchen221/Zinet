#pragma once

#include "Zinet/GraphicLayer/ZtGLCommandBuffer.hpp"
#include "Zinet/GraphicLayer/ZtGLFence.hpp"

#include "Zinet/Core/ZtLogger.hpp"

namespace zt::gl
{;
	class RendererContext;

	class ZINET_GRAPHIC_LAYER_API SignalCommandBuffer : public CommandBuffer
	{

	public:

		SignalCommandBuffer() = default;
		SignalCommandBuffer(const SignalCommandBuffer& other) = default;
		SignalCommandBuffer(SignalCommandBuffer&& other) = default;

		SignalCommandBuffer& operator = (const SignalCommandBuffer& other) = default;
		SignalCommandBuffer& operator = (SignalCommandBuffer&& other) = default;

		~SignalCommandBuffer() noexcept = default;

		const Fence& getFence() const { return fence; }
		Fence& getFence() { return fence; }

		void create(const RendererContext& rendererContext);

		bool isReady() const;

	protected:

		Fence fence;

	};

}
