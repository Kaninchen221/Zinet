#pragma once

#include "Zinet/Renderer/ZtRenderer.h"

#include "vec3.hpp"

class ZINET_RENDERER_API ZtVertex
{

public:

	ZtVertex() = default;
	ZtVertex(const ZtVertex& Other) = default;
	ZtVertex(ZtVertex&& Other) = default;
	ZtVertex(const glm::vec3& NewPosition);

	ZtVertex& operator = (const ZtVertex& Other) = default;
	ZtVertex& operator = (ZtVertex&& Other) = default;

	~ZtVertex() noexcept = default;

	glm::vec3 GetPosition() const;

	void SetPosition(const glm::vec3& NewPosition);

protected:

	glm::vec3 Position;

};