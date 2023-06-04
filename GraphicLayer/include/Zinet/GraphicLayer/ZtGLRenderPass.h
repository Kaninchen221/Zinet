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

		inline static ConsoleLogger Logger = ConsoleLogger::Create("RenderPass");

	public:

		RenderPass() = default;
		RenderPass(const RenderPass& other) = default;
		RenderPass(RenderPass&& other) = default;

		RenderPass& operator = (const RenderPass& other) = default;
		RenderPass& operator = (RenderPass&& other) = default;

		~RenderPass() noexcept = default;

		void createAttachmentDescription(vk::Format format);
		const vk::AttachmentDescription& getAttachmentDescription() const { return attachmentDescription; }

		void createAttachmentReference();
		const vk::AttachmentReference& getAttachmentReference() const { return attachmentReference; }

		void createSubpassDescription();
		const vk::SubpassDescription& getSubpassDescription() const { return subpassDescription; }

		void createSubpassDependency();
		const vk::SubpassDependency& getSubpassDependency() const { return subpassDependency; }

		vk::RenderPassCreateInfo createRenderPassCreateInfo() const;

		void create(Device& device);

	protected:

		vk::AttachmentDescription attachmentDescription;
		vk::AttachmentReference attachmentReference;
		vk::SubpassDescription subpassDescription;
		vk::SubpassDependency subpassDependency;

	};

}