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
			const RendererContext& rendererContext;
			CommandBuffer& commandBuffer;
			bool mipmaps = false;
			vk::Format format = vk::Format::eR8G8B8A8Srgb;
			Vector2ui size;
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

		void create(const CreateInfo& createInfo);

		void loadFromSTBImage(CommandBuffer& commandBuffer, const STBImage& stbImage);

		RenderStates::Image createImageDrawInfo(const Sampler& sampler) const;

		Vector2ui getSize() const { return image.getSize(); }

		void clear();

	protected:

		Image image;
		ImageBuffer imageBuffer;
		ImageView imageView;

	};
}