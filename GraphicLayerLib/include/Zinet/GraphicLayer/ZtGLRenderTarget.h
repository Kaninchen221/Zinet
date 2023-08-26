#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLImageView.h"
#include "Zinet/GraphicLayer/ZtGLFramebuffer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class RenderPass;

	class ZINET_GRAPHIC_LAYER_API RenderTargetBase
	{

	public:

		RenderTargetBase() = default;
		RenderTargetBase(const RenderTargetBase& other) = default;
		RenderTargetBase(RenderTargetBase&& other) = default;

		RenderTargetBase& operator = (const RenderTargetBase& other) = default;
		RenderTargetBase& operator = (RenderTargetBase&& other) = default;

		~RenderTargetBase() noexcept = default;

		Framebuffer& getFramebuffer() { return framebuffer; }

	protected:

		Framebuffer framebuffer;
	};

	class ZINET_GRAPHIC_LAYER_API RenderTarget : public RenderTargetBase
	{
		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("RenderTarget");

	public:


		RenderTarget() = default;
		RenderTarget(const RenderTarget& other) = default;
		RenderTarget(RenderTarget&& other) = default;

		RenderTarget& operator = (const RenderTarget& other) = default;
		RenderTarget& operator = (RenderTarget&& other) = default;

		~RenderTarget() noexcept = default;

		struct ZINET_GRAPHIC_LAYER_API CreateInfo
		{
			const Device& device;
			const Vma& vma;
			RenderPass& renderPass;
			std::uint32_t width;
			std::uint32_t height;
			vk::Format format;
		};

		void create(const CreateInfo& createInfo);

		const Image& getImage() const { return image; }

		const ImageView& getImageView() const { return imageView; }

	protected:

		void createImage(const CreateInfo& createInfo);
		void createImageView(const CreateInfo& createInfo);
		void createFramebuffer(const CreateInfo& createInfo);

		Image image;
		ImageView imageView;

	};

	class ZINET_GRAPHIC_LAYER_API RenderTargetDisplay : public RenderTargetBase
	{
		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("RenderTargetDisplay");

	public:

		RenderTargetDisplay() = default;
		RenderTargetDisplay(const RenderTargetDisplay& other) = default;
		RenderTargetDisplay(RenderTargetDisplay&& other) = default;

		RenderTargetDisplay& operator = (const RenderTargetDisplay& other) = default;
		RenderTargetDisplay& operator = (RenderTargetDisplay&& other) = default;

		~RenderTargetDisplay() noexcept = default;

		struct ZINET_GRAPHIC_LAYER_API CreateInfo
		{
			const Device& device;
			const Vma& vma;
			RenderPass& renderPass;
			std::uint32_t width;
			std::uint32_t height;
			vk::Format format;
			vk::Image swapChainImage;
			vk::ImageView depthBufferImageView;
		};

		void create(const CreateInfo& createInfo);

		vk::Image getSwapChainImage() const { return swapChainImage; }

		const ImageView& getSwapChainImageView() const { return swapChainImageView; }
		ImageView& getSwapChainImageView() { return swapChainImageView; }

	protected:

		void createImageView(const CreateInfo& createInfo);
		void createFramebuffer(const CreateInfo& createInfo);

		vk::Image swapChainImage;
		ImageView swapChainImageView;

	};
}