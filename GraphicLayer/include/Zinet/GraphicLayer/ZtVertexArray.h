#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtObject.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API VertexArray : public Object
	{

	public:

		VertexArray() = default;
		VertexArray(const VertexArray& other) = default;
		VertexArray(VertexArray&& other) = default;

		VertexArray& operator = (const VertexArray& other) = default;
		VertexArray& operator = (VertexArray&& other) = default;

		~VertexArray() noexcept;

		void generate();

		void bind();

		void unbind();

		void deleteResource();

	};

}