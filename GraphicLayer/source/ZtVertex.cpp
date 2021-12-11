#include "Zinet/GraphicLayer/ZtVertex.h"

namespace zt::gl
{

	Vertex::Vertex(const glm::vec3& NewPosition, const glm::vec4& NewColor, const glm::vec2& NewTextureCoordinates)
		: Position(NewPosition),
		Color(NewColor),
		TextureCoordinates(NewTextureCoordinates)
	{}

	glm::vec3 Vertex::GetPosition() const
	{
		return Position;
	}

	void Vertex::SetPosition(const glm::vec3& NewPosition)
	{
		Position = NewPosition;
	}

	std::size_t Vertex::GetOffsetToPosition()
	{
		return 0;
	}

	glm::vec4 Vertex::GetColor() const
	{
		return Color;
	}

	void Vertex::SetColor(const glm::vec4& NewColor)
	{
		Color = NewColor;
	}

	std::size_t Vertex::GetOffsetToColor()
	{
		return sizeof(decltype(Position));
	}

	glm::vec2 Vertex::GetTextureCoordinates() const
	{
		return TextureCoordinates;
	}

	void Vertex::SetTextureCoordinates(const glm::vec2& NewTextureCoordinates)
	{
		TextureCoordinates = NewTextureCoordinates;
	}

	std::size_t Vertex::GetOffsetToTextureCoordinates()
	{
		return sizeof(decltype(Position)) + sizeof(decltype(Color));
	}

}