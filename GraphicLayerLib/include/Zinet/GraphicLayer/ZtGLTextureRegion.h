#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Window/ZtVecTypes.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	struct ZINET_GRAPHIC_LAYER_API TextureRegion
	{
		zt::Vector2f offset;
		zt::Vector2f size;

		TextureRegion toShaderTextureRegion(const zt::Vector2f& textureSize) const;

	};

	ZINET_GRAPHIC_LAYER_API inline bool operator == (const TextureRegion& first, const TextureRegion& second)
	{
		return first.offset == second.offset && first.size == second.size;
	}
}