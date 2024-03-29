#include "Zinet/GraphicLayer/ZtGLUtilities.hpp"

#include "Zinet/GraphicLayer/ZtGLCommandBuffer.hpp"
#include "Zinet/GraphicLayer/ZtGLImage.hpp"
#include "Zinet/GraphicLayer/ZtGLRendererContext.hpp"
#include "Zinet/GraphicLayer/Buffers/ZtGLImageBuffer.hpp"

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
		CommandBuffer::CopyBufferToImageInfo copyBufferToImageInfo
		{
			info.imageBuffer, info.image, newLayout, imageRegion
		};
		info.commandBuffer.copyBufferToImage(copyBufferToImageInfo);
	}

}