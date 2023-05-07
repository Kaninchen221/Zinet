#pragma once

#include "ZtGraphicLayer.h"
#include "ZtGLContext.h"
#include "ZtGLEvent.h"
#include "ZtGLVecTypes.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Renderer;

	class ZINET_GRAPHIC_LAYER_API Window
	{
		inline static ConsoleLogger Logger = ConsoleLogger::Create("Window");
		static inline Renderer* RendererReference = nullptr;

	public:

		Window() = default;
		Window(const Window& other) = default;
		Window(Window&& other) = default;

		Window& operator = (const Window& other) = default;
		Window& operator = (Window&& other) = default;

		~Window() noexcept;

		void create();

		GLFWwindow* getInternal();

		const GLFWwindow* getInternal() const;

		void bindCallbacks();

		bool isOpen();

		bool shouldBeClosed() const;

		static void FramebufferSizeCallback(GLFWwindow* internalWindow, int width, int height);

		Event* getEvent();

		void setRenderer(Renderer& newRenderer) { RendererReference = &newRenderer; }

		Renderer* getRenderer() { return RendererReference; }

		Vector2i getSize() const;

		bool isMinimized() const;

		void requestCloseWindow();

	protected:

		GLFWwindow* internalWindow = nullptr;
		Event event;

		void bindFramebufferSizeCallback();
	};

}