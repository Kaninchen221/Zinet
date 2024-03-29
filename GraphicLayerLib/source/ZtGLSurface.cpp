#include "Zinet/GraphicLayer/ZtGLSurface.hpp"
#include "Zinet/GraphicLayer/ZtGLInstance.hpp"

namespace zt::gl
{
	bool Surface::create(Instance& instance, wd::Window& window)
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