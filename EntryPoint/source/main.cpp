#include "ZtVulkanHelloTriangle.h"

#include "Zinet/GraphicLayer/ZtWindow.h"

int main()
{

	zt::gl::Window window;
	window.createWindow();

	while (!window.shouldBeClosed())
	{
		window.clear();

        zt::gl::Event* Event = window.getEvent();
        Event->pollEvents();

        zt::gl::Keyboard* Keyboard = Event->getKeyboard();
        zt::gl::Mouse* Mouse = Event->getMouse();

        if (Keyboard->isPressed(zt::gl::KeyboardKey::ESCAPE))
        {
            GLFWwindow* WindowPointer = window.getInternalWindow();
            glfwSetWindowShouldClose(WindowPointer, true);
        }


		window.swapBuffers();
	}

    return 0;
}