#pragma once

#include "Zinet/GraphicLayer/Buffers/ZtGLImageBuffer.h"
#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLImageView.h"
#include "Zinet/GraphicLayer/ZtGLSTBImage.h"
#include "Zinet/GraphicLayer/ZtGLDrawInfo.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Renderer;

	// TODO We need possibility to use part of the texture. One bigger texture is better than a lot of smaller textures. 
	class ZINET_GRAPHIC_LAYER_API Texture
	{

	protected:

		inline static ConsoleLogger Logger = ConsoleLogger::Create("Texture");

	public:

		Texture() = default;
		Texture(const Texture& other) = default;
		Texture(Texture&& other) = default;

		Texture& operator = (const Texture& other) = default;
		Texture& operator = (Texture&& other) = default;

		~Texture() noexcept = default;

		const Image& getImage() const { return image; }

		const ImageBuffer& getImageBuffer() const { return imageBuffer; }

		const ImageView& getImageView() const { return imageView; }

		const vk::ImageLayout& getVkImageLayout() const { return vkImageLayout; }

		void create(const STBImage& stbImage, const Renderer& renderer);

		DrawInfo::Image createImageDrawInfo(const Sampler& sampler) const;

	protected:

		Image image;
		ImageBuffer imageBuffer;
		ImageView imageView;
		vk::ImageLayout vkImageLayout;

	};

	// TODO Move it perhaps to an Queue class
	void CopyImageBufferToImage(Image& image, ImageBuffer& imageBuffer, const Renderer& renderer, std::uint32_t width, std::uint32_t height);
}