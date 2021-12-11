#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtBufferUsage.h"
#include "Zinet/GraphicLayer/ZtObject.h"

#include <array>

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API ElementBuffer : public Object
	{

	public:

		ElementBuffer() = default;
		ElementBuffer(const ElementBuffer& Other) = default;
		ElementBuffer(ElementBuffer&& Other) = default;

		ElementBuffer& operator = (const ElementBuffer& Other) = default;
		ElementBuffer& operator = (ElementBuffer&& Other) = default;

		~ElementBuffer() noexcept;

		void Generate();

		void Bind();

		void Unbind();

		template<typename ContainerType>
		void SetData(const ContainerType& Container, BufferUsage Usage);

		void Delete();

	};

	template<typename ContainerType>
	inline void ElementBuffer::SetData(const ContainerType& Container, BufferUsage Usage)
	{

	}

}