#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{

	void RenderPass::createAttachmentDescription(vk::Format format)
	{
		vk::AttachmentDescription& colorAttachmentDescription = attachmentDescriptions[0];
		colorAttachmentDescription.format = format;
		colorAttachmentDescription.samples = vk::SampleCountFlagBits::e1;
		colorAttachmentDescription.loadOp = vk::AttachmentLoadOp::eClear;
		colorAttachmentDescription.storeOp = vk::AttachmentStoreOp::eStore;
		colorAttachmentDescription.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
		colorAttachmentDescription.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
		colorAttachmentDescription.initialLayout = vk::ImageLayout::eUndefined;
		colorAttachmentDescription.finalLayout = vk::ImageLayout::ePresentSrcKHR;
	}

	void RenderPass::createAttachmentReference()
	{
		vk::AttachmentReference& colorAttachmentReference = attachmentReferences[0];
		colorAttachmentReference.attachment = 0;
		colorAttachmentReference.layout = vk::ImageLayout::eColorAttachmentOptimal;
	}

	void RenderPass::createSubpassDescription()
	{
		subpassDescription.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
		subpassDescription.colorAttachmentCount = 1;
		subpassDescription.pColorAttachments = &getAttachmentReference();
		subpassDescription.pDepthStencilAttachment = &getDepthAttachmentReference();
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
		vk::RenderPassCreateInfo createInfo = createRenderPassCreateInfo();
		internal = std::move(vk::raii::RenderPass{ device.getInternal(), createInfo });
	}

	void RenderPass::createDepthAttachmentDescription(vk::Format format)
	{
		vk::AttachmentDescription& depthAttachmentDescription = attachmentDescriptions[1];
		depthAttachmentDescription.format = format;
		depthAttachmentDescription.samples = vk::SampleCountFlagBits::e1;
		depthAttachmentDescription.loadOp = vk::AttachmentLoadOp::eClear;
		depthAttachmentDescription.storeOp = vk::AttachmentStoreOp::eDontCare;
		depthAttachmentDescription.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
		depthAttachmentDescription.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
		depthAttachmentDescription.initialLayout = vk::ImageLayout::eUndefined;
		depthAttachmentDescription.finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;
	}

	void RenderPass::createDepthAttachmentReference()
	{
		vk::AttachmentReference& depthAttachmentReference = attachmentReferences[1];
		depthAttachmentReference.attachment = 1;
		depthAttachmentReference.layout = vk::ImageLayout::eDepthStencilAttachmentOptimal;
	}

}