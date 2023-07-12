#include "Zinet/GraphicLayer/ZtGLTexture.h"

#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLUtilities.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"

namespace zt::gl
{
	void Texture::create(CommandBuffer& commandBuffer, const STBImage& stbImage, const RendererContext& rendererContext)
	{
		Image::CreateInfo imageCreateInfo{
			   .device = rendererContext.getDevice(),
			   .vma = rendererContext.getVma(),
			   .vkImageCreateInfo = image.createCreateInfo(stbImage.getWidth(), stbImage.getHeight(), vk::Format::eR8G8B8A8Srgb),
			   .allocationCreateInfo = image.createAllocationCreateInfo()
		};
		image.create(imageCreateInfo);

		Buffer::CreateInfo bufferCreateInfo{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkBufferCreateInfo = imageBuffer.createCreateInfo(stbImage.sizeBytes()),
			.allocationCreateInfo = imageBuffer.createVmaAllocationCreateInfo(false, true)
		};
		imageBuffer.create(bufferCreateInfo);
		imageBuffer.fillWithCArray(stbImage.get());

		Utilities::CopyImageBufferToImageInfo copyImageBufferToImageInfo
		{
			.commandBuffer = commandBuffer,
			.image = image,
			.imageBuffer = imageBuffer,
			.width = static_cast<std::uint32_t>(stbImage.getWidth()),
			.height = static_cast<std::uint32_t>(stbImage.getHeight())
		};
		Utilities::CopyImageBufferToImage(copyImageBufferToImageInfo);

		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(*image.getInternal(), vk::Format::eR8G8B8A8Srgb);
		imageView.create(rendererContext.getDevice(), imageViewCreateInfo);

		vkImageLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
	}

	RenderStates::Image Texture::createImageDrawInfo(const Sampler& sampler) const
	{
		RenderStates::Image imageDrawInfo
		{
			.buffer = imageBuffer,
			.sampler = sampler,
			.view = imageView,
			.layout = vkImageLayout

		};

		return imageDrawInfo;
	}

}