#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class RendererTests : public ::testing::Test
	{
	protected:

		Renderer renderer;

	};

	TEST_F(RendererTests, Initialize)
	{
		renderer.initialize();

		const Instance& instance = renderer.getInstance();
		ASSERT_NE(instance, vk::raii::Instance(std::nullptr_t{}));
	}

	TEST_F(RendererTests, GetContext)
	{
		const Context& context = renderer.getContext();
	}

	TEST_F(RendererTests, GetInstance)
	{
		const Instance& instance = renderer.getInstance();
		ASSERT_EQ(instance, vk::raii::Instance(std::nullptr_t{}));
	}

}
