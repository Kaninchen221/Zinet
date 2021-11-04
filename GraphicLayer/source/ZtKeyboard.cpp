#include "Zinet/GraphicLayer/ZtKeyboard.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

ZtKeyboard::ZtKeyboard()
{
	Events = std::vector<ZtKeyboardEvent>(MaximumRememberedEvents);
}

void ZtKeyboard::SetWindow(ZtWindow* Window)
{
	this->Window = Window;

	BindCallbacks();
}

const ZtWindow* ZtKeyboard::GetWindow() const
{
	return Window;
}

const ZtKeyboardEvent& ZtKeyboard::GetLastEvent() const
{
	return Events[0];
}

void ZtKeyboard::SetLastEvent(const ZtKeyboardEvent& Event)
{
	Events[0] = Event;
}

const ZtKeyboardEvent& ZtKeyboard::GetPreviousEvent() const
{
	return Events[1];
}

void ZtKeyboard::SetPreviousEvent(const ZtKeyboardEvent& Event)
{
	Events[1] = Event;
}

const std::vector<ZtKeyboardEvent>& ZtKeyboard::GetEvents() const
{
	return Events;
}

ZtBool ZtKeyboard::IsPressed(ZtKeyboardKey Key) const
{
	return glfwGetKey(Window->GetInternalWindow(), static_cast<int>(Key)) == static_cast<ZtInt>(ZtKeyboardEventType::Pressed);
}

ZtBool ZtKeyboard::IsReleased(ZtKeyboardKey Key) const
{
	return glfwGetKey(Window->GetInternalWindow(), static_cast<int>(Key)) == static_cast<ZtInt>(ZtKeyboardEventType::Released);
}

void ZtKeyboard::BindCallbacks()
{
	if (Window == nullptr)
	{
		Logger->error("Can't bind callbacks when window is nullptr");
		return;
	}

	glfwSetKeyCallback(Window->GetInternalWindow(), ZtKeyboard::KeyCallback);
}

void ZtKeyboard::KeyCallback(GLFWwindow* InternalWindow, int Key, int ScanCode, int Action, int Mods)
{
	void* WindowUserPointer = glfwGetWindowUserPointer(InternalWindow);
	ZtWindow* GLWindow = static_cast<ZtWindow*>(WindowUserPointer);
	ZtEvent* Event = GLWindow->GetEvent();
	ZtKeyboard* Keyboard = Event->GetKeyboard();
	
	Keyboard->Events.pop_back();
	
	ZtKeyboardEvent KeyboardEvent;
	KeyboardEvent.Type = static_cast<ZtKeyboardEventType>(Action);
	KeyboardEvent.Key = static_cast<ZtKeyboardKey>(Key);
	Keyboard->Events.insert(Keyboard->Events.begin(), KeyboardEvent);
}

void ZtKeyboard::SetMaximumRememberedEvents(ZtSize Value)
{
	MaximumRememberedEvents = Value;
	Events.resize(MaximumRememberedEvents);
}

ZtSize ZtKeyboard::GetMaximumRememberedEvents() const
{
	return MaximumRememberedEvents;
}
