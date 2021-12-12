#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Context
	{

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Context");

	public:

		Context() = default;
		Context(const Context& other) = default;
		Context(Context&& other) = default;

		Context& operator = (const Context& other) = default;
		Context& operator = (Context&& other) = default;

		~Context() noexcept;

		bool initGLFW();

		void deinitGLFW();

		bool initGLAD();

		bool initOpenGL();

		static void FillMode();

		static void PolygonOnlyMode();

		static void PointsMode();

		static std::string GetSourceAsString(GLenum source);

		static std::string GetTypeAsString(GLenum type);

		static std::string GetSeverityAsString(GLenum severity);
	};

}