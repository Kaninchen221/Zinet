#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

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

		vk::ImageViewCreateInfo createCreateInfo(vk::Image image, const vk::Format& format) const;

		void create(const Device& device, const vk::ImageViewCreateInfo& imageViewCreateInfo);

	};

}