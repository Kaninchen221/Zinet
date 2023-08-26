#include "Zinet/Window/ZtWindow.h"

#include "Zinet/Core/ZtDebug.h"

namespace zt::window
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

        event.setWindow(this);
        event.bindCallbacks();
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
//         if (RendererReference != nullptr)
//             RendererReference->informAboutWindowResize(width, height);
    }

    Event* Window::getEvent()
    {
        return &event;
    }

    zt::math::Vector2ui Window::getSize() const
	{
        int width = 0;
        int height = 0;
		glfwGetFramebufferSize(internalWindow, &width, &height);
        return { width, height };
	}

	bool Window::isMinimized() const
	{
        zt::math::Vector2i windowSize = getSize();
        return windowSize.x == 0 && windowSize.y == 0;
	}

	void Window::requestCloseWindow()
	{
        glfwSetWindowShouldClose(internalWindow, true);
	}

}