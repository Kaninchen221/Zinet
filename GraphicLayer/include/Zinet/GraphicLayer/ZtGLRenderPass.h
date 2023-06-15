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

		const constexpr inline static vk::AttachmentDescription defaultAttachmentDescription{};
		const constexpr inline static vk::AttachmentReference defaultAttachmentReference{};

		const constexpr inline static size_t InvalidIndex = std::numeric_limits<size_t>::max();

	public:

		RenderPass() = default;
		RenderPass(const RenderPass& other) = default;
		RenderPass(RenderPass&& other) = default;

		RenderPass& operator = (const RenderPass& other) = default;
		RenderPass& operator = (RenderPass&& other) = default;

		~RenderPass() noexcept = default;

		const std::vector<vk::AttachmentDescription>& getAttachmentDescriptions() const { return attachmentDescriptions; }

		const std::vector<vk::AttachmentReference>& getAttachmentReferences() const { return attachmentReferences; }

		void createColorAttachmentDescription(vk::Format format);
		const vk::AttachmentDescription& getColorAttachmentDescription() const;

		void createColorAttachmentReference();
		const vk::AttachmentReference& getColorAttachmentReference() const;

		void createSubpassDescription();
		const vk::SubpassDescription& getSubpassDescription() const { return subpassDescription; }

		void createSubpassDependency();
		const vk::SubpassDependency& getSubpassDependency() const { return subpassDependency; }

		void createDepthAttachmentDescription(vk::Format format);
		const vk::AttachmentDescription& getDepthAttachmentDescription() const;

		void createDepthAttachmentReference();
		const vk::AttachmentReference& getDepthAttachmentReference() const;

		vk::RenderPassCreateInfo createRenderPassCreateInfo() const;

		void create(Device& device);

	protected:

		size_t colorAttachmentDescriptionIndex = InvalidIndex;
		size_t colorAttachmentReferenceIndex = InvalidIndex;

		size_t depthAttachmentDescriptionIndex = InvalidIndex;
		size_t depthAttachmentReferenceIndex = InvalidIndex;

		std::vector<vk::AttachmentDescription> attachmentDescriptions;
		std::vector<vk::AttachmentReference> attachmentReferences;
		vk::SubpassDescription subpassDescription;
		vk::SubpassDependency subpassDependency;
	};

}