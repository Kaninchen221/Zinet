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
		Context(const Context& Other) = default;
		Context(Context&& Other) = default;

		Context& operator = (const Context& Other) = default;
		Context& operator = (Context&& Other) = default;

		~Context() noexcept;

		bool InitGLFW();

		void DeinitGLFW();

		bool InitGLAD();

		bool InitOpenGL();

		static void FillMode();

		static void PolygonOnlyMode();

		static void PointsMode();

		static std::string GetSourceAsString(GLenum Source);

		static std::string GetTypeAsString(GLenum Type);

		static std::string GetSeverityAsString(GLenum Severity);
	};

}