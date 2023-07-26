#include "Zinet/GraphicLayer/ZtGLTexture.h"

#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLUtilities.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLMath.h"

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
			.allocationCreateInfo = imageBuffer.createVmaAllocationCreateInfo(false, true)
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

	RenderStates::Image Texture::createImageDrawInfo(const Sampler& sampler) const
	{
		vk::ImageLayout imageLayout = vk::ImageLayout::eGeneral;
		if (!image.getImageLayouts().empty())
		{
			imageLayout = image.getImageLayouts().front();
		}

		RenderStates::Image imageDrawInfo
		{
			.buffer = imageBuffer,
			.sampler = sampler,
			.view = imageView,
			.layout = imageLayout
		};

		return imageDrawInfo;
	}


}