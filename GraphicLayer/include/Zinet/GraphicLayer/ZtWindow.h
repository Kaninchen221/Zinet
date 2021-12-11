#pragma once

#include "ZtGraphicLayer.h"
#include "ZtGLContext.h"
#include "ZtEvent.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Window
	{
		static inline zt::Logger::SimpleConsoleLogger WindowLogger = zt::Logger::CreateSimpleConsoleLogger("Window");

	public:

		Window() = default;
		Window(const Window& Other) = default;
		Window(Window&& Other) = default;

		Window& operator = (const Window& Other) = default;
		Window& operator = (Window&& Other) = default;

		~Window() noexcept;

		void CreateWindow();

		GLFWwindow* GetInternalWindow();

		void InitStb();

		void SetViewport(int X, int Y, int Width, int Height);

		void SetClearColor(float Red, float Green, float Blue, float Alpha);

		void BindCallbacks();

		void BindFramebufferSizeCallback();

		bool IsOpen();

		bool ShouldBeClosed() const;

		void Clear();

		void SwapBuffers();

		static void FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height);

		Event* GetEvent();

	protected:

		Context GLContext;
		GLFWwindow* WindowPointer = nullptr;
		Event Event;

	};

}