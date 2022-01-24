#include "Zinet/GraphicLayer/ZtGLRenderer.h"

namespace zt::gl
{
    Renderer::Renderer()
    {
        GLFW::InitGLFW();

        instance.createApplicationInfo();
        instance.createInstanceCreateInfo();
        instance.createInstance(context);

        debugUtilsMessenger.createDebugUtilsMessenger(instance);

        window.createWindow();

        const VkAllocationCallbacks* allocationCallbacks = nullptr;
        if (glfwCreateWindowSurface(*instance.getInternal(), window.getInternalWindow(), allocationCallbacks, &surface) != VK_SUCCESS)
        {
            Logger->error("Can't create window surface");
        }


        physicalDevice = instance.pickPhysicalDevice();
    }

    Renderer::~Renderer() noexcept
    {
        vkDestroySurfaceKHR(*instance.getInternal(), surface, nullptr);
        GLFW::DeinitGLFW();
    }

}