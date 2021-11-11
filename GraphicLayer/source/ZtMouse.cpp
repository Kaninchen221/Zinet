#include "Zinet/GraphicLayer/ZtMouse.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

ZtMouse::ZtMouse()
{
	ButtonsEvents = std::vector<ZtMouseButtonEvent>(1, ZtMouseButtonEvent());
	PositionEvents = std::vector<ZtMousePositionEvent>(1, ZtMousePositionEvent());
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

void ZtMouse::SetMaxRememberedButtonsEvents(size_t Size)
{
	ButtonsEvents.resize(Size);
}

size_t ZtMouse::GetMaxRememberedButtonsEvents() const
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
	glfwSetCursorPosCallback(InternalWindow->GetInternalWindow(), &ZtMouse::PositionCallback);
}

void ZtMouse::PositionCallback(GLFWwindow* Window, ZtDouble PositionX, ZtDouble PositionY)
{
	void* WindowUserPointer = glfwGetWindowUserPointer(Window);
	ZtWindow* GLWindow = static_cast<ZtWindow*>(WindowUserPointer);
	ZtEvent* Event = GLWindow->GetEvent();
	ZtMouse* Mouse = Event->GetMouse();

	Mouse->PositionEvents.pop_back();

	ZtMousePositionEvent PositionEvent;
	PositionEvent.Position = glm::dvec2(PositionX, PositionY);
	Mouse->PositionEvents.insert(Mouse->PositionEvents.begin(), PositionEvent);
}

const std::vector<ZtMousePositionEvent>& ZtMouse::GetPositionEvents() const
{
	return PositionEvents;
}

void ZtMouse::SetMaxRememberedPositionEvents(size_t Size)
{
	PositionEvents.resize(Size);
}

size_t ZtMouse::GetMaxRememberedPositionEvents() const
{
	return PositionEvents.size();
}
