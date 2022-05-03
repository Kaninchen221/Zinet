#pragma once

#include "gtest/gtest.h"

#include "Zinet/GraphicLayer/ZtGLBufferCopy.h"
#include "Zinet/GraphicLayer/ZtGLStagingBuffer.h"
#include "Zinet/GraphicLayer/ZtGLVertexBuffer.h"

namespace zt::gl::tests
{

	class BufferCopyTests : public ::testing::Test
	{

	};

	TEST(CopyBuffer, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<BufferCopy, vk::BufferCopy>);
	}
}