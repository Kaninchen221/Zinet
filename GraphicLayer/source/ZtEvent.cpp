#include "Zinet/GraphicLayer/ZtEvent.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

namespace zt::gl
{

	void Event::SetWindow(Window* NewWindow)
	{
		WindowPointer = NewWindow;
		Keyboard.SetWindow(NewWindow);
		Mouse.SetWindow(NewWindow);
	}

	const Window* Event::GetWindow() const
	{
		return WindowPointer;
	}

	void Event::PollEvents()
	{
		glfwPollEvents();
	}

	Keyboard* Event::GetKeyboard()
	{
		return &Keyboard;
	}

	Mouse* Event::GetMouse()
	{
		return &Mouse;
	}

	void Event::BindCallbacks()
	{
		Keyboard.BindCallbacks();
		Mouse.BindCallbacks();
	}

}