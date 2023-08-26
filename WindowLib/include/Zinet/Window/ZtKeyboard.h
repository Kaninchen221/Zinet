#pragma once

#include "Zinet/Window/ZtKeyboardEvent.h"

#include "Zinet/Core/ZtLogger.h"

#include <vector>

namespace zt::wd
{

	class Window;

	class Keyboard
	{
		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Keyboard");

	public:

		Keyboard();
		Keyboard(const Keyboard& other) = default;
		Keyboard(Keyboard&& other) = default;

		Keyboard& operator = (const Keyboard& other) = default;
		Keyboard& operator = (Keyboard&& other) = default;

		~Keyboard() noexcept = default;

		void setWindow(Window* newWindow);

		const Window* getWindow() const;

		const std::vector<KeyboardEvent>& getEvents() const;

		bool isPressed(KeyboardKey key) const;

		bool isReleased(KeyboardKey key) const;

		void setMaximumRememberedEvents(size_t value);

		size_t getMaximumRememberedEvents() const;

		static void KeyCallback(GLFWwindow* internalWindow, int key, int scanCode, int action, int mods);

		void bindCallbacks();

	protected:

		Window* window = nullptr;
		std::vector<KeyboardEvent> events;

	};

}