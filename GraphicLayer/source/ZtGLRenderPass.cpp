#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{
	RenderPass::RenderPass()
		: internal(std::nullptr_t{})
	{

	}

	vk::AttachmentDescription RenderPass::createAttachmentDescription(vk::Format format)
	{
		attachmentDescription.format = format;
		attachmentDescription.samples = vk::SampleCountFlagBits::e1;
		attachmentDescription.loadOp = vk::AttachmentLoadOp::eClear;
		attachmentDescription.storeOp = vk::AttachmentStoreOp::eStore;
		attachmentDescription.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
		attachmentDescription.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
		attachmentDescription.initialLayout = vk::ImageLayout::eUndefined;
		attachmentDescription.finalLayout = vk::ImageLayout::ePresentSrcKHR;

		return attachmentDescription;
	}

	vk::AttachmentReference RenderPass::createAttachmentReference()
	{
		attachmentReference.attachment = 0;
		attachmentReference.layout = vk::ImageLayout::eColorAttachmentOptimal;

		return attachmentReference;
	}

	vk::SubpassDescription RenderPass::createSubpassDescription()
	{
		subpassDescription.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
		subpassDescription.colorAttachmentCount = 1;
		subpassDescription.pColorAttachments = &attachmentReference;

		return subpassDescription;
	}

	vk::RenderPassCreateInfo RenderPass::createRenderPassCreateInfo()
	{
		vk::RenderPassCreateInfo createInfo;
		createInfo.attachmentCount = 1;
		createInfo.pAttachments = &attachmentDescription;
		createInfo.subpassCount = 1;
		createInfo.pSubpasses = &subpassDescription;

		return createInfo;
	}

	vk::raii::RenderPass& RenderPass::getInternal()
	{
		return internal;
	}

	void RenderPass::create(Device& device)
	{
		vk::RenderPassCreateInfo createInfo = createRenderPassCreateInfo();
		internal = std::move(vk::raii::RenderPass{ device.getInternal(), createInfo });
	}

}