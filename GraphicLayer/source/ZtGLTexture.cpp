#include "Zinet/GraphicLayer/ZtGLTexture.h"

#include "Zinet/GraphicLayer/ZtGLRenderer.h"

namespace zt::gl
{
	void Texture::create(const STBImage& stbImage, const Renderer& renderer)
	{
		Image::CreateInfo imageCreateInfo{
			   .device = renderer.getDevice(),
			   .vma = renderer.getVma(),
			   .vkImageCreateInfo = image.createCreateInfo(stbImage.getWidth(), stbImage.getHeight(), vk::Format::eR8G8B8A8Srgb),
			   .allocationCreateInfo = image.createAllocationCreateInfo()
		};
		image.create(imageCreateInfo);

		BufferCreateInfo bufferCreateInfo{
			.device = renderer.getDevice(),
			.vma = renderer.getVma(),
			.vkBufferCreateInfo = imageBuffer.createCreateInfo(stbImage.sizeBytes()),
			.allocationCreateInfo = imageBuffer.createVmaAllocationCreateInfo(false, true)
		};
		imageBuffer.create(bufferCreateInfo);
		imageBuffer.fillWithCArray(stbImage.get());

		CopyImageBufferToImage(image, imageBuffer, renderer, stbImage.getWidth(), stbImage.getHeight());

		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(*image.getInternal(), vk::Format::eR8G8B8A8Srgb);
		imageView.create(renderer.getDevice(), imageViewCreateInfo);

		vkImageLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
	}

	DrawInfo::Image Texture::createImageDrawInfo(Sampler& sampler)
	{
		DrawInfo::Image imageDrawInfo
		{
			.buffer = imageBuffer,
			.sampler = sampler,
			.view = imageView,
			.layout = vkImageLayout

		};

		return imageDrawInfo;
	}

	void CopyImageBufferToImage(Image& image, ImageBuffer& imageBuffer, const Renderer& renderer, std::uint32_t width, std::uint32_t height)
	{
		CommandBuffer commandBuffer;
		//vk::CommandBufferAllocateInfo allocateInfo = commandBuffer.createCommandBufferAllocateInfo(commandPool);
		commandBuffer.allocateCommandBuffer(renderer.getDevice(), renderer.getCommandPool());

		// Barrier
		vk::ImageLayout oldLayout = vk::ImageLayout::eUndefined;
		vk::ImageLayout newLayout = vk::ImageLayout::eTransferDstOptimal;
		vk::ImageMemoryBarrier barrier = commandBuffer.createImageMemoryBarrier(image, oldLayout, newLayout);

		vk::PipelineStageFlags sourceStage = vk::PipelineStageFlagBits::eTopOfPipe;

		vk::PipelineStageFlags destinationStage = vk::PipelineStageFlagBits::eFragmentShader;

		commandBuffer.begin();

		commandBuffer->pipelineBarrier(
			sourceStage,
			destinationStage,
			vk::DependencyFlags{},
			{},
			{},
			barrier);

		commandBuffer.end();

		vk::SubmitInfo submitInfo{};
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

		renderer.getQueue().submit(submitInfo);
		renderer.getQueue()->waitIdle();

		// BufferImageCopy
		vk::BufferImageCopy imageRegion{};
		imageRegion.bufferOffset = 0;
		imageRegion.bufferRowLength = 0;
		imageRegion.bufferImageHeight = 0;

		imageRegion.imageSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
		imageRegion.imageSubresource.mipLevel = 0;
		imageRegion.imageSubresource.baseArrayLayer = 0;
		imageRegion.imageSubresource.layerCount = 1;

		imageRegion.imageOffset = vk::Offset3D{ 0, 0, 0 };
		imageRegion.imageExtent = vk::Extent3D{
			width,
			height,
			1
		};

		commandBuffer.allocateCommandBuffer(renderer.getDevice(), renderer.getCommandPool());

		commandBuffer.begin();

		newLayout = vk::ImageLayout::eTransferDstOptimal;
		commandBuffer.copyBufferToImage(imageBuffer, image, newLayout, imageRegion);
		commandBuffer.end();

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

		renderer.getQueue().submit(submitInfo);
		renderer.getQueue()->waitIdle();

		// Barrier after copy
		commandBuffer.allocateCommandBuffer(renderer.getDevice(), renderer.getCommandPool());

		commandBuffer.begin();

		oldLayout = vk::ImageLayout::eTransferDstOptimal;
		newLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
		vk::ImageMemoryBarrier barrierAfterCopy = commandBuffer.createImageMemoryBarrier(image, oldLayout, newLayout);

		sourceStage = vk::PipelineStageFlagBits::eTransfer;
		destinationStage = vk::PipelineStageFlagBits::eFragmentShader;

		commandBuffer->pipelineBarrier(
			sourceStage,
			destinationStage,
			vk::DependencyFlags{},
			{},
			{},
			barrierAfterCopy);

		commandBuffer.end();

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

		renderer.getQueue().submit(submitInfo);
		renderer.getQueue()->waitIdle();
	}

}