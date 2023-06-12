#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class RenderPassTests : public ::testing::Test
	{
	protected:

		RenderPass renderPass;

	};

	TEST(RenderPass, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<RenderPass, VulkanObject<vk::raii::RenderPass>>);
	}

	TEST_F(RenderPassTests, AttachmentDescriptions)
	{
		typedef const vk::AttachmentDescription& (RenderPass::* ExpectedFunction)() const;
		static_assert(IsFunctionEqual<ExpectedFunction>(&RenderPass::getAttachmentDescription));

		vk::Format swapChainFormat{};
		renderPass.createAttachmentDescription(swapChainFormat);
		const vk::AttachmentDescription& attachmentDescription = renderPass.getAttachmentDescription();

		ASSERT_NE(attachmentDescription, vk::AttachmentDescription{});
	}

	TEST_F(RenderPassTests, AttachmentReferenceTest)
	{
		typedef const vk::AttachmentReference& (RenderPass::* ExpectedFunction)() const;
		static_assert(IsFunctionEqual<ExpectedFunction>(&RenderPass::getAttachmentReference));

		renderPass.createAttachmentReference();
		const vk::AttachmentReference& attachmentReference = renderPass.getAttachmentReference();

		ASSERT_NE(attachmentReference, vk::AttachmentReference{});
	}

	TEST_F(RenderPassTests, SubpassDescriptionTest)
	{
		typedef const vk::SubpassDescription& (RenderPass::* ExpectedFunction)() const;
		static_assert(IsFunctionEqual<ExpectedFunction>(&RenderPass::getSubpassDescription));

		renderPass.createSubpassDescription();
		const vk::SubpassDescription& subpassDescription = renderPass.getSubpassDescription();

		ASSERT_NE(subpassDescription, vk::SubpassDescription{});
	}

	TEST_F(RenderPassTests, CreateRenderPassCreateInfoTest)
	{
		vk::RenderPassCreateInfo createInfo = renderPass.createRenderPassCreateInfo();

		ASSERT_NE(createInfo, vk::RenderPassCreateInfo{});
	}

	TEST_F(RenderPassTests, SubpassDependencyTest)
	{
		typedef const vk::SubpassDependency& (RenderPass::* ExpectedFunction)() const;
		static_assert(IsFunctionEqual<ExpectedFunction>(&RenderPass::getSubpassDependency));

		renderPass.createSubpassDependency();
		const vk::SubpassDependency& subpassDependency = renderPass.getSubpassDependency();

		ASSERT_NE(subpassDependency, vk::SubpassDependency{});
	}

	TEST_F(RenderPassTests, DepthAttachmentDescriptions)
	{
		typedef const vk::AttachmentDescription& (RenderPass::* ExpectedFunction)() const;
		static_assert(IsFunctionEqual<ExpectedFunction>(&RenderPass::getDepthAttachmentDescription));

		vk::Format format{};
		renderPass.createDepthAttachmentDescription(format);
		const vk::AttachmentDescription& attachmentDescription = renderPass.getDepthAttachmentDescription();

		ASSERT_NE(attachmentDescription, vk::AttachmentDescription{});
	}

	TEST_F(RenderPassTests, DepthAttachmentReferenceTest)
	{
		typedef const vk::AttachmentReference& (RenderPass::* ExpectedFunction)() const;
		static_assert(IsFunctionEqual<ExpectedFunction>(&RenderPass::getDepthAttachmentReference));

		renderPass.createDepthAttachmentReference();
		const vk::AttachmentReference& attachmentReference = renderPass.getDepthAttachmentReference();

		ASSERT_NE(attachmentReference, vk::AttachmentReference{});
	}

	TEST_F(RenderPassTests, CreateTest)
	{
		GLFW::Init();

		RendererContext rendererContext;
		rendererContext.initialize();

		renderPass.createAttachmentDescription(vk::Format::eR8G8Unorm);
		renderPass.createAttachmentReference();
		renderPass.createDepthAttachmentDescription(rendererContext.getDepthBufferFormat());
		renderPass.createDepthAttachmentReference();
		renderPass.createSubpassDescription();
		renderPass.createSubpassDependency();

		renderPass.create(rendererContext.getDevice());
		vk::raii::RenderPass& internal = renderPass.getInternal();

		ASSERT_NE(*internal, *vk::raii::RenderPass{ std::nullptr_t{} });

		renderPass.~RenderPass();

		GLFW::Deinit();
	}
}