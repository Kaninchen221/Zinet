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

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("ImageView");

	public:

		ImageView();
		ImageView(const ImageView& other) = default;
		ImageView(ImageView&& other) = default;

		ImageView& operator = (const ImageView& other) = default;
		ImageView& operator = (ImageView&& other) = default;

		~ImageView() noexcept = default;

		// TODO Rename to createCreateInfo
		vk::ImageViewCreateInfo createImageViewCreateInfo(vk::Image image, const vk::Format& format) const;

		void create(Device& device, vk::Image image, const vk::Format& format);

	};

}