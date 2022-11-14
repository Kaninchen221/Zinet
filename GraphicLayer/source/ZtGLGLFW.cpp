#include "Zinet/GraphicLayer/ZtGLGLFW.h"

namespace zt::gl
{
    bool GLFW::Init(bool hideWindow)
    {
        if (glfwInit())
        {
            Logger->info("Succesfull initialize GLFW");

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Don't create OpenGL context
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

            if (hideWindow)
            {
                HideWindow();
            }

            return true;
        }
        else
        {
            Logger->error("Failed initialize glfw");
            return false;
        }
    }

    void GLFW::Deinit()
    {
        glfwTerminate();
    }

    void GLFW::HideWindow()
    {
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    }

    void GLFW::UnhideWindow()
    {
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    }
}