#pragma once

#include "Zinet/Renderer/ZtRenderer.h"

class ZINET_RENDERER_API ZtVertexArray
{

public:

	const inline static GLuint InvalidID = 0u;

	ZtVertexArray() = default;
	ZtVertexArray(const ZtVertexArray& Other) = default;
	ZtVertexArray(ZtVertexArray&& Other) = default;

	ZtVertexArray& operator = (const ZtVertexArray& Other) = default;
	ZtVertexArray& operator = (ZtVertexArray&& Other) = default;

	~ZtVertexArray() noexcept;

	void Generate();

	GLuint GetID() const;

	void Bind();

	void Unbind();

	void Delete();

protected:

	GLuint ID = InvalidID;

};