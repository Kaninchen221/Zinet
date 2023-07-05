#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderTarget.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLVma.h"
#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLDebugUtilsMessenger.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{
	class RenderTargetBaseSimpleTests : public ::testing::Test
	{
	protected:

		static_assert(std::is_default_constructible_v<RenderTargetBase>);
		//static_assert(std::is_copy_constructible_v<RenderTargetBase>);
		static_assert(std::is_move_constructible_v<RenderTargetBase>);

		class TestClass : public RenderTargetBase
		{

		};

		TestClass testClass;
	};

	TEST_F(RenderTargetBaseSimpleTests, GetFramebuffer)
	{
		typedef Framebuffer& (RenderTargetBase::* ExpectedFunctionDeclaration)();
		static_assert(zt::core::IsFunctionEqual<ExpectedFunctionDeclaration>(&RenderTargetBase::getFramebuffer));

		Framebuffer& framebuffer = testClass.getFramebuffer();
		ASSERT_FALSE(framebuffer.isValid());
	}

	class RenderTargetSimpleTests : public ::testing::Test
	{
	protected:

		RenderTarget renderTarget;

		static_assert(std::is_base_of_v<RenderTargetBase, RenderTarget>);
	};

	TEST_F(RenderTargetSimpleTests, GetImage)
	{
		typedef const Image& (RenderTarget::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&RenderTarget::getImage);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		const Image& image = renderTarget.getImage();
		ASSERT_EQ(image, nullptr);
	}

	TEST_F(RenderTargetSimpleTests, GetImageView)
	{
		typedef const ImageView& (RenderTarget::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&RenderTarget::getImageView);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		const ImageView& imageView = renderTarget.getImageView();
		ASSERT_EQ(imageView, nullptr);
	}

	class RenderTargetTests : public ::testing::Test
	{
	protected:

		RendererContext rendererContext;
		RenderTarget renderTarget;

		void SetUp() override
		{
			GLFW::Init();
			rendererContext.initialize();
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST_F(RenderTargetTests, Create)
	{
		RenderPass renderPass;
		renderPass.createColorAttachmentDescription(vk::Format::eR8G8B8A8Srgb);
		renderPass.createColorAttachmentReference();
		renderPass.createSubpassDependency();
		renderPass.createSubpassDescription();

		vk::RenderPassCreateInfo createInfo = renderPass.createRenderPassCreateInfo();
		renderPass.create(rendererContext.getDevice(), createInfo);

		RenderTarget::CreateInfo renderTargetCreateInfo
		{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.renderPass = renderPass,
			.width = 400u,
			.height = 400u,
			.format = vk::Format::eR8G8B8A8Srgb
		};
		
		renderTarget.create(renderTargetCreateInfo);
		
		const Image& image = renderTarget.getImage();
		ASSERT_NE(image, nullptr);
		
		const ImageView& imageView = renderTarget.getImageView();
		ASSERT_NE(imageView, nullptr);
		
		const Framebuffer& framebuffer = renderTarget.getFramebuffer();
		ASSERT_NE(framebuffer, nullptr);
	}

	class RenderTargetDisplaySimpleTests : public ::testing::Test
	{
	protected:

		RenderTargetDisplay renderTargetDisplay;

		static_assert(std::is_base_of_v<RenderTargetBase, RenderTarget>);
	};

	TEST_F(RenderTargetDisplaySimpleTests, Getters)
	{
		typedef vk::Image (RenderTargetDisplay::* ExpectedFunctionDeclaration)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunctionDeclaration>(&RenderTargetDisplay::getSwapChainImage));

		vk::Image vkSwapChainImage = renderTargetDisplay.getSwapChainImage();
		EXPECT_FALSE(vkSwapChainImage);

		const ImageView& imageView = renderTargetDisplay.getSwapChainImageView();
		EXPECT_FALSE(imageView.isValid());
 	}

	class RenderTargetDisplayTests : public ::testing::Test
	{
	protected:

		RendererContext rendererContext;
		RenderTargetDisplay renderTargetDisplay;

		void SetUp() override
		{
			GLFW::Init();
			rendererContext.initialize();
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST_F(RenderTargetDisplayTests, Create)
	{
		RenderTargetDisplay::CreateInfo renderTargetCreateInfo
		{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.renderPass = rendererContext.getRenderPass(),
			.width = 400u,
			.height = 400u,
			.format = vk::Format::eB8G8R8A8Srgb,
			.swapChainImage = rendererContext.getSwapChain().getImages()[0],
			.depthBufferImageView = rendererContext.getDepthBuffer().getImageView().getVk()
		};

		renderTargetDisplay.create(renderTargetCreateInfo);

		const vk::Image& vkImage = renderTargetDisplay.getSwapChainImage();
		ASSERT_TRUE(vkImage);

		const ImageView& swapChainImageView = renderTargetDisplay.getSwapChainImageView();
		ASSERT_TRUE(swapChainImageView.isValid());

		const Framebuffer& framebuffer = renderTargetDisplay.getFramebuffer();
		ASSERT_TRUE(framebuffer.isValid());
	}
}
