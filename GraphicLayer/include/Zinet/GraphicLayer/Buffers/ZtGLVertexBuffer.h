#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLBuffer.h"

#include "vk_mem_alloc.h"

namespace zt::gl
{
	class Renderer;
	class Vma;

	class ZINET_GRAPHIC_LAYER_API VertexBuffer : public Buffer
	{

	public:

		VertexBuffer() = default;
		VertexBuffer(const VertexBuffer& other) = default;
		VertexBuffer(VertexBuffer&& other) = default;

		VertexBuffer& operator = (const VertexBuffer& other) = default;
		VertexBuffer& operator = (VertexBuffer&& other) = default;

		~VertexBuffer() noexcept = default;

		vk::BufferCreateInfo createCreateInfo(std::uint64_t size) const override;

	};

}