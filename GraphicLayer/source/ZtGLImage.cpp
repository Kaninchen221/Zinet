#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLVma.h"

namespace zt::gl
{

	vk::ImageCreateInfo Image::createCreateInfo(std::uint32_t width, std::uint32_t height)
	{
		vk::ImageCreateInfo createInfo{};
		createInfo.imageType = vk::ImageType::e2D;
		createInfo.extent.width = width;
		createInfo.extent.height = height;
		createInfo.extent.depth = 1;
		createInfo.mipLevels = 1;
		createInfo.arrayLayers = 1;
		createInfo.format = vk::Format::eR8G8B8A8Srgb;
		createInfo.tiling = vk::ImageTiling::eOptimal;
		createInfo.initialLayout = vk::ImageLayout::eUndefined;
		createInfo.usage = vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled;
		createInfo.sharingMode = vk::SharingMode::eExclusive;
		createInfo.samples = vk::SampleCountFlagBits::e1;

		return createInfo;
	}

	VmaAllocationCreateInfo Image::createAllocationCreateInfo() const
	{
		VmaAllocationCreateInfo allocationCreateInfo{};
		allocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;
		allocationCreateInfo.flags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT;
		allocationCreateInfo.priority = 1.f;

		return allocationCreateInfo;
	}

	void Image::create(const ImageCreateInfo& imageCreateInfo)
	{
		VkImage image;
		VkResult result = vmaCreateImage(imageCreateInfo.vma.getInternal(), &imageCreateInfo.vkImageCreateInfo, &imageCreateInfo.allocationCreateInfo, &image, &allocation, nullptr);
		
		if (result == VK_SUCCESS)
		{
			internal = std::move(vk::raii::Image{ imageCreateInfo.device.getInternal(), image });
		}
		else
		{
			Logger->error("Failed to create Image");
			Ensure(false);
		}
	}

}