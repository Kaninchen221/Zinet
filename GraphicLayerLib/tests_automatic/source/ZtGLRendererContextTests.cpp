#pragma once

#include "Zinet/GraphicLayer/ZtGLRendererContext.hpp"

#include "Zinet/Window/ZtGLFW.hpp"

#include <gtest/gtest.h>

#include <filesystem>
#include <vector>

namespace zt::gl::tests
{

	class RendererContextTests : public ::testing::Test
	{
	protected:

		const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

		RendererContext rendererContext;

		struct MVP
		{

		};
	};

	TEST_F(RendererContextTests, Initialize)
	{
		wd::GLFW::Init();
		rendererContext.initialize();

		const Instance& instance = rendererContext.getInstance();
		ASSERT_TRUE(instance.isValid());

		const DebugUtilsMessenger& debugUtilsMessenger = rendererContext.getDebugUtilsMessenger();
		ASSERT_TRUE(debugUtilsMessenger.isValid());

		const wd::Window& window = rendererContext.getWindow();
		const GLFWwindow* internalWindow = window.getInternal();
		ASSERT_NE(internalWindow, nullptr);

		const Surface& surface = rendererContext.getSurface();
		ASSERT_TRUE(surface.isValid());

		const PhysicalDevice& physicalDevice = rendererContext.getPhysicalDevice();
		ASSERT_TRUE(physicalDevice.isValid());

		std::uint32_t queueFamilyIndex = rendererContext.getQueueFamilyIndex();
		ASSERT_NE(queueFamilyIndex, std::numeric_limits<uint32_t>::max());

		const Device& device = rendererContext.getDevice();
		ASSERT_TRUE(device.isValid());

		const Queue& queue = rendererContext.getQueue();
		ASSERT_TRUE(queue.isValid());

		const SwapChain& swapChain = rendererContext.getSwapChain();
		ASSERT_TRUE(swapChain.isValid());

		const vk::Extent2D& swapExtent = rendererContext.getSwapExtent();
		ASSERT_NE(swapExtent, vk::Extent2D{});

		const DepthStencilBuffer& depthStencilBuffer = rendererContext.getDepthStencilBuffer();
		ASSERT_TRUE(depthStencilBuffer.isValid());

		const RenderPass& renderPass = rendererContext.getRenderPass();
		ASSERT_TRUE(renderPass.isValid());

		const std::vector<RenderTargetDisplay>& renderTargets = rendererContext.getRenderTargets();
		ASSERT_FALSE(renderTargets.empty());

		const Vma& vma = rendererContext.getVma();
		ASSERT_NE(vma.getInternal(), nullptr);

		const CommandPool& commandPool = rendererContext.getCommandPool();
		ASSERT_TRUE(commandPool.isValid());

		const SignalCommandBuffer& signalCommandBuffer = rendererContext.getTransferCommandBuffer();
		ASSERT_TRUE(signalCommandBuffer.isValid());

		wd::GLFW::Deinit();
	}

	class RendererContextSimpleTests : public ::testing::Test
	{
	protected:
		RendererContext rendererContext;
	};

	TEST_F(RendererContextSimpleTests, GetContext)
	{
		[[maybe_unused]] const Context& context = rendererContext.getContext();
	}

	TEST_F(RendererContextSimpleTests, GetInstance)
	{
		const Instance& instance = rendererContext.getInstance();
		ASSERT_EQ(instance, vk::raii::Instance(std::nullptr_t{}));
	}

	TEST_F(RendererContextSimpleTests, GetDebugUtilsMessenger)
	{
		const DebugUtilsMessenger& debugUtilsMessenger = rendererContext.getDebugUtilsMessenger();
		ASSERT_EQ(debugUtilsMessenger, vk::raii::DebugUtilsMessengerEXT(std::nullptr_t{}));
	}

	TEST_F(RendererContextSimpleTests, GetWindow)
	{
		const wd::Window& window = rendererContext.getWindow();
		const GLFWwindow* internalWindow = window.getInternal();

		ASSERT_EQ(internalWindow, nullptr);
	}

	TEST_F(RendererContextSimpleTests, GetSurface)
	{
		const Surface& surface = rendererContext.getSurface();
		ASSERT_EQ(surface, nullptr);
	}

	TEST_F(RendererContextSimpleTests, GetPhysicalDevice)
	{
		const PhysicalDevice& physicalDevice = rendererContext.getPhysicalDevice();
		ASSERT_EQ(physicalDevice, nullptr);
	}

	TEST_F(RendererContextSimpleTests, GetQueueFamilyIndex)
	{
		std::uint32_t queueFamilyIndex = rendererContext.getQueueFamilyIndex();
		ASSERT_EQ(queueFamilyIndex, std::numeric_limits<uint32_t>::max());
	}

	TEST_F(RendererContextSimpleTests, GetDevice)
	{
		const Device& device = rendererContext.getDevice();
		ASSERT_EQ(device, nullptr);
	}

	TEST_F(RendererContextSimpleTests, GetQueue)
	{
		const Queue& queue = rendererContext.getQueue();
		ASSERT_EQ(queue, nullptr);
	}

	TEST_F(RendererContextSimpleTests, GetSwapChainSupportDetails)
	{
		[[maybe_unused]] const SwapChainSupportDetails& swapChainSupportDetails = rendererContext.getSwapChainSupportDetails();
	}

	TEST_F(RendererContextSimpleTests, GetSwapChain)
	{
		const SwapChain& swapChain = rendererContext.getSwapChain();
		ASSERT_EQ(swapChain, nullptr);
	}

	TEST_F(RendererContextSimpleTests, GetSwapExtent)
	{
		const vk::Extent2D& swapExtent = rendererContext.getSwapExtent();
		ASSERT_EQ(swapExtent, vk::Extent2D{});
	}

	TEST_F(RendererContextSimpleTests, GetRenderPass)
	{
		const RenderPass& renderPass = rendererContext.getRenderPass();
		ASSERT_EQ(renderPass, nullptr);
	}

	TEST_F(RendererContextSimpleTests, GetFramebuffers)
	{
		const std::vector<RenderTargetDisplay>& renderTargets = rendererContext.getRenderTargets();
		ASSERT_TRUE(renderTargets.empty());
	}

	TEST_F(RendererContextSimpleTests, GetVma)
	{
		const Vma& vma = rendererContext.getVma();
		ASSERT_EQ(vma.getInternal(), nullptr);
	}

	TEST_F(RendererContextSimpleTests, GetCommandPool)
	{
		[[maybe_unused]] const CommandPool& commandPool = rendererContext.getCommandPool();
	}

	TEST_F(RendererContextSimpleTests, GetCommandBuffer)
	{
		[[maybe_unused]] const CommandBuffer& commandBuffer = rendererContext.getTransferCommandBuffer();
	}

	TEST_F(RendererContextSimpleTests, GetDepthStencilBuffer)
	{
		[[maybe_unused]] const DepthStencilBuffer& depthStencilBuffer = rendererContext.getDepthStencilBuffer();
	}

	TEST_F(RendererContextSimpleTests, GetDepthStencilBufferFormat)
	{
		[[maybe_unused]] const vk::Format& depthStencilBufferFormat = rendererContext.getDepthStencilBufferFormat();
	}
}