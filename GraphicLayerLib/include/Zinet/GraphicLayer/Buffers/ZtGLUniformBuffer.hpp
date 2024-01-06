#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/Buffers/ZtGLBuffer.hpp"

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

		vk::DescriptorBufferInfo createDescriptorBufferInfo() const;

		void setBinding(std::uint32_t newBinding) { binding = newBinding; }
		std::uint32_t getBinding() const { return binding; }

	protected:

		std::uint32_t binding{};

	};

}