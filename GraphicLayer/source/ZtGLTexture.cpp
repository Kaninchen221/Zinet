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
				.vkImageCreateInfo = image.createCreateInfo({ width, height }, mipmapLevels, vk::Format::eR8G8B8A8Srgb),
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

		image.changeLayout(createInfo.commandBuffer, vk::ImageLayout::eShaderReadOnlyOptimal, vk::PipelineStageFlagBits::eFragmentShader);

		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(*image.getInternal(), mipmapLevels, vk::Format::eR8G8B8A8Srgb);
		imageView.create(createInfo.rendererContext.getDevice(), imageViewCreateInfo);
	}

	void Texture::createBlankTextureForMipmap(const CreateBlankTextureInfo& createInfo)
	{
		//Vector2ui textureSize = { createInfo.originalTextureSize.x + (createInfo.originalTextureSize.x / 2u), createInfo.originalTextureSize.y };
		Vector2ui textureSize = { createInfo.originalTextureSize.x, createInfo.originalTextureSize.y };
		std::uint32_t mipmapLevels = static_cast<std::uint32_t>(std::floor(std::log2(std::max(textureSize.x, textureSize.y)))) + 1; // TODO (mid) Refactor this

		Image::CreateInfo imageCreateInfo{
			.device = createInfo.rendererContext.getDevice(),
			.vma = createInfo.rendererContext.getVma(),
			.vkImageCreateInfo = image.createCreateInfo(textureSize, mipmapLevels, vk::Format::eR8G8B8A8Srgb),
			.allocationCreateInfo = image.createAllocationCreateInfo()
		};
		image.create(imageCreateInfo);

		size_t bufferSize = textureSize.x * textureSize.y * sizeof(Vector4<std::uint8_t>);
		Buffer::CreateInfo bufferCreateInfo{
			.device = createInfo.rendererContext.getDevice(),
			.vma = createInfo.rendererContext.getVma(),
			.vkBufferCreateInfo = imageBuffer.createCreateInfo(bufferSize),
			.allocationCreateInfo = imageBuffer.createVmaAllocationCreateInfo(false, true)
		};
		imageBuffer.create(bufferCreateInfo);

		Utilities::CopyImageBufferToImageInfo copyImageBufferToImageInfo
		{
			.commandBuffer = createInfo.commandBuffer,
			.image = image,
			.imageBuffer = imageBuffer,
			.width = textureSize.x,
			.height = textureSize.y
		};
		Utilities::CopyImageBufferToImage(copyImageBufferToImageInfo);

		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(*image.getInternal(), mipmapLevels, vk::Format::eR8G8B8A8Srgb);
		imageView.create(createInfo.rendererContext.getDevice(), imageViewCreateInfo);
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