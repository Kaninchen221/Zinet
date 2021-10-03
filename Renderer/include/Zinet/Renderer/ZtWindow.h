#pragma once

#include "ZtRenderer.h"

#include "Zinet/Core/ZtLogger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height);

class ZINET_RENDERER_API ZtWindow
{
	static inline ZtLogger::SimpleConsoleLogger Logger = ZtLogger::CreateSimpleConsoleLogger("ZtWindow");

public:

	ZtWindow() = default;
	ZtWindow(const ZtWindow& Other) = default;
	ZtWindow(ZtWindow&& Other) = default;

	ZtWindow& operator = (const ZtWindow& Other) = default;
	ZtWindow& operator = (ZtWindow&& Other) = default;

	~ZtWindow() noexcept;

	void InitGLFW();

	void CreateWindow();

	GLFWwindow* GetInternalWindow();

	void InitGLAD();

	void SetViewport(int X, int Y, int Width, int Height);

	void SetClearColor(float Red, float Green, float Blue, float Alpha);

	void BindFramebufferSizeCallback();
	
	bool IsOpen();

	void Clear();

	void SwapBuffers();

protected:

	GLFWwindow* WindowPointer = nullptr;

};