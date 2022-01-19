#include "Zinet/GraphicLayer/ZtGLRenderer.h"

namespace zt::gl
{
    Renderer::Renderer()
    {
        GLFW::InitGLFW();
        instanceHelper.createApplicationInfo();
        instanceHelper.createInstanceCreateInfo();
        instanceHelper.createInstance(context);

        physicalDevice = instanceHelper.pickPhysicalDevice();
    }

    Renderer::~Renderer() noexcept
    {
        GLFW::DeinitGLFW();
    }

}