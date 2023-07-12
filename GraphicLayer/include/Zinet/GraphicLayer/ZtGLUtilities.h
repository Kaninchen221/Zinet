#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Image;
	class ImageBuffer;
	class RendererContext;
	class CommandBuffer;

	class ZINET_GRAPHIC_LAYER_API Utilities
	{
	public:

		struct ZINET_GRAPHIC_LAYER_API CopyImageBufferToImageInfo
		{
			CommandBuffer& commandBuffer;
			Image& image;
			ImageBuffer& imageBuffer;
			std::uint32_t width;
			std::uint32_t height;
		};

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Utilities");

	public:

		Utilities() = delete;
		Utilities(const Utilities& other) = delete;
		Utilities(Utilities&& other) = delete;

		Utilities& operator = (const Utilities& other) = delete;
		Utilities& operator = (Utilities&& other) = delete;

		~Utilities() noexcept = delete;

		static void CopyImageBufferToImage(const CopyImageBufferToImageInfo& info);
	};

}