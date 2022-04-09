#pragma once

#include "Zinet/GraphicLayer/ZtGLQueue.h"
#include "Zinet/GraphicLayer/ZtGLSemaphore.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLSwapChain.h"

#include "gtest/gtest.h"

#include <utility>

namespace zt::gl::tests
{

	class QueueTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		Queue queue;

		void SetUp() override
		{
			GLFW::InitGLFW();

			window.createWindow();
			instance.createApplicationInfo();
			instance.createInstanceCreateInfo();
			instance.create(context);
			surface.create(instance, window);
			physicalDevice.create(instance);
			device.create(physicalDevice, surface);

			uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
			device.createDeviceQueueCreateInfo(physicalDevice, surface);
			queue = device.createQueue(queueFamilyIndex);
		}

		void TearDown() override
		{
			GLFW::DeinitGLFW();
		}
	};

	TEST(Queue, CreateSubmitInfo)
	{
		std::array<Semaphore, 1> waitSemaphores{ {} };
		vk::PipelineStageFlags waitPipelineStageFlags{};
		std::array<CommandBuffer, 2> commandBuffers{ CommandBuffer{}, CommandBuffer{} };
		std::array<Semaphore, 1> signalSemaphores{ {} };

		vk::SubmitInfo submitInfo = Queue::CreateSubmitInfo(
			waitSemaphores, 
			waitPipelineStageFlags,
			commandBuffers, 
			signalSemaphores);

		EXPECT_EQ(waitSemaphores.size(), submitInfo.waitSemaphoreCount);
		EXPECT_EQ(&*waitSemaphores.begin()->getInternal(), submitInfo.pWaitSemaphores);

		EXPECT_EQ(&waitPipelineStageFlags, submitInfo.pWaitDstStageMask);

		EXPECT_EQ(commandBuffers.size(), submitInfo.commandBufferCount);
		EXPECT_EQ(&*commandBuffers.begin()->getInternal(), submitInfo.pCommandBuffers);

		EXPECT_EQ(signalSemaphores.size(), submitInfo.signalSemaphoreCount);
		EXPECT_EQ(&*signalSemaphores.begin()->getInternal(), submitInfo.pSignalSemaphores);
	}

	TEST_F(QueueTests, Submit)
	{
		std::array<Semaphore, 0> waitSemaphores;
		vk::PipelineStageFlags waitPipelineStageFlags = vk::PipelineStageFlagBits::eColorAttachmentOutput;
		std::array<CommandBuffer, 0> commandBuffers;
		std::array<Semaphore, 0> signalSemaphores;

		vk::SubmitInfo submitInfo = Queue::CreateSubmitInfo(
			waitSemaphores,
			waitPipelineStageFlags,
			commandBuffers,
			signalSemaphores);

		std::array<vk::SubmitInfo, 1> submitInfos = { submitInfo };
		Fence fence;
		fence.createUnsignaled(device);
		queue.submit(submitInfos, fence);
	}

	TEST_F(QueueTests, CreatePresentInfo)
	{
		std::array<Semaphore, 1> waitSemaphores{ {} };
		std::array<SwapChain, 1> swapChains{ {} };
		uint32_t imageIndex;

		vk::PresentInfoKHR presentInfo = Queue::CreatePresentInfo(
			waitSemaphores,
			swapChains,
			imageIndex);

		EXPECT_EQ(waitSemaphores.size(), presentInfo.waitSemaphoreCount);
		EXPECT_EQ(&*waitSemaphores.begin()->getInternal(), presentInfo.pWaitSemaphores);

		EXPECT_EQ(swapChains.size(), presentInfo.swapchainCount);
		EXPECT_EQ(&*swapChains.begin()->getInternal(), presentInfo.pSwapchains);

		EXPECT_EQ(&imageIndex, presentInfo.pImageIndices);
	}
}