#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{

	void RenderPass::createAttachmentDescription(vk::Format format)
	{
		attachmentDescription.format = format;
		attachmentDescription.samples = vk::SampleCountFlagBits::e1;
		attachmentDescription.loadOp = vk::AttachmentLoadOp::eClear;
		attachmentDescription.storeOp = vk::AttachmentStoreOp::eStore;
		attachmentDescription.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
		attachmentDescription.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
		attachmentDescription.initialLayout = vk::ImageLayout::eUndefined;
		attachmentDescription.finalLayout = vk::ImageLayout::ePresentSrcKHR;
	}

	void RenderPass::createAttachmentReference()
	{
		attachmentReference.attachment = 0;
		attachmentReference.layout = vk::ImageLayout::eColorAttachmentOptimal;
	}

	void RenderPass::createSubpassDescription()
	{
		subpassDescription.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
		subpassDescription.colorAttachmentCount = 1;
		subpassDescription.pColorAttachments = &attachmentReference;
		subpassDescription.pDepthStencilAttachment = &depthAttachmentReference;
	}

	void RenderPass::createSubpassDependency()
	{
		subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		subpassDependency.dstSubpass = 0;
		subpassDependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests;
		subpassDependency.srcAccessMask = static_cast<vk::AccessFlagBits>(0);
		subpassDependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests;
		subpassDependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite | vk::AccessFlagBits::eDepthStencilAttachmentWrite;
		subpassDependency.dependencyFlags = vk::DependencyFlagBits::eByRegion;
	}

	vk::RenderPassCreateInfo RenderPass::createRenderPassCreateInfo() const
	{
		vk::RenderPassCreateInfo createInfo;
		createInfo.attachmentCount = 2;
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

	void RenderPass::createDepthAttachmentDescription(vk::Format format)
	{
		attachmentDescription.format = format;
		attachmentDescription.samples = vk::SampleCountFlagBits::e1;
		attachmentDescription.loadOp = vk::AttachmentLoadOp::eClear;
		attachmentDescription.storeOp = vk::AttachmentStoreOp::eDontCare;
		attachmentDescription.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
		attachmentDescription.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
		attachmentDescription.initialLayout = vk::ImageLayout::eUndefined;
		attachmentDescription.finalLayout = vk::ImageLayout::eStencilAttachmentOptimal;
	}

	void RenderPass::createDepthAttachmentReference()
	{
		attachmentReference.attachment = 1;
		attachmentReference.layout = vk::ImageLayout::eDepthStencilAttachmentOptimal;
	}

}