#include "Zinet/Window/ZtEvent.h"

namespace zt::wd
{
	const Window* Event::getWindow() const
	{
		return window;
	}

	void Event::pollEvents()
	{
		glfwPollEvents();
	}

	Keyboard* Event::getKeyboard()
	{
		return &keyboard;
	}

	Mouse* Event::getMouse()
	{
		return &mouse;
	}

	void Event::bindCallbacks()
	{
		keyboard.bindCallbacks();
		mouse.bindCallbacks();
	}

}