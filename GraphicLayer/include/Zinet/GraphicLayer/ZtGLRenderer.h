#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Renderer
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Renderer");

	public:

		Renderer();
		Renderer(const Renderer& other) = default;
		Renderer(Renderer&& other) = default;

		Renderer& operator = (const Renderer& other) = default;
		Renderer& operator = (Renderer&& other) = default;

		~Renderer() noexcept;

	public:

		Context context;

		Instance instanceHelper;

		PhysicalDevice physicalDevice;

	};

}