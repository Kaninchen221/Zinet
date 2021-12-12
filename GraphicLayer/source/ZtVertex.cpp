#include "Zinet/GraphicLayer/ZtVertex.h"

namespace zt::gl
{

	Vertex::Vertex(const glm::vec3& newPosition, const glm::vec4& newColor, const glm::vec2& newTextureCoordinates)
		: position(newPosition),
		color(newColor),
		textureCoordinates(newTextureCoordinates)
	{}

	glm::vec3 Vertex::getPosition() const
	{
		return position;
	}

	void Vertex::setPosition(const glm::vec3& newPosition)
	{
		position = newPosition;
	}

	std::size_t Vertex::GetOffsetToPosition()
	{
		return 0;
	}

	glm::vec4 Vertex::getColor() const
	{
		return color;
	}

	void Vertex::setColor(const glm::vec4& newColor)
	{
		color = newColor;
	}

	std::size_t Vertex::GetOffsetToColor()
	{
		return sizeof(decltype(position));
	}

	glm::vec2 Vertex::getTextureCoordinates() const
	{
		return textureCoordinates;
	}

	void Vertex::setTextureCoordinates(const glm::vec2& newTextureCoordinates)
	{
		textureCoordinates = newTextureCoordinates;
	}

	std::size_t Vertex::GetOffsetToTextureCoordinates()
	{
		return sizeof(decltype(position)) + sizeof(decltype(color));
	}

}