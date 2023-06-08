#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLDepthBuffer.h"

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

	TEST_F(DepthBufferTests, Pass)
	{

	}

	class DepthBufferSimpleTests : public ::testing::Test
	{
	protected:

		DepthBuffer depthBuffer;

	};

	TEST_F(DepthBufferSimpleTests, GetImage)
	{
		typedef const Image& (DepthBuffer::* ExpectedFunction)() const;
		static_assert(IsFunctionEqual<ExpectedFunction>(&DepthBuffer::getImage));

		EXPECT_FALSE(depthBuffer.getImage().isValid());
	}

	TEST_F(DepthBufferSimpleTests, GetImageView)
	{
		typedef const ImageView& (DepthBuffer::* ExpectedFunction)() const;
		static_assert(IsFunctionEqual<ExpectedFunction>(&DepthBuffer::getImageView));

		EXPECT_FALSE(depthBuffer.getImageView().isValid());
	}

	TEST_F(DepthBufferSimpleTests, FindSupportedFormat)
	{
		typedef vk::Format (DepthBuffer::* ExpectedFunction)(const std::vector<vk::Format>&, vk::ImageTiling, vk::FormatFeatureFlags) const;
		static_assert(IsFunctionEqual<ExpectedFunction>(&DepthBuffer::findSupportedFormat));

		std::vector<vk::Format> candidates;
		vk::ImageTiling imageTiling{};
		vk::FormatFeatureFlags formatFeatureFlags{};
		
		[[maybe_unused]] vk::Format result = depthBuffer.findSupportedFormat(candidates, imageTiling, formatFeatureFlags);
	}
}