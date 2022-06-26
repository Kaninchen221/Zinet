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

		ImageView() = default;
		ImageView(const ImageView& other) = default;
		ImageView(ImageView&& other) = default;

		ImageView& operator = (const ImageView& other) = default;
		ImageView& operator = (ImageView&& other) = default;

		~ImageView() noexcept = default;

		vk::ImageViewCreateInfo createCreateInfo(vk::Image image, const vk::Format& format) const;

		// TODO As params pass only device and create info
		// TODO Possibility to create from zt::gl::Image
		void create(Device& device, vk::Image image, const vk::Format& format);

	};

}