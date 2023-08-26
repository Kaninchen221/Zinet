#pragma once

#include "Zinet/Window/ZtEvent.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::window
{
	class Renderer;

	class Window
	{
		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Window");

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

		zt::math::Vector2ui getSize() const;

		bool isMinimized() const;

		void requestCloseWindow();

	protected:

		GLFWwindow* internalWindow = nullptr;
		Event event;

		void bindFramebufferSizeCallback();
	};

}