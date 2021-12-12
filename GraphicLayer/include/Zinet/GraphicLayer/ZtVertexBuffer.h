#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtBufferUsage.h"
#include "Zinet/GraphicLayer/ZtObject.h"

#include <array>

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API VertexBuffer : public Object
	{

	public:

		void generate();

		void bind();

		void unbind();

		template<typename ContainerType>
		void setData(const ContainerType& Container, BufferUsage Usage);

		void deleteResource();

	};

	template<typename ContainerType>
	inline void VertexBuffer::setData(const ContainerType& Container, BufferUsage Usage)
	{

	}

}