#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLDepthBuffer.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class DepthBufferTests : public ::testing::Test
	{
	protected:

		Renderer renderer;
		DepthBuffer depthBuffer;


		void SetUp() override
		{
			renderer.initialize();
			[[maybe_unused]] RendererContext& rendererContext = renderer.getRendererContext();
		}
	};

	TEST_F(DepthBufferTests, FindDepthFormat)
	{
		const PhysicalDevice& physicalDevice = renderer.getRendererContext().getPhysicalDevice();
		
		vk::Format format{};
		bool found = depthBuffer.findDepthFormat(physicalDevice, format);

		ASSERT_TRUE(found);
	}

	TEST_F(DepthBufferTests, Create)
	{
		const RendererContext& rendererContext = renderer.getRendererContext();

		vk::Format format;
		bool foundFormat = depthBuffer.findDepthFormat(rendererContext.getPhysicalDevice(), format);
		ASSERT_TRUE(foundFormat);
		
		depthBuffer.create(rendererContext, format);

		ASSERT_TRUE(depthBuffer.getImage().isValid());
		ASSERT_TRUE(depthBuffer.getImageView().isValid());
	}

	class DepthBufferSimpleTests : public ::testing::Test
	{
	protected:

		DepthBuffer depthBuffer;

	};

	TEST_F(DepthBufferSimpleTests, GetImage)
	{
		typedef const Image& (DepthBuffer::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&DepthBuffer::getImage));

		EXPECT_FALSE(depthBuffer.getImage().isValid());
	}

	TEST_F(DepthBufferSimpleTests, GetImageView)
	{
		typedef const ImageView& (DepthBuffer::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&DepthBuffer::getImageView));

		EXPECT_FALSE(depthBuffer.getImageView().isValid());
	}

}