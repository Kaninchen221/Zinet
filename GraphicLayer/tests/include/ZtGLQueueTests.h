#pragma once

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
#include "Zinet/GraphicLayer/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/ZtGLStagingBuffer.h"
#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"
#include "ZtGLRendererBuilder.h"

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

			vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
			instance.getRequiredExtensions();
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
		std::array<CommandBuffer*, 1> commandBuffers{ &commandBuffer };
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
		EXPECT_EQ(&*commandBuffers[0]->getInternal(), submitInfo.pCommandBuffers);

		EXPECT_EQ(signalSemaphores.size(), submitInfo.signalSemaphoreCount);
		EXPECT_EQ(&*signalSemaphores[0]->getInternal(), submitInfo.pSignalSemaphores);
	}

	TEST_F(QueueTests, CreateQueue)
	{
		ASSERT_NE(*queue.getInternal(), *vk::raii::Queue(std::nullptr_t()));
	}

	// TODO Fix after integrating the VMA
	//TEST(QueueTest, SubmitWithFence)
	//{
	//	RendererBuilder rendererBuilder;
	//	rendererBuilder.createAll();
	//	rendererBuilder.updateMVP();
	//	rendererBuilder.drawFrame();
	//}

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

		vk::SubmitInfo submitInfo = queue.createSubmitInfo(
			waitSemaphores,
			waitPipelineStageFlags,
			commandBuffers,
			signalSemaphores);

		queue.submit(submitInfo);
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

	TEST_F(QueueTests, Present)
	{
		SwapChain swapChain;
		SwapChainSupportDetails swapChainSupportDetails;
		swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);
		vk::SwapchainCreateInfoKHR creatInfo = swapChain.createCreateInfo(swapChainSupportDetails, surface, window);
		swapChain.create(device, creatInfo);

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

		vk::PresentInfoKHR presentInfo = queue.createPresentInfo(
			waitSemaphores,
			swapChains,
			imageIndex);

		queue.present(presentInfo); // TODO: Resolve the runtime error
	}

	TEST_F(QueueTests, CopyBuffer)
	{
		// TODO Use new way to create buffers

		//Queue queue;
		//uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
		//queue.create(device, queueFamilyIndex);
		//
		//std::vector<Vertex> vertices{ {}, {} };
		//
		//// Staging Buffer
		//StagingBuffer sourceBuffer;
		//DeviceMemory sourceBufferDeviceMemory;
		//
		//vk::BufferCreateInfo sourceBufferCreateInfo = sourceBuffer.createCreateInfo(sizeof(Vertex) * vertices.size());
		//sourceBuffer.create(device, sourceBufferCreateInfo);
		//
		//vk::MemoryRequirements sourceBufferMemoryRequirements = sourceBuffer->getMemoryRequirements();
		//vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = physicalDevice->getMemoryProperties();
		//vk::MemoryPropertyFlags sourceBufferMemoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
		//vk::MemoryAllocateInfo sourceBufferMemoryAllocateInfo = sourceBuffer.createMemoryAllocateInfo(
		//	sourceBufferMemoryRequirements,
		//	physicalDeviceMemoryProperties,
		//	sourceBufferMemoryPropertyFlags);
		//
		//sourceBufferDeviceMemory.create(device, sourceBufferMemoryAllocateInfo);
		//
		//sourceBuffer.bindMemory(sourceBufferDeviceMemory);
		//
		//sourceBufferDeviceMemory.fillWithSTDContainer(vertices);
		//
		//// Vertex Buffer 
		//VertexBuffer destinationBuffer;
		//DeviceMemory destinationBufferDeviceMemory;
		//
		//vk::BufferCreateInfo destinationBufferCreateInfo = destinationBuffer.createCreateInfo(sizeof(Vertex) * vertices.size());
		//destinationBuffer.create(device, destinationBufferCreateInfo);
		//
		//vk::MemoryRequirements destinationBufferMemoryRequirements = destinationBuffer->getMemoryRequirements();
		//vk::MemoryPropertyFlags destinationBufferMemoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eDeviceLocal;
		//vk::MemoryAllocateInfo destinationBufferrMemoryAllocateInfo = destinationBuffer.createMemoryAllocateInfo(
		//	destinationBufferMemoryRequirements,
		//	physicalDeviceMemoryProperties,
		//	destinationBufferMemoryPropertyFlags);
		//
		//destinationBufferDeviceMemory.create(device, destinationBufferrMemoryAllocateInfo);
		//destinationBuffer.bindMemory(destinationBufferDeviceMemory);
		//
		//CommandPool commandPool;
		//commandPool.create(device, queueFamilyIndex);
		//
		//CommandBuffer commandBuffer;
		//vk::CommandBufferAllocateInfo allocateInfo = commandBuffer.createCommandBufferAllocateInfo(commandPool);
		//commandBuffer.allocateCommandBuffer(device, commandPool);
		//
		//queue.copyBufferToBufferWaitIdle(commandBuffer, sourceBuffer, destinationBuffer);
		//
		//std::pair<void*, std::uint64_t> data = destinationBufferDeviceMemory.getData(destinationBuffer.getSize());
		//std::size_t expectedSize = sizeof(Vertex) * vertices.size();
		//
		//ASSERT_EQ(data.second, expectedSize);
		//
		//int result = std::memcmp(data.first, vertices.data(), expectedSize);
		//
		//ASSERT_EQ(result, 0);
		//
		//std::free(data.first);
	}
}