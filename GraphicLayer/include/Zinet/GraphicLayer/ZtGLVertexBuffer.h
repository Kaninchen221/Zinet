#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLBuffer.h"

#include <vector>

namespace zt::gl
{
	class Vertex;
	class Device;
	class DeviceMemory;

	class ZINET_GRAPHIC_LAYER_API VertexBuffer : public Buffer
	{

	public:

		VertexBuffer() = default;
		VertexBuffer(const VertexBuffer& other) = default;
		VertexBuffer(VertexBuffer&& other) = default;

		VertexBuffer& operator = (const VertexBuffer& other) = default;
		VertexBuffer& operator = (VertexBuffer&& other) = default;

		~VertexBuffer() noexcept = default;

		const std::vector<Vertex>& getVertices() const;

		void setVertices(const std::vector<Vertex>& vertices);

		vk::BufferCreateInfo createCreateInfo() const override;

	protected:

		std::vector<Vertex> vertices;

	};

}