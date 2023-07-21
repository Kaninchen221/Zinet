#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLImageView.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class PhysicalDevice;
	class RendererContext;

	class ZINET_GRAPHIC_LAYER_API DepthBuffer
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("DepthBuffer");

	public:

		DepthBuffer() = default;
		DepthBuffer(const DepthBuffer& other) = default;
		DepthBuffer(DepthBuffer&& other) = default;

		DepthBuffer& operator = (const DepthBuffer& other) = default;
		DepthBuffer& operator = (DepthBuffer&& other) = default;

		~DepthBuffer() noexcept = default;

		const Image& getImage() const { return image; }

		const ImageView& getImageView() const { return imageView; }

		bool findDepthFormat(const PhysicalDevice& physicalDevice, vk::Format& supportedFormat) const;

		void create(const RendererContext& rendererContext, vk::Format format);

		void clear();

	protected:

		Image image;
		ImageView imageView;

	};

}