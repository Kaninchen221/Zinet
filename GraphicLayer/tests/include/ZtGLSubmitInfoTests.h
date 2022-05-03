#pragma once

#include "gtest/gtest.h"

#include "Zinet/GraphicLayer/ZtGLSubmitInfo.h"

namespace zt::gl::tests
{

	class SubmitInfoTests : public ::testing::Test
	{
		SubmitInfo submitInfo;
	};

	TEST(SubmitInfo, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<SubmitInfo, vk::SubmitInfo>);
	}
}