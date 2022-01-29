#pragma once

#include "Zinet/GraphicLayer/ZtGLSwapChainSupportDetails.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class SwapChainSupportDetailsTests : public ::testing::Test
	{
	protected:

		SwapChainSupportDetails swapChainSupportDetails;

	};

	TEST_F(SwapChainSupportDetailsTests, PropertiesTest)
	{
		const vk::SurfaceCapabilitiesKHR& capabilities = swapChainSupportDetails.capabilities;
		const std::vector<vk::SurfaceFormatKHR>& formats = swapChainSupportDetails.formats;
		const std::vector<vk::PresentModeKHR>& presentModes = swapChainSupportDetails.presentModes;
	}

}