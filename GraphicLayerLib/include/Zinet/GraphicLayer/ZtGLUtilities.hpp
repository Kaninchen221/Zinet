#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"
#include "Zinet/GraphicLayer/ZtGLTexture.hpp"

#include "Zinet/Core/ZtLogger.hpp"

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

		template<typename Vector>
		constexpr static Vector FromExtent2DToVector2(const vk::Extent2D& extent);

		constexpr static vk::Extent2D FromVector2ToExtent2D(auto vector);
	};

	template<typename Vector>
	constexpr Vector Utilities::FromExtent2DToVector2(const vk::Extent2D& extent)
	{
		return Vector
		{
			static_cast<Vector::value_type>(extent.width),
			static_cast<Vector::value_type>(extent.height)
		};
	}

	constexpr vk::Extent2D Utilities::FromVector2ToExtent2D(auto vector)
	{
		return vk::Extent2D
		{
			static_cast<std::uint32_t>(vector.x),
				static_cast<std::uint32_t>(vector.y)
		};
	}

}