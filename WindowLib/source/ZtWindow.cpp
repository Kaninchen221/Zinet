#include "Zinet/Window/ZtWindow.h"

#include "Zinet/Core/ZtDebug.h"

#include <type_traits>

namespace zt::wd
{

    Window::~Window() noexcept
    {
        Logger->info(zt::core::CurrentFunctionName());

        if (internalWindow != nullptr)
        {
            glfwDestroyWindow(internalWindow);
        }
    }

    void Window::create()
    {
        Logger->info(zt::core::CurrentFunctionName());

        internalWindow = glfwCreateWindow(800, 600, "Zinet", NULL, NULL);
        if (internalWindow == nullptr)
        {
            Logger->error("Can't create window");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(internalWindow);

        glfwSetWindowUserPointer(internalWindow, this);

        // Window must be always at least bigger as 1 x 1 because of the swap chain
        glfwSetWindowSizeLimits(internalWindow, 1, 1, GLFW_DONT_CARE, GLFW_DONT_CARE);

		bindFramebufferSizeCallback();
    }

    GLFWwindow* Window::getInternal()
    {
        return internalWindow;
    }

    const GLFWwindow* Window::getInternal() const
    {
        return internalWindow;
    }

    void Window::bindCallbacks()
    {
        event.bindCallbacks();
    }

    void Window::bindFramebufferSizeCallback()
    {
        glfwSetFramebufferSizeCallback(internalWindow, &Window::FramebufferSizeCallback);
    }

    bool Window::isOpen()
    {
        return !glfwWindowShouldClose(internalWindow);
    }

    bool Window::shouldBeClosed() const
    {
        return glfwWindowShouldClose(internalWindow);
    }

    void Window::FramebufferSizeCallback(GLFWwindow* internalWindow, int width, int height)
    {
        void* windowUserPointer = glfwGetWindowUserPointer(internalWindow);
        if (windowUserPointer == nullptr)
        {
            Logger->warn("Window::FramebufferSizeCallback: windowUserPointer is nullptr");
            return;
        }

        Window* window = static_cast<Window*>(windowUserPointer);
		if (window->windowResizedCallbackPointer && window->windowResizedCallbackUserPointer)
		{
            auto callable = std::bind(window->windowResizedCallbackPointer, window->windowResizedCallbackUserPointer, Vector2ui{width, height});
			std::invoke(callable);
		}
    }

    Vector2ui Window::getSize() const
	{
        int width = 0;
        int height = 0;
		glfwGetFramebufferSize(internalWindow, &width, &height);
        return { width, height };
	}

	bool Window::isMinimized() const
	{
        Vector2i windowSize = getSize();
        return windowSize.x == 0 && windowSize.y == 0;
	}

	void Window::requestCloseWindow()
	{
        glfwSetWindowShouldClose(internalWindow, true);
	}

}