#include "Zinet/GraphicLayer/ZtGLTexture.h"

#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLUtilities.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"

namespace zt::gl
{
	void Texture::create(const CreateInfo& createInfo)
	{
		std::uint32_t width = createInfo.stbImage.getWidth();
		std::uint32_t height = createInfo.stbImage.getHeight();

		std::uint32_t mipmapLevels = 1u;
		if (createInfo.mipmaps)
		{
			mipmapLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(width, height)))) + 1;
		}

		Image::CreateInfo imageCreateInfo{
			.device = createInfo.rendererContext.getDevice(),
			.vma = createInfo.rendererContext.getVma(),
			.vkImageCreateInfo = image.createCreateInfo(width, height, mipmapLevels, vk::Format::eR8G8B8A8Srgb),
			.allocationCreateInfo = image.createAllocationCreateInfo()
		};
		image.create(imageCreateInfo);

		Buffer::CreateInfo bufferCreateInfo{
			.device = createInfo.rendererContext.getDevice(),
			.vma = createInfo.rendererContext.getVma(),
			.vkBufferCreateInfo = imageBuffer.createCreateInfo(createInfo.stbImage.sizeBytes()),
			.allocationCreateInfo = imageBuffer.createVmaAllocationCreateInfo(false, true)
		};
		imageBuffer.create(bufferCreateInfo);
		imageBuffer.fillWithCArray(createInfo.stbImage.get());

		Utilities::CopyImageBufferToImageInfo copyImageBufferToImageInfo
		{
			.commandBuffer = createInfo.commandBuffer,
			.image = image,
			.imageBuffer = imageBuffer,
			.width = width,
			.height = height
		};
		Utilities::CopyImageBufferToImage(copyImageBufferToImageInfo);

		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(*image.getInternal(), mipmapLevels, vk::Format::eR8G8B8A8Srgb);
		imageView.create(createInfo.rendererContext.getDevice(), imageViewCreateInfo);

		vkImageLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
	}

	void Texture::createBlankTextureForMipmap(const CreateBlankTextureInfo& createInfo)
	{
		std::uint32_t mipmapLevels = 1u;
		std::vector<Vector4f> colors{ createInfo.size.x * createInfo.size.y, createInfo.color }; // TODO (Low) Optimize this

		Image::CreateInfo imageCreateInfo{
			.device = createInfo.rendererContext.getDevice(),
			.vma = createInfo.rendererContext.getVma(),
			.vkImageCreateInfo = image.createCreateInfo(createInfo.size.x, createInfo.size.y, mipmapLevels, vk::Format::eR8G8B8A8Srgb),
			.allocationCreateInfo = image.createAllocationCreateInfo()
		};
		image.create(imageCreateInfo);

		size_t bufferSize = colors.size() * sizeof(Vector4f);
		Buffer::CreateInfo bufferCreateInfo{
			.device = createInfo.rendererContext.getDevice(),
			.vma = createInfo.rendererContext.getVma(),
			.vkBufferCreateInfo = imageBuffer.createCreateInfo(bufferSize),
			.allocationCreateInfo = imageBuffer.createVmaAllocationCreateInfo(false, true)
		};
		imageBuffer.create(bufferCreateInfo);

		imageBuffer.fillWithStdContainer(colors);

		Utilities::CopyImageBufferToImageInfo copyImageBufferToImageInfo
		{
			.commandBuffer = createInfo.commandBuffer,
			.image = image,
			.imageBuffer = imageBuffer,
			.width = createInfo.size.x,
			.height = createInfo.size.y
		};
		Utilities::CopyImageBufferToImage(copyImageBufferToImageInfo);

		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(*image.getInternal(), mipmapLevels, vk::Format::eR8G8B8A8Srgb);
		imageView.create(createInfo.rendererContext.getDevice(), imageViewCreateInfo);

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