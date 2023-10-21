#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Math/ZtVecTypes.h"

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
			vk::ImageAspectFlags imageAspectFlags = vk::ImageAspectFlagBits::eColor;
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

		vk::ImageCreateInfo createCreateInfo(const Vector2<std::uint32_t>& size, std::uint32_t newMipmapLevels = 1u, vk::Format format = vk::Format::eR8G8B8A8Srgb);

		VmaAllocationCreateInfo createAllocationCreateInfo() const;

		void create(const CreateInfo& imageCreateInfo);

		Vector2<std::uint32_t> getSize() const { return { width, height }; }

		std::uint32_t getMipmapLevels() const { return mipmapLevels; }

		const std::vector<vk::ImageLayout>& getImageLayouts() const { return imageLayouts; }

		const std::vector<vk::PipelineStageFlags>& getPipelineStageFlags() const { return pipelineStageFlags; }

		void changeLayout(CommandBuffer& commandBuffer, vk::ImageLayout newLayout, vk::PipelineStageFlags newPipelineStageFlags);

		void clear();

	protected:

		VmaAllocator vmaAllocator{};
		VmaAllocation allocation{};
		std::uint32_t width{};
		std::uint32_t height{};
		vk::ImageAspectFlags imageAspectFlags;
		std::uint32_t mipmapLevels = 0u;
		std::vector<vk::ImageLayout> imageLayouts{};
		std::vector<vk::PipelineStageFlags> pipelineStageFlags{};
	};

}