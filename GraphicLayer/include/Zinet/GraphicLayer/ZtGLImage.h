#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

#include <vk_mem_alloc.h>

namespace zt::gl
{
	class Device;
	class Vma;

	struct ImageCreateInfo
	{
		const Device& device;
		const Vma& vma;
		VkImageCreateInfo vkImageCreateInfo;
		VmaAllocationCreateInfo allocationCreateInfo;
	};

	class ZINET_GRAPHIC_LAYER_API Image : public VulkanObject<vk::raii::Image>
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Image");

	public:

		Image() = default;
		Image(const Image& other) = default;
		Image(Image&& other) = default;

		Image& operator = (const Image& other) = default;
		Image& operator = (Image&& other) = default;

		~Image() noexcept;

		vk::ImageCreateInfo createCreateInfo(std::uint32_t width, std::uint32_t height);

		VmaAllocationCreateInfo createAllocationCreateInfo() const;

		void create(const ImageCreateInfo& imageCreateInfo);

	protected:

		VmaAllocator vmaAllocator{};
		VmaAllocation allocation{};

	};

}