#pragma once

#include "Zinet/Renderer/ZtRenderer.h"
#include "Zinet/Renderer/ZtBufferUsage.h"

#include <array>

class ZINET_RENDERER_API ZtElementBuffer
{

public:

	inline static const GLuint InvalidID = 0u;

	void Generate();

	void Bind();

	void Unbind();

	GLuint GetID() const;

	template<typename ContainerType>
	void SetData(const ContainerType& Container, ZtBufferUsage Usage);

	void Delete();

protected:

	GLuint ID;

};

template<typename ContainerType>
inline void ZtElementBuffer::SetData(const ContainerType& Container, ZtBufferUsage Usage)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Container.size() * sizeof(ContainerType::value_type), Container.data(), static_cast<GLenum>(Usage));
}