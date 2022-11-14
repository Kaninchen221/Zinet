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
		Mouse(const Mouse& other) = default;
		Mouse(Mouse&& other) = default;

		Mouse& operator = (const Mouse& other) = default;
		Mouse& operator = (Mouse&& other) = default;

		~Mouse() noexcept = default;

		void setWindow(Window* newWindow);

		const Window* getWindow() const;

		const std::vector<MouseButtonEvent>& getButtonsEvents() const;

		void setMaxRememberedButtonsEvents(size_t size);

		size_t getMaxRememberedButtonsEvents() const;

		static void ButtonCallback(GLFWwindow* internalWindow, int button, int action, int mods);

		void bindCallbacks();

		static void PositionCallback(GLFWwindow* internalWindow, double positionX, double positionY);

		const std::vector<MousePositionEvent>& getPositionEvents() const;

		void setMaxRememberedPositionEvents(size_t size);

		size_t getMaxRememberedPositionEvents() const;

	protected:

		Window* window = nullptr;
		std::vector<MouseButtonEvent> buttonsEvents;
		std::vector<MousePositionEvent> positionEvents;

	};

}