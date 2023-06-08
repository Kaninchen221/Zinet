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

	TEST_F(DepthBufferSimpleTests, Getters)
	{
		typedef const Image& (DepthBuffer::* ExpectedFunction)() const;
		static_assert(IsFunctionEqual<ExpectedFunction>(&DepthBuffer::getImage));
	}

}