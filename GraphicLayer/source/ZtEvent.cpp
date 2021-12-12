#include "Zinet/GraphicLayer/ZtEvent.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

namespace zt::gl
{

	void Event::setWindow(Window* window)
	{
		this->window = window;
		keyboard.setWindow(window);
		mouse.setWindow(window);
	}

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