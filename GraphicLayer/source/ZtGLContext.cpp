#include "Zinet/GraphicLayer/ZtGLContext.h"

namespace zt::gl
{

    Context::~Context() noexcept
    {
    }

    bool Context::initGLFW()
    {
        if (glfwInit())
        {
            Logger->info("Succesfull initialize GLFW");

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Don't create OpenGL context
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

            return true;
        }
        else
        {
            Logger->error("Failed initialize glfw");
            return false;
        }

        return false;
    }

    void Context::deinitGLFW()
    {
        glfwTerminate();
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