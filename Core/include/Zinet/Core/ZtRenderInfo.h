#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtTexture.h"
#include "Zinet/Core/ZtRectangle.h"
#include "Zinet/Core/ZtRenderInfo.h"
#include "Zinet/Core/ZtPrimitiveType.h"
#include "Zinet/Core/ZtVertex.h"

#include "plf_colony.h"

struct ZINET_CORE_API ZtRenderInfo
{
	plf::colony<ZtVertex> Vertices;
	ZtTexture Texture;
	ZtRectangleI TextureSourceRect;
	ZtPrimitiveType PrimitiveType;
};