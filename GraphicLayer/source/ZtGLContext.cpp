#include "Zinet/GraphicLayer/ZtGLContext.h"

ZtGLContext::~ZtGLContext() noexcept
{
}

bool ZtGLContext::InitGLFW()
{
    if(glfwInit())
    {
        Logger->info("Succesfull initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

        return true;
    }
    else
    {
        Logger->error("Failed initialize glfw");
        return false;
    }

    return false;
}

void ZtGLContext::DeinitGLFW()
{
    glfwTerminate();
}

bool ZtGLContext::InitGLAD()
{
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger->info("Succesfull initialize glad");
        return true;
    }
    else
    {
        Logger->error("Failed initialize glad");
        return false;
    }
}

bool ZtGLContext::InitOpenGL()
{
    GLint Flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &Flags);

    if (Flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(&ZtGLContext::OpenGLDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

        Logger->info("Succesfull init OpenGL Debug Context");
    }
    else
    {
        Logger->error("Can't initialize OpenGL Debug Context");
        return false;
    }
}

void ZtGLContext::FillMode()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ZtGLContext::PolygonOnlyMode()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void ZtGLContext::PointsMode()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}

void ZtGLContext::OpenGLDebugOutput(GLenum Source, GLenum Type, GLuint Id, GLenum Severity, GLsizei Length, const GLchar* Message, const void* UserParam)
{
    std::string SourceAsString = GetSourceAsString(Source);
    std::string TypeAsString = GetTypeAsString(Type);
    std::string SeverityAsString = GetSeverityAsString(Severity);

    if (Severity == GL_DEBUG_SEVERITY_NOTIFICATION)
    {
        Logger->info("{} : {} : {} : {} : {}", SourceAsString, TypeAsString, Id, SeverityAsString, Message);
    }
    else
    {
        Logger->error("{} : {} : {} : {} : {}", SourceAsString, TypeAsString, Id, SeverityAsString, Message);
    }
}

std::string ZtGLContext::GetSourceAsString(GLenum Source)
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

std::string ZtGLContext::GetTypeAsString(GLenum Type)
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

std::string ZtGLContext::GetSeverityAsString(GLenum Severity)
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
