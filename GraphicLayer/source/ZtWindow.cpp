#include "Zinet/GraphicLayer/ZtWindow.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

ZtWindow::~ZtWindow() noexcept
{
    WindowLogger->info(__FUNCTION__);

    if (WindowPointer != nullptr)
    {
        glfwDestroyWindow(WindowPointer);
    }

    GLContext.DeinitGLFW();
}

void ZtWindow::CreateWindow()
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

GLFWwindow* ZtWindow::GetInternalWindow()
{
	return WindowPointer;
}

void ZtWindow::SetViewport(int X, int Y, int Width, int Height)
{

}

void ZtWindow::SetClearColor(float Red, float Green, float Blue, float Alpha)
{

}

void ZtWindow::BindFramebufferSizeCallback()
{
    glfwSetFramebufferSizeCallback(WindowPointer, &ZtWindow::FramebufferSizeCallback);
}

bool ZtWindow::IsOpen()
{
    return !glfwWindowShouldClose(WindowPointer);
}

bool ZtWindow::ShouldBeClosed() const
{
    return glfwWindowShouldClose(WindowPointer);
}

void ZtWindow::Clear()
{

}

void ZtWindow::SwapBuffers()
{
    glfwSwapBuffers(WindowPointer);
}

void ZtWindow::FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height)
{

}

ZtEvent* ZtWindow::GetEvent()
{
    return &Event;
}
