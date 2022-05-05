#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLBuffer.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API VertexBuffer : public Buffer
	{

	public:

		VertexBuffer() = default;
		VertexBuffer(const VertexBuffer& other) = default;
		VertexBuffer(VertexBuffer&& other) = default;

		VertexBuffer& operator = (const VertexBuffer& other) = default;
		VertexBuffer& operator = (VertexBuffer&& other) = default;

		~VertexBuffer() noexcept = default;

		vk::BufferCreateInfo createCreateInfo() const override;

	};

}