#include "Zinet/Window/ZtGLFW.h"

#include <GLFW/glfw3.h>

namespace zt::wd
{
    bool GLFW::Init(bool hideWindow)
    {
        if (glfwInit())
        {
            Logger->info("Succesfull initialize GLFW");

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Don't create OpenGL context
            glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

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
		Logger->info("Terminate GLFW");
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