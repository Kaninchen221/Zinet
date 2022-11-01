#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLBuffer.h"

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

		~VertexBuffer() noexcept;

		vk::BufferCreateInfo createCreateInfo(std::uint64_t size) const override;

		VmaAllocationCreateInfo createVmaAllocationCreateInfo(bool randomAccess) const;

		void create(const Renderer& renderer, const VkBufferCreateInfo& bufferCreateInfo, const VmaAllocationCreateInfo& allocationCreateInfo);

	private:

		const Vma* vma;
		VmaAllocation allocation = nullptr;

	};

}