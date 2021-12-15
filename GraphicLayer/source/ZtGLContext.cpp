#include "Zinet/GraphicLayer/ZtGLContext.h"

namespace zt::gl
{

    Context::~Context() noexcept
    {
        instance.destroy();
        deinitGLFW();
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

    void Context::createApplicationInfo()
    {
        applicationInfo.sType = vk::StructureType::eApplicationInfo;
        applicationInfo.pApplicationName = "Zinet";
        applicationInfo.applicationVersion = 1;
        applicationInfo.pEngineName = "Zinet Renderer";
        applicationInfo.engineVersion = 1;
        applicationInfo.apiVersion = VK_API_VERSION_1_2;
    }

    const vk::ApplicationInfo& Context::getApplicationInfo() const
    {
        return applicationInfo;
    }

    void Context::createInstanceCreateInfo()
    {
        instanceCreateInfo.flags = {};
        instanceCreateInfo.pApplicationInfo = &applicationInfo;
    }

    const vk::InstanceCreateInfo& Context::getInstanceCreateInfo() const
    {
        return instanceCreateInfo;
    }

    void Context::createInstance()
    {
        instance = vk::createInstance(instanceCreateInfo);
    }

    const vk::Instance& Context::getInstance() const
    {
        return instance;
    }

}