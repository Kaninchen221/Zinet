#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderer.hpp"
#include "Zinet/GraphicLayer/ZtGLDepthStencilBuffer.hpp"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.hpp"

#include "Zinet/Window/ZtGLFW.hpp"

#include "Zinet/Core/ZtTypeTraits.hpp"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class DepthStencilBufferTests : public ::testing::Test
	{
	protected:

		Renderer renderer;
		DepthStencilBuffer depthStencilBuffer;


		void SetUp() override
		{
			renderer.initialize();
			[[maybe_unused]] RendererContext& rendererContext = renderer.getRendererContext();
		}
	};

	TEST_F(DepthStencilBufferTests, FindDepthFormat)
	{
		const PhysicalDevice& physicalDevice = renderer.getRendererContext().getPhysicalDevice();
		
		vk::Format format{};
		bool found = depthStencilBuffer.findDepthFormat(physicalDevice, format);

		ASSERT_TRUE(found);
	}

	TEST_F(DepthStencilBufferTests, Create)
	{
		RendererContext& rendererContext = renderer.getRendererContext();

		vk::Format format;
		bool foundFormat = depthStencilBuffer.findDepthFormat(rendererContext.getPhysicalDevice(), format);
		ASSERT_TRUE(foundFormat);
		
		ASSERT_FALSE(depthStencilBuffer.isValid());
		depthStencilBuffer.create(rendererContext, format);

		ASSERT_TRUE(depthStencilBuffer.getImage().isValid());
		ASSERT_TRUE(depthStencilBuffer.getImageView().isValid());
		ASSERT_TRUE(depthStencilBuffer.isValid());
	}

	class DepthStencilBufferSimpleTests : public ::testing::Test
	{
	protected:

		DepthStencilBuffer depthStencilBuffer;

	};

	TEST_F(DepthStencilBufferSimpleTests, GetImage)
	{
		typedef const Image& (DepthStencilBuffer::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&DepthStencilBuffer::getImage));

		EXPECT_FALSE(depthStencilBuffer.getImage().isValid());
	}

	TEST_F(DepthStencilBufferSimpleTests, GetImageView)
	{
		typedef const ImageView& (DepthStencilBuffer::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&DepthStencilBuffer::getImageView));

		EXPECT_FALSE(depthStencilBuffer.getImageView().isValid());
	}

}