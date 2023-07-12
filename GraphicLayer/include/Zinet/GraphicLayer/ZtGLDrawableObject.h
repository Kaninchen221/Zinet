#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLDrawInfo.h"
#include "Zinet/GraphicLayer/ZtGLTransform.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class RendererContext;

	class ZINET_GRAPHIC_LAYER_API DrawableObject
	{

	public:

		DrawableObject() = default;
		DrawableObject(const DrawableObject& other) = default;
		DrawableObject(DrawableObject&& other) = default;

		DrawableObject& operator = (const DrawableObject& other) = default;
		DrawableObject& operator = (DrawableObject&& other) = default;

		virtual ~DrawableObject() noexcept = default;

		virtual DrawInfo createDrawInfo(RendererContext& rendererContext) const = 0;

		virtual const Transform& getTransform() const = 0;

		virtual Vector2ui getAbsoluteSize() const = 0;
	};

}