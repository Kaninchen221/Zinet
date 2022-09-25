#include "Zinet/GraphicLayer/ZtGLWindow.h"

namespace zt::gl
{

    Window::~Window() noexcept
    {
        WindowLogger->info(__FUNCTION__);

        if (internalWindow != nullptr)
        {
            glfwDestroyWindow(internalWindow);
        }
    }

    void Window::create()
    {
        WindowLogger->info(__FUNCTION__);

        internalWindow = glfwCreateWindow(800, 600, "Zinet", NULL, NULL);
        if (internalWindow == nullptr)
        {
            WindowLogger->error("Can't create window");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(internalWindow);

        glfwSetWindowUserPointer(internalWindow, this);

        event.setWindow(this);
        event.bindCallbacks();
    }

    GLFWwindow* Window::getInternal()
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

    }

    Event* Window::getEvent()
    {
        return &event;
    }

}