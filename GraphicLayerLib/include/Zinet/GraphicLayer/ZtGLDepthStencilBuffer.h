#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.h"
#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLImageView.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class PhysicalDevice;
	class RendererContext;

	class ZINET_GRAPHIC_LAYER_API DepthStencilBuffer
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("DepthStencilBuffer");

	public:

		DepthStencilBuffer() = default;
		DepthStencilBuffer(const DepthStencilBuffer& other) = default;
		DepthStencilBuffer(DepthStencilBuffer&& other) = default;

		DepthStencilBuffer& operator = (const DepthStencilBuffer& other) = default;
		DepthStencilBuffer& operator = (DepthStencilBuffer&& other) = default;

		~DepthStencilBuffer() noexcept = default;

		const Image& getImage() const { return image; }

		const ImageView& getImageView() const { return imageView; }

		bool findDepthFormat(const PhysicalDevice& physicalDevice, vk::Format& supportedFormat) const;

		void create(RendererContext& rendererContext, vk::Format format);

		void clear();

		bool isValid() const;

	protected:

		Image image;
		ImageView imageView;

	};

}