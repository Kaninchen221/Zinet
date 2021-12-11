#include "Zinet/GraphicLayer/ZtKeyboard.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

namespace zt::gl
{

	Keyboard::Keyboard()
	{
		Events = std::vector<KeyboardEvent>(1, KeyboardEvent());
	}

	void Keyboard::SetWindow(Window* newWindow)
	{
		window = newWindow;
	}

	const Window* Keyboard::GetWindow() const
	{
		return window;
	}

	const std::vector<KeyboardEvent>& Keyboard::GetEvents() const
	{
		return Events;
	}

	bool Keyboard::IsPressed(KeyboardKey Key) const
	{
		return glfwGetKey(window->GetInternalWindow(), static_cast<int>(Key)) == static_cast<int>(KeyboardEventType::Pressed);
	}

	bool Keyboard::IsReleased(KeyboardKey Key) const
	{
		return glfwGetKey(window->GetInternalWindow(), static_cast<int>(Key)) == static_cast<int>(KeyboardEventType::Released);
	}

	void Keyboard::BindCallbacks()
	{
		if (window == nullptr)
		{
			Logger->error("Can't bind callbacks when window is nullptr");
			return;
		}

		glfwSetKeyCallback(window->GetInternalWindow(), Keyboard::KeyCallback);
	}

	void Keyboard::KeyCallback(GLFWwindow* InternalWindow, int Key, int ScanCode, int Action, int Mods)
	{
		void* WindowUserPointer = glfwGetWindowUserPointer(InternalWindow);
		Window* GLWindow = static_cast<Window*>(WindowUserPointer);
		Event* Event = GLWindow->GetEvent();
		Keyboard* Keyboard = Event->GetKeyboard();

		Keyboard->Events.pop_back();

		KeyboardEvent KeyboardEvent;
		KeyboardEvent.Type = static_cast<KeyboardEventType>(Action);
		KeyboardEvent.Key = static_cast<KeyboardKey>(Key);
		Keyboard->Events.insert(Keyboard->Events.begin(), KeyboardEvent);
	}

	void Keyboard::SetMaximumRememberedEvents(size_t Value)
	{
		Events.resize(Value);
	}

	size_t Keyboard::GetMaximumRememberedEvents() const
	{
		return Events.size();
	}

}