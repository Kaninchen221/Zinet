#include "Zinet/GraphicLayer/ZtGLTextureRegion.h"

namespace zt::gl
{

	TextureRegion TextureRegion::toShaderTextureRegion(const zt::Vector2f& textureSize) const
	{
		TextureRegion result = *this;
		result.offset.x /= textureSize.x;
		result.offset.y /= textureSize.y;
		result.size.x /= textureSize.x;
		result.size.y /= textureSize.y;

		return result;
	}

}