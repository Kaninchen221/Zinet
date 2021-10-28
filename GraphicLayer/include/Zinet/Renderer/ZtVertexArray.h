#pragma once

#include "Zinet/Renderer/ZtRenderer.h"
#include "Zinet/Renderer/ZtObject.h"

class ZINET_RENDERER_API ZtVertexArray : public ZtObject
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