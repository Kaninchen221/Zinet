#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtKeyboardEvent.h"

#include "Zinet/Core/ZtLogger.h"

#include <vector>

namespace zt::gl
{

	class Window;

	class ZINET_GRAPHIC_LAYER_API Keyboard
	{
		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Keyboard");

	public:

		Keyboard();
		Keyboard(const Keyboard& Other) = default;
		Keyboard(Keyboard&& Other) = default;

		Keyboard& operator = (const Keyboard& Other) = default;
		Keyboard& operator = (Keyboard&& Other) = default;

		~Keyboard() noexcept = default;

		void SetWindow(Window* newWindow);

		const Window* GetWindow() const;

		const std::vector<KeyboardEvent>& GetEvents() const;

		bool IsPressed(KeyboardKey Key) const;

		bool IsReleased(KeyboardKey Key) const;

		void SetMaximumRememberedEvents(size_t Value);

		size_t GetMaximumRememberedEvents() const;

		static void KeyCallback(GLFWwindow* InternalWindow, int Key, int ScanCode, int Action, int Mods);

		void BindCallbacks();

	protected:

		Window* window = nullptr;
		std::vector<KeyboardEvent> Events;

	};

}