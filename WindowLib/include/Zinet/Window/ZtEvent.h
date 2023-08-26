#pragma once

#include "Zinet/Window/ZtKeyboard.h"
#include "Zinet/Window/ZtMouse.h"

namespace zt::window
{
	class Window;

	class Event
	{

	public:

		void setWindow(Window* newWindow);

		const Window* getWindow() const;

		void pollEvents();

		Keyboard* getKeyboard();

		Mouse* getMouse();

		void bindCallbacks();

	protected:

		Window* window = nullptr;
		Keyboard keyboard;
		Mouse mouse;

	};

}