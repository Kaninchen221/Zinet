#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Device;

	class ZINET_GRAPHIC_LAYER_API RenderPass : public VulkanObject<vk::raii::RenderPass>
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

		vk::SubpassDependency createSubpassDependency();

		vk::RenderPassCreateInfo createRenderPassCreateInfo();

		void create(Device& device);

	protected:

		vk::AttachmentDescription attachmentDescription;
		vk::AttachmentReference attachmentReference;
		vk::SubpassDescription subpassDescription;
		vk::SubpassDependency subpassDependency;

	};

}