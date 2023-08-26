#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"

namespace zt::gl
{
	Surface::Surface()
	{
	}

	bool Surface::create(Instance& instance, Window& window)
	{
		VkSurfaceKHR tempVkSurface{};
		const VkAllocationCallbacks* allocationCallbacks = nullptr;
		VkResult result = glfwCreateWindowSurface(
			*instance.getInternal(),
			window.getInternal(), 
			allocationCallbacks, 
			&tempVkSurface);

		vk::raii::SurfaceKHR tempSurface{ instance.getInternal(), tempVkSurface };
		internal.swap(tempSurface);
		tempSurface.release();

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