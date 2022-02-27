#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Device;

	class ZINET_GRAPHIC_LAYER_API RenderPass
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Render Pass");

	public:

		RenderPass();
		RenderPass(const RenderPass& other) = default;
		RenderPass(RenderPass&& other) = default;

		RenderPass& operator = (const RenderPass& other) = default;
		RenderPass& operator = (RenderPass&& other) = default;

		~RenderPass() noexcept = default;

		vk::AttachmentDescription createAttachmentDescription(vk::Format format);

		vk::AttachmentReference createAttachmentReference();

		vk::SubpassDescription createSubpassDescription();

		vk::RenderPassCreateInfo createRenderPassCreateInfo();

		vk::raii::RenderPass& getInternal();

		void create(Device& device);

	protected:

		vk::AttachmentDescription attachmentDescription;
		vk::AttachmentReference attachmentReference;
		vk::SubpassDescription subpassDescription;

		vk::raii::RenderPass internal;

	};

}