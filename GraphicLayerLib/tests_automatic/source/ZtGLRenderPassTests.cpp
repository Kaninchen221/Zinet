#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"

#include "Zinet/Window/ZtWindow.h"
#include "Zinet/Window/ZtGLFW.h"

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

	TEST_F(RenderPassTests, GetAttachmentDescriptions)
	{
		typedef const std::vector<vk::AttachmentDescription>& (RenderPass::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&RenderPass::getAttachmentDescriptions));
	}

	TEST_F(RenderPassTests, GetAttachmentReferences)
	{
		typedef const std::vector<vk::AttachmentReference>& (RenderPass::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&RenderPass::getAttachmentReferences));
	}

	TEST_F(RenderPassTests, AttachmentDescriptions)
	{
		typedef const vk::AttachmentDescription& (RenderPass::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&RenderPass::getColorAttachmentDescription));

		vk::Format swapChainFormat{};
		renderPass.createColorAttachmentDescription(swapChainFormat);
		const vk::AttachmentDescription& attachmentDescription = renderPass.getColorAttachmentDescription();

		ASSERT_NE(attachmentDescription, vk::AttachmentDescription{});
	}

	TEST_F(RenderPassTests, AttachmentReferenceTest)
	{
		typedef const vk::AttachmentReference& (RenderPass::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&RenderPass::getColorAttachmentReference));

		renderPass.createColorAttachmentReference();
		const vk::AttachmentReference& attachmentReference = renderPass.getColorAttachmentReference();

		ASSERT_NE(attachmentReference, vk::AttachmentReference{});
	}

	TEST_F(RenderPassTests, SubpassDescriptionTest)
	{
		typedef const vk::SubpassDescription& (RenderPass::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&RenderPass::getSubpassDescription));

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
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&RenderPass::getSubpassDependency));

		renderPass.createSubpassDependency();
		const vk::SubpassDependency& subpassDependency = renderPass.getSubpassDependency();

		ASSERT_NE(subpassDependency, vk::SubpassDependency{});
	}

	TEST_F(RenderPassTests, DepthAttachmentDescriptions)
	{
		typedef const vk::AttachmentDescription& (RenderPass::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&RenderPass::getDepthAttachmentDescription));

		vk::Format format{};
		renderPass.createDepthAttachmentDescription(format);
		const vk::AttachmentDescription& attachmentDescription = renderPass.getDepthAttachmentDescription();

		ASSERT_NE(attachmentDescription, vk::AttachmentDescription{});
	}

	TEST_F(RenderPassTests, DepthAttachmentReferenceTest)
	{
		typedef const vk::AttachmentReference& (RenderPass::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&RenderPass::getDepthAttachmentReference));

		renderPass.createDepthAttachmentReference();
		const vk::AttachmentReference& attachmentReference = renderPass.getDepthAttachmentReference();

		ASSERT_NE(attachmentReference, vk::AttachmentReference{});
	}

	TEST_F(RenderPassTests, CreateTest)
	{
		wd::GLFW::Init();

		RendererContext rendererContext;
		rendererContext.initialize();

		renderPass.createColorAttachmentDescription(vk::Format::eR8G8Unorm);
		renderPass.createColorAttachmentReference();
		renderPass.createDepthAttachmentDescription(rendererContext.getDepthStencilBufferFormat());
		renderPass.createDepthAttachmentReference();
		renderPass.createSubpassDescription();
		renderPass.createSubpassDependency();

		vk::RenderPassCreateInfo createInfo = renderPass.createRenderPassCreateInfo();
		renderPass.create(rendererContext.getDevice(), createInfo);
		vk::raii::RenderPass& internal = renderPass.getInternal();

		ASSERT_NE(*internal, *vk::raii::RenderPass{ std::nullptr_t{} });

		renderPass.clear();

		wd::GLFW::Deinit();
	}
}