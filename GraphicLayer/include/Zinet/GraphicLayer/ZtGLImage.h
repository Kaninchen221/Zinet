#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

#include <vk_mem_alloc.h>

namespace zt::gl
{
	class Device;
	class Vma;

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

		inline static ConsoleLogger Logger = ConsoleLogger::Create("Image");

	public:

		Image() = default;
		Image(const Image& other) = default;
		Image(Image&& other) = default;

		Image& operator = (const Image& other) = default;
		Image& operator = (Image&& other) = default;

		~Image() noexcept;

		vk::ImageCreateInfo createCreateInfo(std::uint32_t width, std::uint32_t height, vk::Format format = vk::Format::eR8G8B8A8Srgb);

		VmaAllocationCreateInfo createAllocationCreateInfo() const;

		void create(const CreateInfo& imageCreateInfo);

	protected:

		VmaAllocator vmaAllocator{};
		VmaAllocation allocation{};

	};

}