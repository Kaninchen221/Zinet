#include "Zinet/GraphicLayer/ZtGLEvent.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"

namespace zt::gl
{

	void Event::setWindow(Window* newWindow)
	{
		window = newWindow;
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