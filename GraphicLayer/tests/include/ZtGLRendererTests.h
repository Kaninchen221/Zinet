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

		const DebugUtilsMessenger& debugUtilsMessenger = renderer.getDebugUtilsMessenger();
		ASSERT_NE(debugUtilsMessenger, vk::raii::DebugUtilsMessengerEXT(std::nullptr_t{}));

		const Window& window = renderer.getWindow();
		const GLFWwindow* internalWindow = window.getInternal();
		ASSERT_NE(internalWindow, nullptr);

		const Surface& surface = renderer.getSurface();
		ASSERT_NE(surface, nullptr);

		const PhysicalDevice& physicalDevice = renderer.getPhysicalDevice();
		ASSERT_NE(physicalDevice, nullptr);

		std::uint32_t queueFamilyIndex = renderer.getQueueFamilyIndex();
		ASSERT_NE(queueFamilyIndex, std::numeric_limits<uint32_t>::max());

		const Device& device = renderer.getDevice();
		ASSERT_NE(device, nullptr);

		const Queue& queue = renderer.getQueue();
		ASSERT_NE(queue, nullptr);

		const SwapChain& swapChain = renderer.getSwapChain();
		ASSERT_NE(swapChain, nullptr);

		const std::vector<ImageView>& imageViews = renderer.getImageViews();
		ASSERT_FALSE(imageViews.empty());

		const vk::Extent2D& swapExtent = renderer.getSwapExtent();
		ASSERT_NE(swapExtent, vk::Extent2D{});

		const PipelineLayout& pipelineLayout = renderer.getPipelineLayout();
		ASSERT_NE(pipelineLayout, nullptr);

		const RenderPass& renderPass = renderer.getRenderPass();
		ASSERT_NE(renderPass, nullptr);
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

	TEST_F(RendererTests, GetDebugUtilsMessenger)
	{
		const DebugUtilsMessenger& debugUtilsMessenger = renderer.getDebugUtilsMessenger();
		ASSERT_EQ(debugUtilsMessenger, vk::raii::DebugUtilsMessengerEXT(std::nullptr_t{}));
	}

	TEST_F(RendererTests, GetWindow)
	{
		const Window& window = renderer.getWindow();
		const GLFWwindow* internalWindow = window.getInternal();

		ASSERT_EQ(internalWindow, nullptr);
	}

	TEST_F(RendererTests, GetSurface)
	{
		const Surface& surface = renderer.getSurface();
		ASSERT_EQ(surface, nullptr);
	}

	TEST_F(RendererTests, GetPhysicalDevice)
	{
		const PhysicalDevice& physicalDevice = renderer.getPhysicalDevice();
		ASSERT_EQ(physicalDevice, nullptr);
	}

	TEST_F(RendererTests, GetQueueFamilyIndex)
	{
		std::uint32_t queueFamilyIndex = renderer.getQueueFamilyIndex();
		ASSERT_EQ(queueFamilyIndex, std::numeric_limits<uint32_t>::max());
	}

	TEST_F(RendererTests, GetDevice)
	{
		const Device& device = renderer.getDevice();
		ASSERT_EQ(device, nullptr);
	}

	TEST_F(RendererTests, GetQueue)
	{
		const Queue& queue = renderer.getQueue();
		ASSERT_EQ(queue, nullptr);
	}

	TEST_F(RendererTests, GetSwapChainSupportDetails)
	{
		const SwapChainSupportDetails& swapChainSupportDetails = renderer.getSwapChainSupportDetails();
	}

	TEST_F(RendererTests, GetSwapChain)
	{
		const SwapChain& swapChain = renderer.getSwapChain();
		ASSERT_EQ(swapChain, nullptr);
	}

	TEST_F(RendererTests, GetImageViews)
	{
		const std::vector<ImageView>& imageViews = renderer.getImageViews();
		ASSERT_TRUE(imageViews.empty());
	}

	TEST_F(RendererTests, GetSwapExtent)
	{
		const vk::Extent2D& swapExtent = renderer.getSwapExtent();
		ASSERT_EQ(swapExtent, vk::Extent2D{});
	}

	TEST_F(RendererTests, GetPipelineLayout)
	{
		const PipelineLayout& pipelineLayout = renderer.getPipelineLayout();
		ASSERT_EQ(pipelineLayout, nullptr);
	}

	TEST_F(RendererTests, GetRenderPass)
	{
		const RenderPass& renderPass = renderer.getRenderPass();
		ASSERT_EQ(renderPass, nullptr);
	}

}
