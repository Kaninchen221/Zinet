#pragma once

#include "Zinet/Renderer/ZtRenderer.h"
#include "Zinet/Renderer/ZtVertexBufferUsage.h"

#include <array>

class ZINET_RENDERER_API ZtVertexBuffer
{

public:

	inline static const GLuint InvalidID = 0u;

	void Generate();

	void Bind();

	void Unbind();

	GLuint GetID() const;

	template<typename ContainerType>
	void SetData(const ContainerType& Container, ZtVertexBufferUsage Usage);

	void Delete();

protected:

	GLuint ID;

};

template<typename ContainerType>
inline void ZtVertexBuffer::SetData(const ContainerType& Container, ZtVertexBufferUsage Usage)
{
	glBufferData(GL_ARRAY_BUFFER, Container.size() * sizeof(ContainerType::value_type), Container.data(), static_cast<GLenum>(Usage));
}