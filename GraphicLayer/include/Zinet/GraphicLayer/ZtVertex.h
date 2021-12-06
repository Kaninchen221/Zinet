#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

class ZINET_GRAPHIC_LAYER_API ZtVertex
{

public:

	ZtVertex() = default;
	ZtVertex(const ZtVertex& Other) = default;
	ZtVertex(ZtVertex&& Other) = default;
	ZtVertex(const glm::vec3& NewPosition, const glm::vec4& NewColor, const glm::vec2& NewTextureCoordinates);

	ZtVertex& operator = (const ZtVertex& Other) = default;
	ZtVertex& operator = (ZtVertex&& Other) = default;

	~ZtVertex() noexcept = default;

	glm::vec3 GetPosition() const;

	void SetPosition(const glm::vec3& NewPosition);

	static std::size_t GetOffsetToPosition();

	glm::vec4 GetColor() const;

	void SetColor(const glm::vec4& NewColor);

	static std::size_t GetOffsetToColor();

	glm::vec2 GetTextureCoordinates() const;

	void SetTextureCoordinates(const glm::vec2& NewTextureCoordinates);

	static std::size_t GetOffsetToTextureCoordinates();

protected:

	glm::vec3 Position;
	glm::vec4 Color;
	glm::vec2 TextureCoordinates;

};