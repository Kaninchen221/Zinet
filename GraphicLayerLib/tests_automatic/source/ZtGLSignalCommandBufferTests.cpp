#pragma once

#include "Zinet/GraphicLayer/ZtGLSignalCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"

#include "Zinet/Window/ZtGLFW.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{
	class SignalCommandBufferSimpleTests : public ::testing::Test
	{
	protected:

		SignalCommandBuffer signalCommandBuffer;

		static_assert(std::is_default_constructible_v<SignalCommandBuffer>);
		static_assert(!std::is_copy_constructible_v<SignalCommandBuffer>);
		static_assert(!std::is_copy_assignable_v<SignalCommandBuffer>);
		static_assert(std::is_move_constructible_v<SignalCommandBuffer>);
		static_assert(std::is_move_assignable_v<SignalCommandBuffer>);
		static_assert(std::is_destructible_v<SignalCommandBuffer>);
	};

	TEST_F(SignalCommandBufferSimpleTests, GetCommandBuffer)
	{
		const CommandBuffer& commandBuffer = signalCommandBuffer.getCommandBuffer();
		ASSERT_FALSE(commandBuffer.isValid());
	}

	TEST_F(SignalCommandBufferSimpleTests, GetFence)
	{
		const Fence& fence = signalCommandBuffer.getFence();
		ASSERT_FALSE(fence.isValid());
	}

	class SignalCommandBufferTests : public ::testing::Test
	{
	protected:

		RendererContext rendererContext;
		SignalCommandBuffer signalCommandBuffer;

		void SetUp() override
		{
			rendererContext.initialize();
		}

		void TearDown() override
		{
		}
	};

	TEST_F(SignalCommandBufferTests, Create)
	{
		signalCommandBuffer.create(rendererContext);

		const CommandBuffer& commandBuffer = signalCommandBuffer.getCommandBuffer();
		EXPECT_TRUE(commandBuffer.isValid());

		const Fence& fence = signalCommandBuffer.getFence();
		EXPECT_TRUE(fence.isValid());
	}
}
