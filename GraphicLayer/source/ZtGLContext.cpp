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

bool ZtGLContext::InitOpenGL()
{
    return true;
}

void ZtGLContext::FillMode()
{

}

void ZtGLContext::PolygonOnlyMode()
{

}

void ZtGLContext::PointsMode()
{

}