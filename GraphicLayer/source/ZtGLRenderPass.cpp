#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{

	void RenderPass::createColorAttachmentDescription(vk::Format format)
	{
		vk::AttachmentDescription colorAttachmentDescription{};
		colorAttachmentDescription.format = format;
		colorAttachmentDescription.samples = vk::SampleCountFlagBits::e1;
		colorAttachmentDescription.loadOp = vk::AttachmentLoadOp::eClear;
		colorAttachmentDescription.storeOp = vk::AttachmentStoreOp::eStore;
		colorAttachmentDescription.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
		colorAttachmentDescription.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
		colorAttachmentDescription.initialLayout = vk::ImageLayout::eUndefined;
		colorAttachmentDescription.finalLayout = vk::ImageLayout::ePresentSrcKHR;

		attachmentDescriptions.push_back(colorAttachmentDescription);
		colorAttachmentDescriptionIndex = attachmentDescriptions.size() - 1;
	}

	void RenderPass::createColorAttachmentReference()
	{
		vk::AttachmentReference colorAttachmentReference{};
		colorAttachmentReference.attachment = 0;
		colorAttachmentReference.layout = vk::ImageLayout::eColorAttachmentOptimal;

		attachmentReferences.push_back(colorAttachmentReference);
		colorAttachmentReferenceIndex = attachmentReferences.size() - 1;
	}

	void RenderPass::createSubpassDescription()
	{
		subpassDescription.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
		subpassDescription.colorAttachmentCount = 1;

		if (colorAttachmentDescriptionIndex != InvalidIndex && colorAttachmentReferenceIndex != InvalidIndex)
			subpassDescription.pColorAttachments = &getColorAttachmentReference();

		if (depthAttachmentDescriptionIndex != InvalidIndex && depthAttachmentReferenceIndex != InvalidIndex)
			subpassDescription.pDepthStencilAttachment = &getDepthAttachmentReference();
	}

	void RenderPass::createSubpassDependency()
	{
		subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		subpassDependency.dstSubpass = 0;
		subpassDependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests;
		subpassDependency.srcAccessMask = static_cast<vk::AccessFlagBits>(0);
		subpassDependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests;
		subpassDependency.dependencyFlags = vk::DependencyFlagBits::eByRegion;

		if (depthAttachmentDescriptionIndex && depthAttachmentReferenceIndex)
			subpassDependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite | vk::AccessFlagBits::eDepthStencilAttachmentWrite;
	}

	vk::RenderPassCreateInfo RenderPass::createRenderPassCreateInfo() const
	{
		vk::RenderPassCreateInfo createInfo;
		createInfo.attachmentCount = static_cast<std::uint32_t>(attachmentDescriptions.size());
		createInfo.pAttachments = attachmentDescriptions.data();
		createInfo.subpassCount = 1;
		createInfo.pSubpasses = &subpassDescription;
		createInfo.dependencyCount = 1;
		createInfo.pDependencies = &subpassDependency;

		return createInfo;
	}

	void RenderPass::create(Device& device)
	{
		// TODO (Low) CreateInfo as function param
		vk::RenderPassCreateInfo createInfo = createRenderPassCreateInfo();
		internal = std::move(vk::raii::RenderPass{ device.getInternal(), createInfo });
	}

	void RenderPass::createDepthAttachmentDescription(vk::Format format)
	{
		vk::AttachmentDescription depthAttachmentDescription{};
		depthAttachmentDescription.format = format;
		depthAttachmentDescription.samples = vk::SampleCountFlagBits::e1;
		depthAttachmentDescription.loadOp = vk::AttachmentLoadOp::eClear;
		depthAttachmentDescription.storeOp = vk::AttachmentStoreOp::eDontCare;
		depthAttachmentDescription.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
		depthAttachmentDescription.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
		depthAttachmentDescription.initialLayout = vk::ImageLayout::eUndefined;
		depthAttachmentDescription.finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;

		attachmentDescriptions.push_back(depthAttachmentDescription);
		depthAttachmentDescriptionIndex = attachmentDescriptions.size() - 1;
	}

	void RenderPass::createDepthAttachmentReference()
	{
		vk::AttachmentReference depthAttachmentReference{};
		depthAttachmentReference.attachment = 1;
		depthAttachmentReference.layout = vk::ImageLayout::eDepthStencilAttachmentOptimal;

		attachmentReferences.push_back(depthAttachmentReference);
		depthAttachmentReferenceIndex = attachmentReferences.size() - 1;
	}

	const vk::AttachmentDescription& RenderPass::getColorAttachmentDescription() const
	{
		if (colorAttachmentDescriptionIndex != InvalidIndex)
			return attachmentDescriptions[colorAttachmentDescriptionIndex];

		return defaultAttachmentDescription;
	}

	const vk::AttachmentReference& RenderPass::getColorAttachmentReference() const
	{
		if (colorAttachmentReferenceIndex != InvalidIndex)
			return attachmentReferences[colorAttachmentReferenceIndex];

		return defaultAttachmentReference;
	}

	const vk::AttachmentDescription& RenderPass::getDepthAttachmentDescription() const
	{
		if (depthAttachmentDescriptionIndex != InvalidIndex)
			return attachmentDescriptions[depthAttachmentDescriptionIndex];

		return defaultAttachmentDescription;
	}

	const vk::AttachmentReference& RenderPass::getDepthAttachmentReference() const
	{
		if (depthAttachmentReferenceIndex != InvalidIndex)
			return attachmentReferences[depthAttachmentReferenceIndex];

		return defaultAttachmentReference;
	}

}