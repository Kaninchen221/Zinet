#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Device;

	class ZINET_GRAPHIC_LAYER_API ImageView
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("ImageView");

	public:

		ImageView();
		ImageView(const ImageView& other) = default;
		ImageView(ImageView&& other) = default;

		ImageView& operator = (const ImageView& other) = default;
		ImageView& operator = (ImageView&& other) = default;

		~ImageView() noexcept = default;

		const vk::raii::ImageView& getInternal() const;

		vk::ImageViewCreateInfo createImageViewCreateInfo(vk::Image image, const vk::Format& format) const;

		void create(Device& device, vk::Image image, const vk::Format& format);

	protected:

		vk::raii::ImageView internal;

	};

}