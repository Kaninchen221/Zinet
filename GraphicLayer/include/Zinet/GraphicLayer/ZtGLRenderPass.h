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

		const std::array<vk::AttachmentDescription, 2u>& getAttachmentDescriptions() const { return attachmentDescriptions; }

		const std::array<vk::AttachmentReference, 2u>& getAttachmentReferences() const { return attachmentReferences; }

		// TODO (mid) update names
		void createAttachmentDescription(vk::Format format);
		const vk::AttachmentDescription& getAttachmentDescription() const { return attachmentDescriptions[0]; }

		void createAttachmentReference();
		const vk::AttachmentReference& getAttachmentReference() const { return attachmentReferences[0]; }

		void createSubpassDescription();
		const vk::SubpassDescription& getSubpassDescription() const { return subpassDescription; }

		void createSubpassDependency();
		const vk::SubpassDependency& getSubpassDependency() const { return subpassDependency; }

		void createDepthAttachmentDescription(vk::Format format);
		const vk::AttachmentDescription& getDepthAttachmentDescription() const { return attachmentDescriptions[1]; }

		void createDepthAttachmentReference();
		const vk::AttachmentReference& getDepthAttachmentReference() const { return attachmentReferences[1]; }

		vk::RenderPassCreateInfo createRenderPassCreateInfo() const;

		void create(Device& device);

	protected:

		std::array<vk::AttachmentDescription, 2u> attachmentDescriptions;
		std::array<vk::AttachmentReference, 2u> attachmentReferences;
		vk::SubpassDescription subpassDescription;
		vk::SubpassDependency subpassDependency;

	};

}