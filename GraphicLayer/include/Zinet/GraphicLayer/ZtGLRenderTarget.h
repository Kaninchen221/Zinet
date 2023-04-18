#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLImageView.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class ZINET_GRAPHIC_LAYER_API RenderTarget
	{

	public:

		struct ZINET_GRAPHIC_LAYER_API CreateInfo
		{
			const Device& device;
			const Vma& vma;
			std::uint32_t width;
			std::uint32_t height;
			vk::Format format;
		};

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("RenderTarget");

	public:

		RenderTarget() = default;
		RenderTarget(const RenderTarget& other) = default;
		RenderTarget(RenderTarget&& other) = default;

		RenderTarget& operator = (const RenderTarget& other) = default;
		RenderTarget& operator = (RenderTarget&& other) = default;

		~RenderTarget() noexcept = default;

		const Image& getImage() const { return image; }

		const ImageView& getImageView() const { return imageView; }

		void create(const CreateInfo& createInfo);

	protected:

		void createImage(const CreateInfo& createInfo);

		Image image;
		ImageView imageView;

	};

}