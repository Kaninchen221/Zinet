#include "Zinet/GraphicLayer/ZtGLUtilities.h"

#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLImageBuffer.h"
#include "Zinet/GraphicLayer/ZtGLMath.h"

#include <algorithm>

namespace zt::gl
{
	void Utilities::CopyImageBufferToImage(const CopyImageBufferToImageInfo& info)
	{
		vk::ImageLayout newLayout = vk::ImageLayout::eTransferDstOptimal;
		vk::PipelineStageFlags destinationStage = vk::PipelineStageFlagBits::eFragmentShader;
		info.image.changeLayout(info.commandBuffer, newLayout, destinationStage);

		// BufferImageCopy
		vk::BufferImageCopy imageRegion{};
		imageRegion.bufferOffset = 0;
		imageRegion.bufferRowLength = 0;
		imageRegion.bufferImageHeight = 0;

		imageRegion.imageSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
		imageRegion.imageSubresource.mipLevel = 0;
		imageRegion.imageSubresource.baseArrayLayer = 0;
		imageRegion.imageSubresource.layerCount = 1;

		const Vector2ui& imageSize = info.image.getSize();
		imageRegion.imageOffset = vk::Offset3D{ 0, 0, 0 };
		imageRegion.imageExtent = vk::Extent3D{
			imageSize.x,
			imageSize.y,
			1
		};

		newLayout = vk::ImageLayout::eTransferDstOptimal;
		info.commandBuffer.copyBufferToImage(info.imageBuffer, info.image, newLayout, imageRegion);
	}

	void Utilities::GenerateMipmapTexture(const GenerateMipmapTextureInfo& info, Texture& mipmapTexture)
	{
		if (!info.rendererContext.getPhysicalDevice().isFormatSupportingGeneratingMipmaps(vk::Format::eR8G8B8A8Srgb))
		{
			zt::core::Ensure(false);
			return;
		}

		Texture& texture = info.texture;
		CommandBuffer& commandBuffer = info.commandBuffer;
		RendererContext& rendererContext = info.rendererContext;

		const Vector2ui textureSize = texture.getSize();

		Texture::CreateInfo textureCreateInfo
		{
			rendererContext, commandBuffer, true, vk::Format::eR8G8B8A8Srgb, textureSize
		};
		mipmapTexture.create(textureCreateInfo);

		////////////////////////
		const std::uint32_t mipmapLevels = Math::GetMaximumMipmapLevelsCount(textureSize);

		const vk::Offset3D srcSize = { 
			static_cast<std::int32_t>(textureSize.x), 
			static_cast<std::int32_t>(textureSize.y),
			1 };

		mipmapTexture.getImage().changeLayout(commandBuffer, vk::ImageLayout::eTransferDstOptimal, vk::PipelineStageFlagBits::eTransfer);

		for (std::uint32_t mipmapLevel = 0u; mipmapLevel < mipmapLevels; mipmapLevel++)
		{
			vk::Offset3D mipmapSize = vk::Offset3D{ 
				static_cast<int>(textureSize.x / std::pow(2, mipmapLevel)),
				static_cast<int>(textureSize.y / std::pow(2, mipmapLevel)),
				1 };

			vk::ImageBlit imageBlit{};
			imageBlit.srcOffsets[0] = vk::Offset3D{ 0, 0, 0 };
			imageBlit.srcOffsets[1] = srcSize;
			imageBlit.srcSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
			imageBlit.srcSubresource.mipLevel = 0;
			imageBlit.srcSubresource.baseArrayLayer = 0;
			imageBlit.srcSubresource.layerCount = 1;
			imageBlit.dstOffsets[0] = vk::Offset3D{ 0, 0, 0 };
			imageBlit.dstOffsets[1] = mipmapSize;
			imageBlit.dstSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
			imageBlit.dstSubresource.mipLevel = mipmapLevel;
			imageBlit.dstSubresource.baseArrayLayer = 0;
			imageBlit.dstSubresource.layerCount = 1;

			const Image& sourceImage = texture.getImage();
			vk::ImageLayout sourceImageLayout = sourceImage.getImageLayouts().front();
			const Image& destinyImage = mipmapTexture.getImage();
			vk::ImageLayout destinyImageLayout = destinyImage.getImageLayouts().front();
			vk::Filter filter = vk::Filter::eNearest;
			commandBuffer->blitImage(sourceImage.getVk(), sourceImageLayout, destinyImage.getVk(), destinyImageLayout, imageBlit, filter);
		}
	}

}