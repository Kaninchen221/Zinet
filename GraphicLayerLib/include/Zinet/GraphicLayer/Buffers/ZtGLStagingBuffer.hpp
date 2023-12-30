#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLBuffer.h"

#include <vector>

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API StagingBuffer : public Buffer
	{

	public:

		StagingBuffer() = default;
		StagingBuffer(const StagingBuffer& other) = default;
		StagingBuffer(StagingBuffer&& other) = default;

		StagingBuffer& operator = (const StagingBuffer& other) = default;
		StagingBuffer& operator = (StagingBuffer&& other) = default;

		~StagingBuffer() noexcept = default;

		vk::BufferCreateInfo createCreateInfo(std::uint64_t newSize) const override;

	};

}