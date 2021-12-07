#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

class ZINET_GRAPHIC_LAYER_API ZtGLContext
{

	static inline ZtLogger::SimpleConsoleLogger Logger = ZtLogger::CreateSimpleConsoleLogger("ZtGLContext");

public:

	ZtGLContext() = default;
	ZtGLContext(const ZtGLContext& Other) = default;
	ZtGLContext(ZtGLContext&& Other) = default;

	ZtGLContext& operator = (const ZtGLContext& Other) = default;
	ZtGLContext& operator = (ZtGLContext&& Other) = default;

	~ZtGLContext() noexcept;

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