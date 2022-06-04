#pragma once

#include "Zinet/GraphicLayer/ZtGLQueue.h"
#include "Zinet/GraphicLayer/ZtGLSemaphore.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLSwapChain.h"
#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLPipelineLayout.h"
#include "Zinet/GraphicLayer/ZtGLPipeline.h"
#include "Zinet/GraphicLayer/ZtGLCommandPool.h"

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
			GLFW::Init();

			instance.createApplicationInfo();
			instance.createInstanceCreateInfo();
			instance.create(context);
			window.create();

			bool surfaceResult = surface.create(instance, window);
			if (!surfaceResult)
			{
				FAIL() << "Can't create surface";
			}

			bool physicalDeviceResult = physicalDevice.create(instance);
			if (!physicalDeviceResult)
			{
				FAIL() << "Can't create physical device";
			}

			vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
			vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice, surface, deviceQueueCreateInfo);
			device.create(physicalDevice, deviceCreateInfo);

			uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
			//vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
			queue.create(device, queueFamilyIndex);
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST(Queue, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<Queue, VulkanObject<vk::raii::Queue>>);
	}

	TEST(Queue, CreateSubmitInfo)
	{
		Semaphore semaphore;
		std::array<Semaphore*, 1> waitSemaphores{ &semaphore };
		vk::PipelineStageFlags waitPipelineStageFlags{};
		CommandBuffer commandBuffer;
		std::array<CommandBuffer*, 1> commandBuffers{ &commandBuffer };
		std::array<Semaphore*, 1> signalSemaphores{ &semaphore };

		SubmitInfo submitInfo = Queue::CreateSubmitInfo(
			waitSemaphores, 
			waitPipelineStageFlags,
			commandBuffers, 
			signalSemaphores);

		EXPECT_EQ(waitSemaphores.size(), submitInfo.waitSemaphoreCount);
		EXPECT_EQ(&*waitSemaphores[0]->getInternal(), submitInfo.pWaitSemaphores);

		EXPECT_EQ(&waitPipelineStageFlags, submitInfo.pWaitDstStageMask);

		EXPECT_EQ(commandBuffers.size(), submitInfo.commandBufferCount);
		EXPECT_EQ(&*commandBuffers[0]->getInternal(), submitInfo.pCommandBuffers);

		EXPECT_EQ(signalSemaphores.size(), submitInfo.signalSemaphoreCount);
		EXPECT_EQ(&*signalSemaphores[0]->getInternal(), submitInfo.pSignalSemaphores);
	}

	TEST_F(QueueTests, CreateQueue)
	{
		uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
		queue.create(device, queueFamilyIndex);

		ASSERT_NE(*queue.getInternal(), *vk::raii::Queue(std::nullptr_t()));
	}

	TEST_F(QueueTests, SubmitWithFence)
	{
		Semaphore semaphore;
		semaphore.create(device);
		std::array<Semaphore*, 1> waitSemaphores{ &semaphore };
		vk::PipelineStageFlags waitPipelineStageFlags{};

		CommandPool commandPool;
		uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
		commandPool.create(device, queueFamilyIndex);

		CommandBuffer commandBuffer;
		commandBuffer.allocateCommandBuffer(device, commandPool);
		std::array<CommandBuffer*, 1> commandBuffers{ &commandBuffer };

		std::array<Semaphore*, 1> signalSemaphores{ &semaphore };

		SubmitInfo submitInfo = Queue::CreateSubmitInfo(
			waitSemaphores,
			waitPipelineStageFlags,
			commandBuffers,
			signalSemaphores);

		Fence fence;
		fence.createUnsignaled(device);
		queue.submit(submitInfo, fence);
	}

	TEST_F(QueueTests, Submit)
	{
		Semaphore semaphore;
		semaphore.create(device);
		std::array<Semaphore*, 1> waitSemaphores{ &semaphore };
		vk::PipelineStageFlags waitPipelineStageFlags{};

		CommandPool commandPool;
		uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
		commandPool.create(device, queueFamilyIndex);

		CommandBuffer commandBuffer;
		commandBuffer.allocateCommandBuffer(device, commandPool);
		std::array<CommandBuffer*, 1> commandBuffers{ &commandBuffer };

		std::array<Semaphore*, 1> signalSemaphores{ &semaphore };

		SubmitInfo submitInfo = Queue::CreateSubmitInfo(
			waitSemaphores,
			waitPipelineStageFlags,
			commandBuffers,
			signalSemaphores);

		queue.submit(submitInfo);
	}

	TEST_F(QueueTests, CreatePresentInfo)
	{
		std::array<Semaphore*, 1> waitSemaphores{ {} };
		std::array<SwapChain*, 1> swapChains{ {} };
		uint32_t imageIndex;

		vk::PresentInfoKHR presentInfo = Queue::CreatePresentInfo(
			waitSemaphores,
			swapChains,
			imageIndex);

		EXPECT_EQ(waitSemaphores.size(), presentInfo.waitSemaphoreCount);
		EXPECT_EQ(&*waitSemaphores[0]->getInternal(), presentInfo.pWaitSemaphores);

		EXPECT_EQ(swapChains.size(), presentInfo.swapchainCount);
		EXPECT_EQ(&*swapChains[0]->getInternal(), presentInfo.pSwapchains);

		EXPECT_EQ(&imageIndex, presentInfo.pImageIndices);
	}

	TEST_F(QueueTests, Present)
	{
		SwapChain swapChain;
		SwapChainSupportDetails swapChainSupportDetails;
		swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);
		swapChain.create(device, swapChainSupportDetails, surface, window);

		Semaphore semaphore;
		semaphore.create(device);
		std::array<Semaphore*, 1> waitSemaphores{ &semaphore };
		std::array<SwapChain*, 1> swapChains{ &swapChain };

		uint64_t timeout = 1;

		Fence fence;
		fence.createUnsignaled(device);

		std::pair<vk::Result, uint32_t> nextImage = swapChain.acquireNextImage(timeout, semaphore, fence);
		uint32_t imageIndex = nextImage.second;

		RenderPass renderPass;
		renderPass.createAttachmentDescription(vk::Format::eR8G8Unorm);
		renderPass.createAttachmentReference();
		renderPass.createSubpassDescription();
		renderPass.createSubpassDependency();
		renderPass.create(device);

		vk::PresentInfoKHR presentInfo = Queue::CreatePresentInfo(
			waitSemaphores,
			swapChains,
			imageIndex);

		queue.present(presentInfo); // TODO: Resolve the runtime error
	}
}