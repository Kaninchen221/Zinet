#include "..\include\Zinet\GraphicLayer\ZtEvent.h"

void ZtEvent::SetWindow(ZtWindow* Window)
{
	this->Window = Window;
	Keyboard.SetWindow(Window);
	Mouse.SetWindow(Window);
}

const ZtWindow* ZtEvent::GetWindow() const
{
	return Window;
}

void ZtEvent::PollEvents()
{
	glfwPollEvents();
}

ZtKeyboard* ZtEvent::GetKeyboard()
{
	return &Keyboard;
}

ZtMouse* ZtEvent::GetMouse()
{
	return &Mouse;
}

void ZtEvent::BindCallbacks()
{
	Keyboard.BindCallbacks();
	Mouse.BindCallbacks();
}
