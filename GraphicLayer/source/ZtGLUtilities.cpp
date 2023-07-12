#include "Zinet/GraphicLayer/ZtGLUtilities.h"

#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLImageBuffer.h"

namespace zt::gl
{
	void Utilities::CopyImageBufferToImage(const CopyImageBufferToImageInfo& info)
	{
		// Barrier
		vk::ImageLayout oldLayout = vk::ImageLayout::eUndefined;
		vk::ImageLayout newLayout = vk::ImageLayout::eTransferDstOptimal;
		vk::ImageMemoryBarrier barrier = info.commandBuffer.createImageMemoryBarrier(info.image, oldLayout, newLayout);

		vk::PipelineStageFlags sourceStage = vk::PipelineStageFlagBits::eTopOfPipe;

		vk::PipelineStageFlags destinationStage = vk::PipelineStageFlagBits::eFragmentShader;

		info.commandBuffer->pipelineBarrier(
			sourceStage,
			destinationStage,
			vk::DependencyFlags{},
			{},
			{},
			barrier);

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
			info.width,
			info.height,
			1
		};

		newLayout = vk::ImageLayout::eTransferDstOptimal;
		info.commandBuffer.copyBufferToImage(info.imageBuffer, info.image, newLayout, imageRegion);

		oldLayout = vk::ImageLayout::eTransferDstOptimal;
		newLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
		vk::ImageMemoryBarrier barrierAfterCopy = info.commandBuffer.createImageMemoryBarrier(info.image, oldLayout, newLayout);

		sourceStage = vk::PipelineStageFlagBits::eTransfer;
		destinationStage = vk::PipelineStageFlagBits::eFragmentShader;

		info.commandBuffer->pipelineBarrier(
			sourceStage,
			destinationStage,
			vk::DependencyFlags{},
			{},
			{},
			barrierAfterCopy);
	}
}