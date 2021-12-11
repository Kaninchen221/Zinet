#include "Zinet/GraphicLayer/ZtWindow.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace zt::gl
{

    Window::~Window() noexcept
    {
        WindowLogger->info(__FUNCTION__);

        if (WindowPointer != nullptr)
        {
            glfwDestroyWindow(WindowPointer);
        }

        GLContext.DeinitGLFW();
    }

    void Window::CreateWindow()
    {
        GLContext.InitGLFW();

        WindowLogger->info(__FUNCTION__);

        WindowPointer = glfwCreateWindow(800, 600, "Zinet", NULL, NULL);
        if (WindowPointer == nullptr)
        {
            WindowLogger->error("Can't create window");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(WindowPointer);

        glfwSetWindowUserPointer(WindowPointer, this);

        Event.SetWindow(this);
        Event.BindCallbacks();
    }

    GLFWwindow* Window::GetInternalWindow()
    {
        return WindowPointer;
    }

    void Window::SetViewport(int X, int Y, int Width, int Height)
    {

    }

    void Window::SetClearColor(float Red, float Green, float Blue, float Alpha)
    {

    }

    void Window::BindFramebufferSizeCallback()
    {
        glfwSetFramebufferSizeCallback(WindowPointer, &Window::FramebufferSizeCallback);
    }

    bool Window::IsOpen()
    {
        return !glfwWindowShouldClose(WindowPointer);
    }

    bool Window::ShouldBeClosed() const
    {
        return glfwWindowShouldClose(WindowPointer);
    }

    void Window::Clear()
    {

    }

    void Window::SwapBuffers()
    {
        glfwSwapBuffers(WindowPointer);
    }

    void Window::FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height)
    {

    }

    Event* Window::GetEvent()
    {
        return &Event;
    }

}