#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtMousePositionEvent.h"
#include "Zinet/GraphicLayer/ZtMouseButtonEvent.h"

#include <vector>

namespace zt::gl
{

	class Window;

	class ZINET_GRAPHIC_LAYER_API Mouse
	{

	public:

		Mouse();
		Mouse(const Mouse& Other) = default;
		Mouse(Mouse&& Other) = default;

		Mouse& operator = (const Mouse& Other) = default;
		Mouse& operator = (Mouse&& Other) = default;

		~Mouse() noexcept = default;

		void SetWindow(Window* window);

		const Window* GetWindow() const;

		const std::vector<MouseButtonEvent>& GetButtonsEvents() const;

		void SetMaxRememberedButtonsEvents(size_t Size);

		size_t GetMaxRememberedButtonsEvents() const;

		static void ButtonCallback(GLFWwindow* Window, int Button, int Action, int Mods);

		void BindCallbacks();

		static void PositionCallback(GLFWwindow* glfwWindow, double PositionX, double PositionY);

		const std::vector<MousePositionEvent>& GetPositionEvents() const;

		void SetMaxRememberedPositionEvents(size_t Size);

		size_t GetMaxRememberedPositionEvents() const;

	protected:

		Window* InternalWindow = nullptr;
		std::vector<MouseButtonEvent> ButtonsEvents;
		std::vector<MousePositionEvent> PositionEvents;

	};

}