#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLVma.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"

namespace zt::gl
{
	// TODO (Low) Use Vector2ui instead of 2 params
	vk::ImageCreateInfo Image::createCreateInfo(std::uint32_t newWidth, std::uint32_t newHeight, std::uint32_t newMipmapLevels, vk::Format format)
	{
		vk::ImageCreateInfo createInfo{};
		createInfo.imageType = vk::ImageType::e2D;
		createInfo.extent.width = newWidth;
		createInfo.extent.height = newHeight;
		createInfo.extent.depth = 1;
		createInfo.mipLevels = newMipmapLevels;
		createInfo.arrayLayers = 1;
		createInfo.format = format;
		createInfo.tiling = vk::ImageTiling::eOptimal;
		createInfo.initialLayout = vk::ImageLayout::eUndefined;
		createInfo.usage = vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled | vk::ImageUsageFlagBits::eTransferSrc;
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

	void Image::create(const Image::CreateInfo& imageCreateInfo)
	{
		VkImage image;
		vmaAllocator = imageCreateInfo.vma.getInternal();
		VkResult result = vmaCreateImage(imageCreateInfo.vma.getInternal(), &imageCreateInfo.vkImageCreateInfo, &imageCreateInfo.allocationCreateInfo, &image, &allocation, nullptr);
		
		if (result == VK_SUCCESS)
		{
			internal = std::move(vk::raii::Image{ imageCreateInfo.device.getInternal(), image });
			width = imageCreateInfo.vkImageCreateInfo.extent.width;
			height = imageCreateInfo.vkImageCreateInfo.extent.height;
			mipmapLevels = imageCreateInfo.vkImageCreateInfo.mipLevels;
		}
		else
		{
			Logger->error("Failed to create Image");
			zt::core::Ensure(false);
		}
	}

	Image::~Image() noexcept
	{
		if (allocation != nullptr)
		{
			vmaDestroyImage(vmaAllocator, nullptr, allocation);
		}
	}

	void Image::changeLayout(CommandBuffer& commandBuffer, vk::ImageLayout newLayout, vk::PipelineStageFlags newPipelineStageFlags, std::uint32_t mipmapLevel)
	{
		vk::ImageMemoryBarrier barrier = commandBuffer.createImageMemoryBarrier(*this, currentImageLayout, newLayout, mipmapLevels, mipmapLevel);

		commandBuffer->pipelineBarrier(
			currentPipelineStageFlags,
			newPipelineStageFlags,
			vk::DependencyFlags{},
			{},
			{},
			barrier);

		currentImageLayout = newLayout;
		currentPipelineStageFlags = newPipelineStageFlags;
	}

}