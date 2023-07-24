#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLVma.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"

namespace zt::gl
{
	vk::ImageCreateInfo Image::createCreateInfo(const Vector2<std::uint32_t>& size, std::uint32_t newMipmapLevels, vk::Format format)
	{
		vk::ImageCreateInfo createInfo{};
		createInfo.imageType = vk::ImageType::e2D;
		createInfo.extent.width = size.x;
		createInfo.extent.height = size.y;
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

			imageLayouts.clear();
			pipelineStageFlags.clear();
			imageLayouts.reserve(mipmapLevels);
			pipelineStageFlags.reserve(mipmapLevels);
			for (std::uint32_t mipmapLevel = 0u; mipmapLevel < mipmapLevels; ++mipmapLevel)
			{
				imageLayouts.push_back(vk::ImageLayout::eUndefined);
				pipelineStageFlags.push_back(vk::PipelineStageFlagBits::eTopOfPipe);
			}
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
			allocation = nullptr;
		}
	}

	void Image::changeLayout(CommandBuffer& commandBuffer, vk::ImageLayout newLayout, vk::PipelineStageFlags newPipelineStageFlags)
	{
		std::vector<vk::ImageLayout> tempImageLayouts;
		std::vector<vk::PipelineStageFlags> tempPipelineStageFlags;

		tempImageLayouts.reserve(mipmapLevels);
		tempPipelineStageFlags.reserve(mipmapLevels);

		for (std::uint32_t mipmapLevel = 0u; mipmapLevel < mipmapLevels; mipmapLevel++)
		{
			vk::ImageLayout currentImageLayout = imageLayouts[mipmapLevel];
			vk::PipelineStageFlags currentPipelineStageFlags = pipelineStageFlags[mipmapLevel];

			vk::ImageMemoryBarrier barrier = commandBuffer.createImageMemoryBarrier(*this, currentImageLayout, newLayout, mipmapLevels, mipmapLevel);

			commandBuffer->pipelineBarrier(
				currentPipelineStageFlags,
				newPipelineStageFlags,
				vk::DependencyFlags{},
				{},
				{},
				barrier);

			tempImageLayouts.push_back(newLayout);
			tempPipelineStageFlags.push_back(newPipelineStageFlags);
		}

		imageLayouts = tempImageLayouts;
		pipelineStageFlags = tempPipelineStageFlags;
	}

}