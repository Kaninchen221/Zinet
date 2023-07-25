#include "Zinet/GraphicLayer/ZtGLTexture.h"

#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLUtilities.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLMath.h"

namespace zt::gl
{
	void Texture::createNormalTexture(const CreateInfo& createInfo)
	{
		std::uint32_t width = createInfo.stbImage.getWidth();
		std::uint32_t height = createInfo.stbImage.getHeight();

		std::uint32_t mipmapLevels = 1u;
		if (createInfo.mipmaps)
		{
			mipmapLevels = Math::GetMaximumMipmapLevelsCount({ width, height });
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
			.imageBuffer = imageBuffer
		};
		Utilities::CopyImageBufferToImage(copyImageBufferToImageInfo);

		image.changeLayout(createInfo.commandBuffer, vk::ImageLayout::eShaderReadOnlyOptimal, vk::PipelineStageFlagBits::eFragmentShader);

		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(*image.getInternal(), mipmapLevels, vk::Format::eR8G8B8A8Srgb);
		imageView.create(createInfo.rendererContext.getDevice(), imageViewCreateInfo);
	}

	void Texture::createBlankTextureForMipmap(const CreateBlankTextureInfo& createInfo)
	{
		std::uint32_t mipmapLevels = Math::GetMaximumMipmapLevelsCount(createInfo.textureSize);

		Image::CreateInfo imageCreateInfo{
			.device = createInfo.rendererContext.getDevice(),
			.vma = createInfo.rendererContext.getVma(),
			.vkImageCreateInfo = image.createCreateInfo(createInfo.textureSize, mipmapLevels, vk::Format::eR8G8B8A8Srgb),
			.allocationCreateInfo = image.createAllocationCreateInfo()
		};
		image.create(imageCreateInfo);

		size_t bufferSize = createInfo.textureSize.x * createInfo.textureSize.y * sizeof(Vector4<std::uint8_t>);
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
			.imageBuffer = imageBuffer
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