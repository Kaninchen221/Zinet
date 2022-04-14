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
		Window(const Window& other) = default;
		Window(Window&& other) = default;

		Window& operator = (const Window& other) = default;
		Window& operator = (Window&& other) = default;

		~Window() noexcept;

		void create();

		GLFWwindow* getInternal();

		void initStb();

		void setViewport(int x, int y, int width, int height);

		void setClearColor(float red, float green, float blue, float alpha);

		void bindCallbacks();

		void bindFramebufferSizeCallback();

		bool isOpen();

		bool shouldBeClosed() const;

		void clear();

		void swapBuffers();

		static void FramebufferSizeCallback(GLFWwindow* internalWindow, int width, int height);

		Event* getEvent();

	protected:

		Context context;
		GLFWwindow* internalWindow = nullptr;
		Event event;

	};

}