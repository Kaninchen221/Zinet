#pragma once

#include "Zinet/GraphicLayer/ZtGLQueue.h"

#include "gtest/gtest.h"

#include <utility>

namespace zt::gl::tests
{

	class QueueTests : public ::testing::Test
	{
	protected:

		Queue queue;

		QueueTests()
			: queue(std::move(vk::raii::Queue(std::nullptr_t())))
		{

		}

	};

	TEST_F(QueueTests, NoDefaultConstructorTest)
	{
		ASSERT_FALSE(std::is_default_constructible<Queue>::value);
	}

	TEST_F(QueueTests, GetInternalTest)
	{
		const vk::raii::Queue& internal = queue.getInternal();
	}

}