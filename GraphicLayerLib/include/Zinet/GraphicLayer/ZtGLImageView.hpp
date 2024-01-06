#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"

#include "Zinet/Core/ZtLogger.hpp"

namespace zt::gl
{
	class Device;

	class ZINET_GRAPHIC_LAYER_API ImageView : public VulkanObject<vk::raii::ImageView>
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("ImageView");

	public:

		ImageView() = default;
		ImageView(const ImageView& other) = default;
		ImageView(ImageView&& other) = default;

		ImageView& operator = (const ImageView& other) = default;
		ImageView& operator = (ImageView&& other) = default;

		~ImageView() noexcept = default;

		vk::ImageViewCreateInfo createCreateInfo(vk::Image image, std::uint32_t newMipmapLevels = 1u, const vk::Format& format = vk::Format::eR8G8B8A8Srgb) const;

		void create(const Device& device, const vk::ImageViewCreateInfo& imageViewCreateInfo);

		std::uint32_t getMipmapLevels() const { return mipmapLevels; }

	protected:

		std::uint32_t mipmapLevels = 0u;
	};

}