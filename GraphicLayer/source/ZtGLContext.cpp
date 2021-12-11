#include "Zinet/GraphicLayer/ZtGLContext.h"

namespace zt::gl
{

    Context::~Context() noexcept
    {
    }

    bool Context::InitGLFW()
    {
        if (glfwInit())
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

    void Context::DeinitGLFW()
    {
        glfwTerminate();
    }

    bool Context::InitOpenGL()
    {
        return true;
    }

    void Context::FillMode()
    {

    }

    void Context::PolygonOnlyMode()
    {

    }

    void Context::PointsMode()
    {

    }

}