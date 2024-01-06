#include "Zinet/GraphicLayer/ZtGLQueue.hpp"
#include "Zinet/GraphicLayer/ZtGLSemaphore.hpp"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.hpp"
#include "Zinet/GraphicLayer/ZtGLFence.hpp"
#include "Zinet/GraphicLayer/ZtGLSwapChain.hpp"
#include "Zinet/GraphicLayer/ZtGLDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLSurface.hpp"
#include "Zinet/GraphicLayer/Buffers/ZtGLBuffer.hpp"
#include "Zinet/GraphicLayer/ZtGLSignalCommandBuffer.hpp"

#include <utility>

namespace zt::gl
{
    void Queue::create(Device& device, uint32_t queueFamilyIndex)
    {
        // We creating only one queue
        uint32_t queueIndex = 0u;
        vk::raii::Queue tempQueue{ device.getInternal(), queueFamilyIndex, queueIndex };
        internal.swap(tempQueue);
        tempQueue.release();
    }

    vk::SubmitInfo Queue::createSubmitInfo(
        std::span<Semaphore*> waitSemaphores,
        vk::PipelineStageFlags& waitPipelineStageFlags,
        std::span<vk::CommandBuffer> commandBuffers,
        std::span<Semaphore*> signalSemaphores) const
    {
        vk::SubmitInfo submitInfo;
        submitInfo.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size());
        submitInfo.pWaitSemaphores = &*waitSemaphores[0]->getInternal();
        submitInfo.pWaitDstStageMask = &waitPipelineStageFlags;
        submitInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());
        submitInfo.pCommandBuffers = &commandBuffers[0];
        submitInfo.signalSemaphoreCount = static_cast<uint32_t>(signalSemaphores.size());
        submitInfo.pSignalSemaphores = &*signalSemaphores[0]->getInternal();
         
        return submitInfo;
    }

    void Queue::submitWithFence(const vk::SubmitInfo& submitInfo, Fence& fence) const
    {
        internal.submit(submitInfo, *fence.getInternal());
    }

    void Queue::submit(const vk::SubmitInfo& submitInfo) const
    {
        internal.submit(submitInfo);
    }

	void Queue::submit(CommandBuffer& commandBuffer) const
	{
		vk::SubmitInfo submitInfo{};
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

		submit(submitInfo);
	}

	void Queue::submit(SignalCommandBuffer& signalCommandBuffer) const
	{
		vk::SubmitInfo submitInfo{};
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*signalCommandBuffer.getInternal();

		submitWithFence(submitInfo, signalCommandBuffer.getFence());
	}

    vk::PresentInfoKHR Queue::createPresentInfo(
        std::span<Semaphore*> waitSemaphores, 
        std::span<SwapChain*> swapChains, 
        uint32_t& imageIndex)
    {
        vk::PresentInfoKHR presentInfo;
        presentInfo.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size());
        presentInfo.pWaitSemaphores = &*waitSemaphores[0]->getInternal();
        presentInfo.swapchainCount = static_cast<uint32_t>(swapChains.size());
        presentInfo.pSwapchains = &*swapChains[0]->getInternal();
        presentInfo.pImageIndices = &imageIndex;
        presentInfo.pResults = nullptr;

        return presentInfo;
    }

    void Queue::present(vk::PresentInfoKHR& presentInfo) const
    {
        vk::Result result = internal.presentKHR(presentInfo);
        if (result != vk::Result::eSuccess)
            Logger->error("Submit return non success vk::Result");
    }

    void Queue::copyBufferToBufferWaitIdle(CommandBuffer& commandBuffer, Buffer& sourceBuffer, Buffer& destinationBuffer) const
    {
        commandBuffer.begin();

        vk::BufferCopy bufferCopy;
        bufferCopy.srcOffset = 0;
        bufferCopy.dstOffset = 0;
        bufferCopy.size = sourceBuffer.getSize();

        commandBuffer->copyBuffer(*sourceBuffer.getInternal(), *destinationBuffer.getInternal(), bufferCopy);

        commandBuffer.end();

        vk::SubmitInfo submitInfo{};
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

        submit(submitInfo);
        internal.waitIdle();
	}

	void Queue::submitWaitIdle(CommandBuffer& commandBuffer)
	{
		vk::SubmitInfo submitInfo{};
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

		submit(submitInfo);
		internal.waitIdle();
	}

	void Queue::submitWaitIdle(CommandBuffer& commandBuffer, SubmitWaitIdleFunction function)
	{
		commandBuffer.begin();

        std::invoke(function, commandBuffer);

		commandBuffer.end();

		vk::SubmitInfo submitInfo{};
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

		submit(submitInfo);
		internal.waitIdle();
	}

}