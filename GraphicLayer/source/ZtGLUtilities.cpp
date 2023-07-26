#include "Zinet/GraphicLayer/ZtGLUtilities.h"

#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLImageBuffer.h"

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

		const Vector2i textureSize{ texture.getSize() };
		const std::uint8_t uint8Max = std::numeric_limits<std::uint8_t>::max();
		Vector4<std::uint8_t> color{ uint8Max, uint8Max, uint8Max, uint8Max };

		Texture::CreateInfo textureCreateInfo
		{
			rendererContext, commandBuffer, true, vk::Format::eR8G8B8A8Srgb, textureSize
		};
		mipmapTexture.create(textureCreateInfo);

		////////////////////////
		Vector2ui mipmapTextureSize{ mipmapTexture.getSize() };
		size_t mipmapLevels = static_cast<size_t>(std::floor(std::log2(std::max(textureSize.x, textureSize.y)))) + 1; // TODO (mid) Refactor this

		for (std::uint32_t mipmapLevel = 0u; mipmapLevel < mipmapLevels; mipmapLevel++)
		{
			//size_t previousMipmapLevel = std::clamp<int>(static_cast<int>(mipmapLevel - 1), 0u, 1000u);

			Vector2i position{ 0, 0 };
			//position.x = static_cast<int>(std::clamp<size_t>(mipmapLevel, 0u, 1u) * textureSize.x);
			//position.y = static_cast<int>((std::pow(2, previousMipmapLevel) - 1) / (std::pow(2, previousMipmapLevel)) * textureSize.y);

			Vector2i size{ 0, 0 };
			size.x = static_cast<int>(textureSize.x / std::pow(2, mipmapLevel));
			size.y = static_cast<int>(textureSize.y / std::pow(2, mipmapLevel));

			vk::Offset3D mipmapPosition = vk::Offset3D{ 
				position.x,
				position.y,
				0 };

			vk::Offset3D mipmapSize = vk::Offset3D{ 
				size.x,
				size.y,
				1 };

			//mipmapTexture.getImage().changeLayout(info.commandBuffer, vk::ImageLayout::eTransferDstOptimal, vk::PipelineStageFlagBits::eTransfer, mipmapLevel - 1u);
			vk::ImageMemoryBarrier barrier = commandBuffer.createImageMemoryBarrier(mipmapTexture.getImage(), vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal, 1, mipmapLevel);
			commandBuffer->pipelineBarrier(
				vk::PipelineStageFlagBits::eTopOfPipe,
				vk::PipelineStageFlagBits::eTransfer,
				vk::DependencyFlags{},
				{},
				{},
				barrier);

			vk::ImageBlit imageBlit{};
			imageBlit.srcOffsets[0] = vk::Offset3D{ 0, 0, 0 };
			imageBlit.srcOffsets[1] = vk::Offset3D{ textureSize.x, textureSize.y, 1 };
			imageBlit.srcSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
			imageBlit.srcSubresource.mipLevel = 0;
			imageBlit.srcSubresource.baseArrayLayer = 0;
			imageBlit.srcSubresource.layerCount = 1;
			imageBlit.dstOffsets[0] = mipmapPosition;
			imageBlit.dstOffsets[1] = mipmapSize;
			imageBlit.dstSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
			imageBlit.dstSubresource.mipLevel = mipmapLevel;
			//imageBlit.dstSubresource.mipLevel = 0;
			imageBlit.dstSubresource.baseArrayLayer = 0;
			imageBlit.dstSubresource.layerCount = 1;

			const Image& sourceImage = texture.getImage();
			vk::ImageLayout sourceImageLayout = vk::ImageLayout::eTransferSrcOptimal;
			const Image& destinyImage = mipmapTexture.getImage();
			vk::ImageLayout destinyImageLayout = vk::ImageLayout::eTransferDstOptimal;
			vk::Filter filter = vk::Filter::eNearest;
			commandBuffer->blitImage(sourceImage.getVk(), sourceImageLayout, destinyImage.getVk(), destinyImageLayout, imageBlit, filter);
		}
	}

}