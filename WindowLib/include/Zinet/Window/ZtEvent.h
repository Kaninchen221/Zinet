#pragma once

#include "Zinet/Window/ZtKeyboard.h"
#include "Zinet/Window/ZtMouse.h"

namespace zt::wd
{
	class Window;

	class Event
	{

	public:

		Event() = delete;
		Event(Window& newWindow) : window{ &newWindow }, keyboard{ newWindow }, mouse{ newWindow } {}
		Event(const Event& other) = default;
		Event(Event&& other) = default;

		Event& operator = (const Event& other) = default;
		Event& operator = (Event&& other) = default;

		~Event() noexcept = default;

		const Window* getWindow() const;

		void pollEvents();

		Keyboard& getKeyboard() { return keyboard; }
		const Keyboard& getKeyboard() const { return keyboard; }

		Mouse& getMouse() { return mouse; }
		const Mouse& getMouse() const { return mouse; }

		void bindCallbacks();

	protected:

		Window* window = nullptr;
		Keyboard keyboard;
		Mouse mouse;

	};

}