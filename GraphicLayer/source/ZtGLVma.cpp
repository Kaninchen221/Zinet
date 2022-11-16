#include "Zinet/GraphicLayer/ZtGLVma.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"

namespace zt::gl
{
	Vma::~Vma() noexcept
	{
		vmaDestroyAllocator(vmaAllocator);
	}

	const VmaAllocator Vma::getInternal() const
	{
		return vmaAllocator;
	}

	VmaAllocatorCreateInfo Vma::createAllocatorCreateInfo(const Instance& instance, const Device& device, const PhysicalDevice& physicalDevice) const
	{

		VmaAllocatorCreateInfo createInfo{};
		createInfo.instance = *instance.getInternal();
		createInfo.device = *device.getInternal();
		createInfo.physicalDevice = *physicalDevice.getInternal();

		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		createInfo.vulkanApiVersion = applicationInfo.apiVersion;

		return createInfo;
	}

	void Vma::create(const VmaAllocatorCreateInfo& allocatorCreateInfo)
	{
		vmaCreateAllocator(&allocatorCreateInfo, &vmaAllocator);
	}
}