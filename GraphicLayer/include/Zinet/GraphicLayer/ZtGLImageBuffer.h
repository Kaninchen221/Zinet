#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLBuffer.h"

#include <vector>

namespace zt::gl
{
	class Sampler;
	class ImageView;

	class ZINET_GRAPHIC_LAYER_API ImageBuffer : public Buffer
	{

	public:

		ImageBuffer() = default;
		ImageBuffer(const ImageBuffer& other) = default;
		ImageBuffer(ImageBuffer&& other) = default;

		ImageBuffer& operator = (const ImageBuffer& other) = default;
		ImageBuffer& operator = (ImageBuffer&& other) = default;

		~ImageBuffer() noexcept = default;

		vk::BufferCreateInfo createCreateInfo(std::uint64_t size) const override;

		vk::DescriptorImageInfo createDescriptorImageInfo(Sampler& sampler, ImageView& imageView, vk::ImageLayout imageLayout);

	};

}