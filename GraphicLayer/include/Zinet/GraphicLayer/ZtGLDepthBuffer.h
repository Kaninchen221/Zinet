#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLImage.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API DepthBuffer
	{

	protected:

		inline static ConsoleLogger Logger = ConsoleLogger::Create("DepthBuffer");

	public:

		DepthBuffer() = default;
		DepthBuffer(const DepthBuffer& other) = default;
		DepthBuffer(DepthBuffer&& other) = default;

		DepthBuffer& operator = (const DepthBuffer& other) = default;
		DepthBuffer& operator = (DepthBuffer&& other) = default;

		~DepthBuffer() noexcept = default;

		const Image& getImage() const { return image; }

	protected:

		Image image;

	};

}