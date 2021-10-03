#include "Zinet/Renderer/ZtWindow.h"

void FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height)
{

}

ZtWindow::~ZtWindow() noexcept
{
    Logger->info(__FUNCTION__);

    glfwTerminate();
}

void ZtWindow::InitGLFW()
{
    Logger->info(__FUNCTION__);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void ZtWindow::CreateWindow()
{
    Logger->info(__FUNCTION__);

    WindowPointer = glfwCreateWindow(800, 600, "Zinet", NULL, NULL);
    if (WindowPointer == nullptr)
    {
        Logger->error("Can't create window");
        glfwTerminate();
    }

    glfwMakeContextCurrent(WindowPointer);
}

GLFWwindow* ZtWindow::GetInternalWindow()
{
	return WindowPointer;
}

void ZtWindow::InitGLAD()
{
    Logger->info(__FUNCTION__);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger->error("Can't initialize glad");
    }
}

void ZtWindow::SetViewport(int X, int Y, int Width, int Height)
{
    glViewport(X, Y, Width, Height);
}

void ZtWindow::SetClearColor(float Red, float Green, float Blue, float Alpha)
{
    glClearColor(Red, Green, Blue, Alpha);
}

void ZtWindow::BindFramebufferSizeCallback()
{
    glfwSetFramebufferSizeCallback(WindowPointer, FramebufferSizeCallback);
}

bool ZtWindow::IsOpen()
{
    return !glfwWindowShouldClose(WindowPointer);
}

void ZtWindow::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void ZtWindow::SwapBuffers()
{
    glfwSwapBuffers(WindowPointer);
}
