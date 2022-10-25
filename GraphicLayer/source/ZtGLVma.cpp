#include "Zinet/GraphicLayer/ZtGLVma.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"

namespace zt::gl
{
	const VmaAllocator Vma::getInternal() const
	{
		return vmaAllocator;
	}

	VmaAllocatorCreateInfo Vma::createAllocatorCreateInfo(const Renderer& renderer) const
	{
		const Instance& instance = renderer.getInstance();

		VmaAllocatorCreateInfo createInfo{};
		createInfo.instance = *instance.getInternal();
		createInfo.device = *renderer.getDevice().getInternal();
		createInfo.physicalDevice = *renderer.getPhysicalDevice().getInternal();

		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		createInfo.vulkanApiVersion = applicationInfo.apiVersion;

		return createInfo;
	}

	void Vma::create(const VmaAllocatorCreateInfo& allocatorCreateInfo)
	{
		vmaCreateAllocator(&allocatorCreateInfo, &vmaAllocator);
	}
}