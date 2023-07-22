#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

#include <vk_mem_alloc.h>

namespace zt::gl
{
	class Device;
	class Vma;
	class CommandBuffer;

	class ZINET_GRAPHIC_LAYER_API Image : public VulkanObject<vk::raii::Image>
	{

	public:

		struct CreateInfo
		{
			const Device& device;
			const Vma& vma;
			VkImageCreateInfo vkImageCreateInfo;
			VmaAllocationCreateInfo allocationCreateInfo;
		};

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Image");

	public:

		Image() = default;
		Image(const Image& other) = default;
		Image(Image&& other) = default;

		Image& operator = (const Image& other) = default;
		Image& operator = (Image&& other) = default;

		~Image() noexcept;

		vk::ImageCreateInfo createCreateInfo(std::uint32_t newWidth, std::uint32_t newHeight, std::uint32_t newMipmapLevels = 1u, vk::Format format = vk::Format::eR8G8B8A8Srgb);

		VmaAllocationCreateInfo createAllocationCreateInfo() const;

		void create(const CreateInfo& imageCreateInfo);

		std::uint32_t getWidth() const { return width; }
		std::uint32_t getHeight() const { return height; }

		std::uint32_t getMipmapLevels() const { return mipmapLevels; }

		vk::ImageLayout getCurrentImageLayout() const { return currentImageLayout; }
		vk::PipelineStageFlags getCurrentPipelineStageFlags() const { return currentPipelineStageFlags; }

		// TODO Test it
		void changeLayout(CommandBuffer& commandBuffer, vk::ImageLayout newLayout, vk::PipelineStageFlags newPipelineStageFlags, std::uint32_t mipmapLevel = 0u);

	protected:

		VmaAllocator vmaAllocator{};
		VmaAllocation allocation{};
		std::uint32_t width{};
		std::uint32_t height{};
		std::uint32_t mipmapLevels = 0u;
		vk::ImageLayout currentImageLayout = vk::ImageLayout::eUndefined; // TODO (mid) Test it
		vk::PipelineStageFlags currentPipelineStageFlags = vk::PipelineStageFlagBits::eTopOfPipe; // TODO (mid) Test it
	};

}