#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "Zinet/GraphicLayer/ZtGLInstance.h"

namespace zt::gl
{
	void Renderer::initialize()
	{
		createInstance();
	}

	const Context& Renderer::getContext() const
	{
		return context;
	}

	const Instance& Renderer::getInstance() const
	{
		return instance;
	}

	void Renderer::createInstance()
	{
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);
	}
}