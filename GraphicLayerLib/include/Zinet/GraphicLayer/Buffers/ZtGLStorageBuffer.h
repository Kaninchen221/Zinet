#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLBuffer.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API StorageBuffer : public Buffer
	{

	public:

		StorageBuffer() = default;
		StorageBuffer(const StorageBuffer& other) = default;
		StorageBuffer(StorageBuffer&& other) = default;

		StorageBuffer& operator = (const StorageBuffer& other) = default;
		StorageBuffer& operator = (StorageBuffer&& other) = default;

		~StorageBuffer() noexcept = default;

		vk::BufferCreateInfo createCreateInfo(std::uint64_t newSize) const override;

		vk::DescriptorBufferInfo createDescriptorBufferInfo() const;

		void setBinding(std::uint32_t newBinding) { binding = newBinding; }
		std::uint32_t getBinding() const { return binding; }

	protected:

		std::uint32_t binding{};

	};

}