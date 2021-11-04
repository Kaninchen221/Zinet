#pragma once

#include "ZtGraphicLayer.h"
#include "ZtGLContext.h"
#include "ZtEvent.h"

#include "Zinet/Core/ZtLogger.h"

class ZINET_GRAPHIC_LAYER_API ZtWindow
{
	static inline ZtLogger::SimpleConsoleLogger WindowLogger = ZtLogger::CreateSimpleConsoleLogger("ZtWindow");
	static inline ZtLogger::SimpleConsoleLogger OpenGLLogger = ZtLogger::CreateSimpleConsoleLogger("ZtOpenGLContext");

public:

	ZtWindow() = default;
	ZtWindow(const ZtWindow& Other) = default;
	ZtWindow(ZtWindow&& Other) = default;

	ZtWindow& operator = (const ZtWindow& Other) = default;
	ZtWindow& operator = (ZtWindow&& Other) = default;

	~ZtWindow() noexcept;

	void CreateWindow();

	GLFWwindow* GetInternalWindow();

	void InitStb();

	void SetViewport(int X, int Y, int Width, int Height);

	void SetClearColor(float Red, float Green, float Blue, float Alpha);

	void BindFramebufferSizeCallback();
	
	bool IsOpen();

	GLboolean ShouldBeClosed() const;

	void Clear();

	void SwapBuffers();

	static void FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height);

	static void OpenGLDebugOutput(GLenum Source, GLenum Type, GLuint Id, GLenum Severity,
		GLsizei Length, const GLchar* Message, const void* UserParam);

	static std::string GetSourceAsString(GLenum Source);

	static std::string GetTypeAsString(GLenum Type);

	static std::string GetSeverityAsString(GLenum Severity);

	ZtEvent* GetEvent();

protected:

	ZtGLContext GLContext;
	GLFWwindow* WindowPointer = nullptr;
	ZtEvent Event;

};