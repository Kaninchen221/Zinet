#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLrenderer.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class RendererTests : public ::testing::Test
	{
	protected:

		Renderer renderer;

	};

	TEST_F(RendererTests, PassTest)
	{

	}

}