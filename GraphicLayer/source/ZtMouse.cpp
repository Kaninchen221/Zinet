#include "Zinet/GraphicLayer/ZtMouse.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

namespace zt::gl
{

	Mouse::Mouse()
	{
		ButtonsEvents = std::vector<MouseButtonEvent>(1, MouseButtonEvent());
		PositionEvents = std::vector<MousePositionEvent>(1, MousePositionEvent());
	}

	void Mouse::SetWindow(Window* window)
	{
		InternalWindow = window;
	}

	const Window* Mouse::GetWindow() const
	{
		return InternalWindow;
	}

	const std::vector<MouseButtonEvent>& Mouse::GetButtonsEvents() const
	{
		return ButtonsEvents;
	}

	void Mouse::SetMaxRememberedButtonsEvents(size_t Size)
	{
		ButtonsEvents.resize(Size);
	}

	size_t Mouse::GetMaxRememberedButtonsEvents() const
	{
		return ButtonsEvents.size();
	}

	void Mouse::ButtonCallback(GLFWwindow* glfwWindow, int Button, int Action, int Mods)
	{
		void* WindowUserPointer = glfwGetWindowUserPointer(glfwWindow);
		Window* GLWindow = static_cast<Window*>(WindowUserPointer);
		Event* Event = GLWindow->GetEvent();
		Mouse* Mouse = Event->GetMouse();

		Mouse->ButtonsEvents.pop_back();

		MouseButtonEvent ButtonEvent;
		ButtonEvent.Type = static_cast<MouseButtonEventType>(Action);
		ButtonEvent.Button = static_cast<MouseButton>(Button);
		Mouse->ButtonsEvents.insert(Mouse->ButtonsEvents.begin(), ButtonEvent);
	}

	void Mouse::BindCallbacks()
	{
		glfwSetMouseButtonCallback(InternalWindow->GetInternalWindow(), &Mouse::ButtonCallback);
		glfwSetCursorPosCallback(InternalWindow->GetInternalWindow(), &Mouse::PositionCallback);
	}

	void Mouse::PositionCallback(GLFWwindow* glfwWindow, double PositionX, double PositionY)
	{
		Window* windowUserPointer = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
		Event* Event = windowUserPointer->GetEvent();
		Mouse* Mouse = Event->GetMouse();

		Mouse->PositionEvents.pop_back();

		MousePositionEvent PositionEvent;
		PositionEvent.Position = glm::dvec2(PositionX, PositionY);
		Mouse->PositionEvents.insert(Mouse->PositionEvents.begin(), PositionEvent);
	}

	const std::vector<MousePositionEvent>& Mouse::GetPositionEvents() const
	{
		return PositionEvents;
	}

	void Mouse::SetMaxRememberedPositionEvents(size_t Size)
	{
		PositionEvents.resize(Size);
	}

	size_t Mouse::GetMaxRememberedPositionEvents() const
	{
		return PositionEvents.size();
	}

}