#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLBuffer.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API UniformBuffer : public Buffer
	{

	public:

		UniformBuffer() = default;
		UniformBuffer(const UniformBuffer& other) = default;
		UniformBuffer(UniformBuffer&& other) = default;

		UniformBuffer& operator = (const UniformBuffer& other) = default;
		UniformBuffer& operator = (UniformBuffer&& other) = default;

		~UniformBuffer() noexcept = default;

		vk::BufferCreateInfo createCreateInfo(std::uint64_t newSize) const override;

		vk::DescriptorBufferInfo createDescriptorBufferInfo();

	};

}