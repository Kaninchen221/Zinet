#include "Zinet/GraphicLayer/ZtGLGLFW.h"

namespace zt::gl
{
    bool GLFW::InitGLFW()
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

    void GLFW::DeinitGLFW()
    {
        glfwTerminate();
    }
}