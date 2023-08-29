#include "Zinet/GraphicLayer/ZtGLTexture.h"

#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLUtilities.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"

#include "Zinet/Math/ZtMath.h"

namespace zt::gl
{
	void Texture::create(const CreateInfo& createInfo)
	{
		std::uint32_t mipmapLevels = 1u;
		if (createInfo.mipmaps)
		{
			mipmapLevels = Math::GetMaximumMipmapLevelsCount(createInfo.size);
		}

		Image::CreateInfo imageCreateInfo{
			.device = createInfo.rendererContext.getDevice(),
			.vma = createInfo.rendererContext.getVma(),
			.vkImageCreateInfo = image.createCreateInfo(createInfo.size, mipmapLevels, createInfo.format),
			.allocationCreateInfo = image.createAllocationCreateInfo()
		};
		image.create(imageCreateInfo);

		Buffer::CreateInfo bufferCreateInfo{
			.device = createInfo.rendererContext.getDevice(),
			.vma = createInfo.rendererContext.getVma(),
			.vkBufferCreateInfo = imageBuffer.createCreateInfo(createInfo.size.x * createInfo.size.y * 4u), // 4u because we only support vk::Format::eR8G8B8A8Srgb format for now
			.allocationCreateInfo = imageBuffer.createVmaAllocationCreateInfo(false, false)
		};
		imageBuffer.create(bufferCreateInfo);

		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(*image.getInternal(), mipmapLevels, createInfo.format);
		imageView.create(createInfo.rendererContext.getDevice(), imageViewCreateInfo);
	}

	void Texture::loadFromSTBImage(CommandBuffer& commandBuffer, const STBImage& stbImage)
	{
		auto stbImageSize = stbImage.sizeBytes();

		imageBuffer.fillWithCArray(stbImage.get(), stbImageSize);

		Utilities::CopyImageBufferToImageInfo copyImageBufferToImageInfo
		{
			.commandBuffer = commandBuffer,
			.image = image,
			.imageBuffer = imageBuffer
		};
		Utilities::CopyImageBufferToImage(copyImageBufferToImageInfo);
	}

	void Texture::clear()
	{
		imageView.clear();
		imageBuffer.clear();
		image.clear();
	}

	void Texture::generateMipmapTexture(const GenerateMipmapTextureInfo& info)
	{
		if (!info.rendererContext.getPhysicalDevice().isFormatSupportingGeneratingMipmaps(vk::Format::eR8G8B8A8Srgb))
		{
			zt::core::Ensure(false);
			return;
		}

		const Vector2ui textureSize = info.texture.getSize();
		const std::uint32_t mipmapLevels = Math::GetMaximumMipmapLevelsCount(textureSize);

		const vk::Offset3D srcSize = {
			static_cast<std::int32_t>(textureSize.x),
			static_cast<std::int32_t>(textureSize.y),
			1 };

		getImage().changeLayout(info.commandBuffer, vk::ImageLayout::eTransferDstOptimal, vk::PipelineStageFlagBits::eTransfer);

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

			const Image& sourceImage = info.texture.getImage();
			vk::ImageLayout sourceImageLayout = sourceImage.getImageLayouts().front();
			const Image& destinyImage = getImage();
			vk::ImageLayout destinyImageLayout = destinyImage.getImageLayouts().front();
			vk::Filter filter = vk::Filter::eNearest;
			info.commandBuffer->blitImage(sourceImage.getVk(), sourceImageLayout, destinyImage.getVk(), destinyImageLayout, imageBlit, filter);
		}
	}

}