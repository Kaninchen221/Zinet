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

	};

	TEST_F(QueueTests, GetInternalTest)
	{
		const vk::raii::Queue& internal = queue.getInternal();
	}

}