#include "Zinet/GraphicLayer/ZtMouse.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

ZtMouse::ZtMouse()
{
	ButtonsEvents = std::vector<ZtMouseButtonEvent>(1, ZtMouseButtonEvent());
}

void ZtMouse::SetWindow(ZtWindow* Window)
{
	InternalWindow = Window;
}

const ZtWindow* ZtMouse::GetWindow() const
{
	return InternalWindow;
}

const std::vector<ZtMouseButtonEvent>& ZtMouse::GetButtonsEvents() const
{
	return ButtonsEvents;
}

void ZtMouse::SetMaximumRememberedButtonsEvents(size_t Size)
{
	ButtonsEvents.resize(Size);
}

size_t ZtMouse::GetMaximumRememberedButtonsEvents() const
{
	return ButtonsEvents.size();
}

void ZtMouse::ButtonCallback(GLFWwindow* Window, ZtInt Button, ZtInt Action, ZtInt Mods)
{
	void* WindowUserPointer = glfwGetWindowUserPointer(Window);
	ZtWindow* GLWindow = static_cast<ZtWindow*>(WindowUserPointer);
	ZtEvent* Event = GLWindow->GetEvent();
	ZtMouse* Mouse = Event->GetMouse();

	Mouse->ButtonsEvents.pop_back();

	ZtMouseButtonEvent ButtonEvent;
	ButtonEvent.Type = static_cast<ZtMouseButtonEventType>(Action);
	ButtonEvent.Button = static_cast<ZtMouseButton>(Button);
	Mouse->ButtonsEvents.insert(Mouse->ButtonsEvents.begin(), ButtonEvent);
}

void ZtMouse::BindCallbacks()
{
	glfwSetMouseButtonCallback(InternalWindow->GetInternalWindow(), &ZtMouse::ButtonCallback);
}
