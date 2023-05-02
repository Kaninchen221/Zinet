#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLDrawInfo.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API DrawableObject
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("DrawableObject");

	public:

		DrawableObject() = default;
		DrawableObject(const DrawableObject& other) = default;
		DrawableObject(DrawableObject&& other) = default;

		DrawableObject& operator = (const DrawableObject& other) = default;
		DrawableObject& operator = (DrawableObject&& other) = default;

		virtual ~DrawableObject() noexcept = default;

		virtual const DrawInfo& getDrawInfo() const = 0;

		virtual void createDrawInfo() = 0;
	};

}