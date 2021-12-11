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

		void Generate();

		void Bind();

		void Unbind();

		template<typename ContainerType>
		void SetData(const ContainerType& Container, BufferUsage Usage);

		void Delete();

	};

	template<typename ContainerType>
	inline void VertexBuffer::SetData(const ContainerType& Container, BufferUsage Usage)
	{

	}

}