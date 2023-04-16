#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{

	const vk::AttachmentDescription& RenderPass::createAttachmentDescription(vk::Format format)
	{
		attachmentDescription.format = format;
		attachmentDescription.samples = vk::SampleCountFlagBits::e1;
		attachmentDescription.loadOp = vk::AttachmentLoadOp::eClear;
		attachmentDescription.loadOp = vk::AttachmentLoadOp::eDontCare; // TODO I add it while trying to render 2 objects 
		attachmentDescription.storeOp = vk::AttachmentStoreOp::eStore;
		attachmentDescription.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
		attachmentDescription.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
		attachmentDescription.initialLayout = vk::ImageLayout::eUndefined;
		attachmentDescription.finalLayout = vk::ImageLayout::ePresentSrcKHR;

		return attachmentDescription;
	}

	const vk::AttachmentReference& RenderPass::createAttachmentReference()
	{
		attachmentReference.attachment = 0;
		attachmentReference.layout = vk::ImageLayout::eColorAttachmentOptimal;

		return attachmentReference;
	}

	const vk::SubpassDescription& RenderPass::createSubpassDescription()
	{
		subpassDescription.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
		subpassDescription.colorAttachmentCount = 1;
		subpassDescription.pColorAttachments = &attachmentReference;

		return subpassDescription;
	}

	const vk::SubpassDependency& RenderPass::createSubpassDependency()
	{
		subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		subpassDependency.dstSubpass = 0;
		subpassDependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
		subpassDependency.srcAccessMask = static_cast<vk::AccessFlagBits>(0);
		subpassDependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
		subpassDependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;
		subpassDependency.dependencyFlags = vk::DependencyFlagBits::eByRegion;

		return subpassDependency;
	}

	vk::RenderPassCreateInfo RenderPass::createRenderPassCreateInfo() const
	{
		vk::RenderPassCreateInfo createInfo;
		createInfo.attachmentCount = 1;
		createInfo.pAttachments = &attachmentDescription;
		createInfo.subpassCount = 1;
		createInfo.pSubpasses = &subpassDescription;
		createInfo.dependencyCount = 1;
		createInfo.pDependencies = &subpassDependency;

		return createInfo;
	}

	void RenderPass::create(Device& device)
	{
		vk::RenderPassCreateInfo createInfo = createRenderPassCreateInfo();
		internal = std::move(vk::raii::RenderPass{ device.getInternal(), createInfo });
	}

}