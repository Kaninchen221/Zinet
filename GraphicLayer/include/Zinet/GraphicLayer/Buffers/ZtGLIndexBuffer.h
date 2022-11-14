#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLBuffer.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API IndexBuffer : public Buffer
	{

	public:

		IndexBuffer() = default;
		IndexBuffer(const IndexBuffer& other) = default;
		IndexBuffer(IndexBuffer&& other) = default;

		IndexBuffer& operator = (const IndexBuffer& other) = default;
		IndexBuffer& operator = (IndexBuffer&& other) = default;

		~IndexBuffer() noexcept = default;

		vk::BufferCreateInfo createCreateInfo(std::uint64_t newSize) const override;

	};

}