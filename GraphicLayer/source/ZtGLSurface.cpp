#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"

namespace zt::gl
{
	bool Surface::create(const Instance& instance, Window& window)
	{
		const VkAllocationCallbacks* allocationCallbacks = nullptr;
		VkResult result = glfwCreateWindowSurface(*instance.getInternal(), window.getInternalWindow(), allocationCallbacks, &internal);
		if (result == VK_SUCCESS)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	VkSurfaceKHR Surface::getInternal() const
	{
		return internal;
	}

	Surface::~Surface() noexcept
	{
		if (internal != VkSurfaceKHR())
		{
			Logger->error("Call destroy before detructor");
		}
	}

	void Surface::destroy(const Instance& instance)
	{
		vkDestroySurfaceKHR(*instance.getInternal(), internal, nullptr);
		internal = VkSurfaceKHR();
	}
}