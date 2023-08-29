#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Math/ZtVecTypes.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	struct ZINET_GRAPHIC_LAYER_API TextureRegion
	{
		Vector2f offset;
		Vector2f size;

		TextureRegion toShaderTextureRegion(const Vector2f& textureSize) const;

	};

	ZINET_GRAPHIC_LAYER_API inline bool operator == (const TextureRegion& first, const TextureRegion& second)
	{
		return first.offset == second.offset && first.size == second.size;
	}
}