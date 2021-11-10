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

    GLContext.InitGLAD();
    GLContext.InitOpenGL();

    Event.SetWindow(this);
    Event.BindCallbacks();
}

GLFWwindow* ZtWindow::GetInternalWindow()
{
	return WindowPointer;
}

void ZtWindow::InitStb()
{
    stbi_set_flip_vertically_on_load(true);
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
    glfwSetFramebufferSizeCallback(WindowPointer, &ZtWindow::FramebufferSizeCallback);
}

bool ZtWindow::IsOpen()
{
    return !glfwWindowShouldClose(WindowPointer);
}

GLboolean ZtWindow::ShouldBeClosed() const
{
    return glfwWindowShouldClose(WindowPointer);
}

void ZtWindow::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void ZtWindow::SwapBuffers()
{
    glfwSwapBuffers(WindowPointer);
}

void ZtWindow::FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height)
{
    // TODO: Temporary fix
    glfwGetFramebufferSize(Window, &Width, &Height);
    glViewport(0, 0, Width, Height);
}

void ZtWindow::OpenGLDebugOutput(GLenum Source, GLenum Type, GLuint Id, GLenum Severity,
    GLsizei Length, const GLchar* Message, const void* UserParam)
{
    std::string SourceAsString = GetSourceAsString(Source);
    std::string TypeAsString = GetTypeAsString(Type);
    std::string SeverityAsString = GetSeverityAsString(Severity);

    if (Severity == GL_DEBUG_SEVERITY_NOTIFICATION)
    {
        OpenGLLogger->info("{} : {} : {} : {} : {}", SourceAsString, TypeAsString, Id, SeverityAsString, Message);
    }
    else
    {
        OpenGLLogger->error("{} : {} : {} : {} : {}", SourceAsString, TypeAsString, Id, SeverityAsString, Message);
    }
}

std::string ZtWindow::GetSourceAsString(GLenum Source)
{
    switch (Source)
    {
    case GL_DEBUG_SOURCE_API:
        return "GL_DEBUG_SOURCE_API";
        break;

    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
        break;

    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        return "GL_DEBUG_SOURCE_SHADER_COMPILER";
        break;

    case GL_DEBUG_SOURCE_THIRD_PARTY:
        return "GL_DEBUG_SOURCE_THIRD_PARTY";
        break;

    case GL_DEBUG_SOURCE_APPLICATION:
        return "GL_DEBUG_SOURCE_APPLICATION";
        break;

    case GL_DEBUG_SOURCE_OTHER:
        return "GL_DEBUG_SOURCE_OTHER";
        break;

    default:
        return "UNKNOWN_GL_DEBUG_SOURCE";
    }
}

std::string ZtWindow::GetTypeAsString(GLenum Type)
{
    switch (Type)
    {
    case GL_DEBUG_TYPE_ERROR:
        return "GL_DEBUG_TYPE_ERROR";
        break;

    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_PORTABILITY:
        return "GL_DEBUG_TYPE_PORTABILITY";
        break;

    case GL_DEBUG_TYPE_PERFORMANCE:
        return "GL_DEBUG_TYPE_PERFORMANCE";
        break;

    case GL_DEBUG_TYPE_MARKER:
        return "GL_DEBUG_TYPE_MARKER";
        break;

    case GL_DEBUG_TYPE_PUSH_GROUP:
        return "GL_DEBUG_TYPE_PUSH_GROUP";
        break;

    case GL_DEBUG_TYPE_POP_GROUP:
        return "GL_DEBUG_TYPE_POP_GROUP";
        break;

    case GL_DEBUG_TYPE_OTHER:
        return "GL_DEBUG_TYPE_OTHER";
        break;

    default:
        return "UNKNOWN_GL_DEBUG_TYPE";
    }
}

std::string ZtWindow::GetSeverityAsString(GLenum Severity)
{
    switch (Severity)
    {
    case GL_DEBUG_SEVERITY_LOW:
        return "GL_DEBUG_SEVERITY_LOW";
        break;

    case GL_DEBUG_SEVERITY_MEDIUM:
        return "GL_DEBUG_SEVERITY_MEDIUM";
        break;

    case GL_DEBUG_SEVERITY_HIGH:
        return "GL_DEBUG_SEVERITY_HIGH";
        break;

    case GL_DEBUG_SEVERITY_NOTIFICATION:
        return "GL_DEBUG_SEVERITY_NOTIFICATION";
        break;

    default:
        return "UNKNOWN_GL_DEBUG_SEVERITY";
    }
}

ZtEvent* ZtWindow::GetEvent()
{
    return &Event;
}
