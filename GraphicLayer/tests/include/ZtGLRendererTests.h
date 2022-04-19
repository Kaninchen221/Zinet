#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLrenderer.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class RendererTests : public ::testing::Test
	{
	protected:

		Renderer renderer;

	};

	TEST_F(RendererTests, GetContext)
	{
		Context& context = renderer.getContext();
	}

	TEST_F(RendererTests, GetInstance)
	{
		Instance& instance = renderer.getInstance();
	}

	TEST_F(RendererTests, GetDebugUtilsMessenger)
	{
		DebugUtilsMessenger& debugUtilsMessenger = renderer.getDebugUtilsMessenger();
	}

	TEST_F(RendererTests, GetWindow)
	{
		Window& window = renderer.getWindow();
	}

	TEST_F(RendererTests, GetSurface)
	{
		Surface& surface = renderer.getSurface();
	}

	TEST_F(RendererTests, GetPhysicalDevice)
	{
		PhysicalDevice& physicalDevice = renderer.getPhysicalDevice();
	}

	TEST_F(RendererTests, GetDevice)
	{
		Device& device = renderer.getDevice();
	}

	TEST_F(RendererTests, GetQueue)
	{
		Queue& queue = renderer.getQueue();
	}

	TEST_F(RendererTests, GetSwapChain)
	{
		SwapChain& swapChain = renderer.getSwapChain();
	}

	TEST_F(RendererTests, GetPipelineLayout)
	{
		PipelineLayout& pipelineLayout = renderer.getPipelineLayout();
	}

	TEST_F(RendererTests, GetRenderPass)
	{
		RenderPass& renderPass = renderer.getRenderPass();
	}

	TEST_F(RendererTests, GetPipeline)
	{
		Pipeline& pipeline = renderer.getPipeline();
	}

	TEST_F(RendererTests, GetFramebuffers)
	{
		std::vector<Framebuffer>& framebuffers = renderer.getFramebuffers();
	}

	TEST_F(RendererTests, GetCommandPool)
	{
		CommandPool& commandPool = renderer.getCommandPool();
	}

	TEST_F(RendererTests, GetCommandBuffer)
	{
		CommandBuffer& commandBuffer = renderer.getCommandBuffer();
	}

	TEST_F(RendererTests, Run)
	{
		//renderer.contentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";
		//renderer.prepare();
	}

}