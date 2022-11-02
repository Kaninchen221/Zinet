#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLBuffer.h"

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

		vk::BufferCreateInfo createCreateInfo(std::uint64_t size) const override;

		VmaAllocationCreateInfo createVmaAllocationCreateInfo(bool randomAccess) const override
		{
			VmaAllocationCreateInfo allocationCreateInfo{};
			return allocationCreateInfo;
		}
	};

}