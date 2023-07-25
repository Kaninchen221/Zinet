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
	class RendererContext;
	class CommandBuffer;

	class ZINET_GRAPHIC_LAYER_API Texture
	{

	public:

		struct ZINET_GRAPHIC_LAYER_API CreateInfo
		{
			CommandBuffer& commandBuffer;
			const STBImage& stbImage;
			const RendererContext& rendererContext;
			bool mipmaps = false;
		};

		struct ZINET_GRAPHIC_LAYER_API CreateBlankTextureInfo
		{
			CommandBuffer& commandBuffer;
			const Vector2ui& textureSize;
			const Vector4<std::uint8_t>& color;
			const RendererContext& rendererContext;
		};

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Texture");

	public:

		Texture() = default;
		Texture(const Texture& other) = default;
		Texture(Texture&& other) = default;

		Texture& operator = (const Texture& other) = default;
		Texture& operator = (Texture&& other) = default;

		~Texture() noexcept = default;

		const Image& getImage() const { return image; }
		Image& getImage() { return image; }

		const ImageBuffer& getImageBuffer() const { return imageBuffer; }
		ImageBuffer& getImageBuffer() { return imageBuffer; }

		const ImageView& getImageView() const { return imageView; }
		ImageView& getImageView() { return imageView; }

		void createNormalTexture(const CreateInfo& createInfo); // TODO Split this function to create and load from STBImage

		// TODO (low) test it
		void createBlankTextureForMipmap(const CreateBlankTextureInfo& createInfo);

		RenderStates::Image createImageDrawInfo(const Sampler& sampler) const;

		Vector2f getSize() const { return Vector2f{ image.getSize() }; }

	protected:

		Image image;
		ImageBuffer imageBuffer;
		ImageView imageView;

	};
}