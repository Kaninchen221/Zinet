#pragma once

#include "Zinet/Window/ZtEvent.h"
#include "Zinet/Window/ZtGLFW.h"
#include "Zinet/Window/ZtVecTypes.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::wd
{
	class Window
	{
	public:

		using WindowResizedCallback = std::function<void(void*, const Vector2ui&)>;

	private:

		inline static core::ConsoleLogger Logger = core::ConsoleLogger::Create("Window");

		inline static WindowResizedCallback WindowResizedCallbackPointer = nullptr;
		inline static void* WindowResizedCallbackUserPointer = nullptr;

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

		zt::Vector2ui getSize() const;

		bool isMinimized() const;

		void requestCloseWindow();

		static void SetWindowResizedCallback(void* userPointer, WindowResizedCallback callback);

		static WindowResizedCallback GetWindowResizedCallback() { return WindowResizedCallbackPointer; }

		static void* GetWindowResizedCallbackUserPointer() { return WindowResizedCallbackUserPointer; }

	protected:

		GLFWwindow* internalWindow{};
		Event event;

		void bindFramebufferSizeCallback();
	};

	inline void Window::SetWindowResizedCallback(void* userPointer, WindowResizedCallback callback)
	{
		if (userPointer && callback)
		{
			WindowResizedCallbackPointer = callback;
			WindowResizedCallbackUserPointer = userPointer;
		}
		else
		{
			Logger->error("Can't bind user pointer: {} : Is callback valid: {}", userPointer, callback.operator bool());
		}
	}
}