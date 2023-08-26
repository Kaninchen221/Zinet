#pragma once

#include "Zinet/GraphicLayer/Imgui/ZtGLImgui.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class ImguiTests : public ::testing::Test
	{
	protected:

		Renderer renderer;
		Imgui imgui;

		void SetUp() override
		{
			GLFW::Init(false);
			renderer.initialize();
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST_F(ImguiTests, Init)
	{
		RendererContext& rendererContext = renderer.getRendererContext();
		imgui.preinit(rendererContext);
		imgui.init(rendererContext);

		const DescriptorPool& descriptorPool = imgui.getDescriptorPool();
		ASSERT_TRUE(descriptorPool.isValid());
	}

	class ImguiSimpleTests : public ::testing::Test
	{
	protected:

		Imgui imgui;

	};

	TEST_F(ImguiSimpleTests, GetDescriptorPool)
	{
		typedef const DescriptorPool& (Imgui::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Imgui::getDescriptorPool));

		[[maybe_unused]] const DescriptorPool& descriptorPool = imgui.getDescriptorPool();
	}
}