#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"

namespace zt::gl
{
	Surface::Surface()
	{
	}

	bool Surface::create(Instance& instance, Window& window)
	{
		VkSurfaceKHR tempSurface{};
		const VkAllocationCallbacks* allocationCallbacks = nullptr;
		VkResult result = glfwCreateWindowSurface(
			*instance.getInternal(),
			window.getInternal(), 
			allocationCallbacks, 
			&tempSurface);

		internal = std::move(vk::raii::SurfaceKHR{ instance.getInternal(), std::move(tempSurface) });

		if (result == VK_SUCCESS)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}