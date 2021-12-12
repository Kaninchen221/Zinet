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
		ElementBuffer(const ElementBuffer& other) = default;
		ElementBuffer(ElementBuffer&& other) = default;

		ElementBuffer& operator = (const ElementBuffer& other) = default;
		ElementBuffer& operator = (ElementBuffer&& other) = default;

		~ElementBuffer() noexcept;

		void generate();

		void bind();

		void unbind();

		template<typename ContainerType>
		void setData(const ContainerType& container, BufferUsage usage);

		void deleteResource();

	};

	template<typename ContainerType>
	inline void ElementBuffer::setData(const ContainerType& container, BufferUsage usage)
	{

	}

}