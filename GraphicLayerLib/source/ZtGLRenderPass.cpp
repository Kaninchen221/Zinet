#include "Zinet/GraphicLayer/ZtGLRenderPass.hpp"
#include "Zinet/GraphicLayer/ZtGLDevice.hpp"

namespace zt::gl
{

	void RenderPass::createColorAttachmentDescription(vk::Format format)
	{
		vk::AttachmentDescription colorAttachmentDescription{};
		colorAttachmentDescription.format = format;
		colorAttachmentDescription.samples = vk::SampleCountFlagBits::e1;
		colorAttachmentDescription.loadOp = vk::AttachmentLoadOp::eClear;
		colorAttachmentDescription.storeOp = vk::AttachmentStoreOp::eStore;
		colorAttachmentDescription.stencilLoadOp = vk::AttachmentLoadOp::eLoad;
		colorAttachmentDescription.stencilStoreOp = vk::AttachmentStoreOp::eStore;
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

	void RenderPass::create(const Device& device, const vk::RenderPassCreateInfo& createInfo)
	{
		vk::raii::RenderPass tempRenderPass{ device.getInternal(), createInfo };
		internal.swap(tempRenderPass);
		tempRenderPass.release();
	}

	void RenderPass::createDepthAttachmentDescription(vk::Format format)
	{
		vk::AttachmentDescription attachmentDescription{};
		attachmentDescription.format = format;
		attachmentDescription.samples = vk::SampleCountFlagBits::e1;
		attachmentDescription.loadOp = vk::AttachmentLoadOp::eClear;
		attachmentDescription.storeOp = vk::AttachmentStoreOp::eStore;
		attachmentDescription.stencilLoadOp = vk::AttachmentLoadOp::eClear;
		attachmentDescription.stencilStoreOp = vk::AttachmentStoreOp::eStore;
		attachmentDescription.initialLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;
		attachmentDescription.finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;

		attachmentDescriptions.push_back(attachmentDescription);
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