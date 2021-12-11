#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtObject.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API VertexArray : public Object
	{

	public:

		VertexArray() = default;
		VertexArray(const VertexArray& Other) = default;
		VertexArray(VertexArray&& Other) = default;

		VertexArray& operator = (const VertexArray& Other) = default;
		VertexArray& operator = (VertexArray&& Other) = default;

		~VertexArray() noexcept;

		void Generate();

		void Bind();

		void Unbind();

		void Delete();

	};

}