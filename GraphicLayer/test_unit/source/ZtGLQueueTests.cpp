#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLQueue.h"
#include "Zinet/GraphicLayer/ZtGLSemaphore.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLSwapChain.h"
#include "Zinet/GraphicLayer/ZtGLRenderPass.h"
#include "Zinet/GraphicLayer/ZtGLPipelineLayout.h"
#include "Zinet/GraphicLayer/ZtGLPipeline.h"
#include "Zinet/GraphicLayer/ZtGLCommandPool.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLSwapChainSupportDetails.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLFence.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLStagingBuffer.h"
#include "Zinet/GraphicLayer/ZtGLVma.h"
#include "ZtGLRendererBuilder.h"

#include <gtest/gtest.h>

#include <utility>
#include <functional>

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

			vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
			instance.populateRequiredExtensions();
			vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
			instance.create(context, instanceCreateInfo);
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
		std::vector<vk::CommandBuffer> commandBuffers = { *commandBuffer.getInternal() };
		std::array<Semaphore*, 1> signalSemaphores{ &semaphore };

		Queue queue;
		vk::SubmitInfo submitInfo = queue.createSubmitInfo(
			waitSemaphores, 
			waitPipelineStageFlags,
			commandBuffers, 
			signalSemaphores);

		EXPECT_EQ(waitSemaphores.size(), submitInfo.waitSemaphoreCount);
		EXPECT_EQ(&*waitSemaphores[0]->getInternal(), submitInfo.pWaitSemaphores);

		EXPECT_EQ(&waitPipelineStageFlags, submitInfo.pWaitDstStageMask);

		EXPECT_EQ(commandBuffers.size(), submitInfo.commandBufferCount);
		EXPECT_EQ(commandBuffers[0], *submitInfo.pCommandBuffers);

		EXPECT_EQ(signalSemaphores.size(), submitInfo.signalSemaphoreCount);
		EXPECT_EQ(&*signalSemaphores[0]->getInternal(), submitInfo.pSignalSemaphores);
	}

	TEST_F(QueueTests, CreateQueue)
	{
		ASSERT_NE(*queue.getInternal(), *vk::raii::Queue(std::nullptr_t()));
	}

	TEST(Queue, Submit)
	{
		Queue queue;
		vk::SubmitInfo submitInfo;
		
		typedef void(Queue::* Submit)(const vk::SubmitInfo&) const;
		[[maybe_unused]] Submit submit = &Queue::submit;
	}

	TEST(Queue, SubmitWithFence)
	{
		Queue queue;
		vk::SubmitInfo submitInfo;
		Fence fence;

		typedef void(Queue::* SubmitWithFence)(const vk::SubmitInfo&, Fence& fence) const;
		[[maybe_unused]] SubmitWithFence submitWithFence = &Queue::submitWithFence;
	}

	TEST(Queue, CreatePresentInfo)
	{
		std::array<Semaphore*, 1> waitSemaphores{ {} };
		std::array<SwapChain*, 1> swapChains{ {} };
		uint32_t imageIndex;

		Queue queue;
		vk::PresentInfoKHR presentInfo = queue.createPresentInfo(
			waitSemaphores,
			swapChains,
			imageIndex);

		EXPECT_EQ(waitSemaphores.size(), presentInfo.waitSemaphoreCount);
		EXPECT_EQ(&*waitSemaphores[0]->getInternal(), presentInfo.pWaitSemaphores);

		EXPECT_EQ(swapChains.size(), presentInfo.swapchainCount);
		EXPECT_EQ(&*swapChains[0]->getInternal(), presentInfo.pSwapchains);

		EXPECT_EQ(&imageIndex, presentInfo.pImageIndices);
	}

	TEST(Queue, Present)
	{
		Queue queue;
		vk::PresentInfoKHR presentInfo;
		
		auto present = std::bind_front(&Queue::present, &queue, presentInfo);
	}

	TEST(Queue, CopyBuffer)
	{
		Renderer renderer;
		renderer.initialize();
		RendererContext& rendererContext = renderer.getRendererContext();
		
		std::vector<Vertex> vertices{ {}, {} };
		
		//Staging Buffer
		StagingBuffer sourceBuffer;

		std::uint64_t size = sizeof(Vertex) * vertices.size();
		BufferCreateInfo sourceBufferCreateInfo{ .device = rendererContext.getDevice(), .vma = rendererContext.getVma() };
		sourceBufferCreateInfo.vkBufferCreateInfo = sourceBuffer.createCreateInfo(size);
		sourceBufferCreateInfo.allocationCreateInfo = sourceBuffer.createVmaAllocationCreateInfo(false, true);

		sourceBuffer.create(sourceBufferCreateInfo);
		sourceBuffer.fillWithStdContainer(vertices);

		// Vertex Buffer 
		VertexBuffer destinationBuffer;

		BufferCreateInfo destinationBufferCreateInfo{ .device = rendererContext.getDevice(), .vma = rendererContext.getVma() };
		destinationBufferCreateInfo.vkBufferCreateInfo = destinationBuffer.createCreateInfo(size);
		destinationBufferCreateInfo.allocationCreateInfo = destinationBuffer.createVmaAllocationCreateInfo(false, false);

		destinationBuffer.create(destinationBufferCreateInfo);
		destinationBuffer.fillWithStdContainer(vertices);

		// Copying
		const Queue& queue = rendererContext.getQueue();
		std::uint32_t queueFamilyIndex = rendererContext.getQueueFamilyIndex();

		CommandPool commandPool;
		commandPool.create(rendererContext.getDevice(), queueFamilyIndex);
		
		CommandBuffer commandBuffer;
		vk::CommandBufferAllocateInfo allocateInfo = commandBuffer.createCommandBufferAllocateInfo(commandPool);
		commandBuffer.allocateCommandBuffer(rendererContext.getDevice(), commandPool);
		
		queue.copyBufferToBufferWaitIdle(commandBuffer, sourceBuffer, destinationBuffer);

		std::unique_ptr<void, decltype(LambdaFree)> data = destinationBuffer.getData();
		std::size_t expectedSize = sizeof(Vertex) * vertices.size();
		
		int result = std::memcmp(data.get(), vertices.data(), expectedSize);
		
		ASSERT_EQ(result, 0);
	}
}