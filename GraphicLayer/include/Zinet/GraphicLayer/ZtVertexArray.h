#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtObject.h"

class ZINET_GRAPHIC_LAYER_API ZtVertexArray : public ZtObject
{

public:

	ZtVertexArray() = default;
	ZtVertexArray(const ZtVertexArray& Other) = default;
	ZtVertexArray(ZtVertexArray&& Other) = default;

	ZtVertexArray& operator = (const ZtVertexArray& Other) = default;
	ZtVertexArray& operator = (ZtVertexArray&& Other) = default;

	~ZtVertexArray() noexcept;

	void Generate();

	void Bind();

	void Unbind();

	void Delete();

};