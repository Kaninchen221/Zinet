#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtBufferUsage.h"
#include "Zinet/GraphicLayer/ZtObject.h"

#include <array>

class ZINET_GRAPHIC_LAYER_API ZtVertexBuffer : public ZtObject
{

public:

	void Generate();

	void Bind();

	void Unbind();

	template<typename ContainerType>
	void SetData(const ContainerType& Container, ZtBufferUsage Usage);

	void Delete();

};

template<typename ContainerType>
inline void ZtVertexBuffer::SetData(const ContainerType& Container, ZtBufferUsage Usage)
{
	glBufferData(GL_ARRAY_BUFFER, Container.size() * sizeof(ContainerType::value_type), Container.data(), static_cast<GLenum>(Usage));
}