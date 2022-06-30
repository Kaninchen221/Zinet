#include "Zinet/GraphicLayer/ZtGLQueue.h"
#include "Zinet/GraphicLayer/ZtGLSemaphore.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLFence.h"
#include "Zinet/GraphicLayer/ZtGLSwapChain.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLBuffer.h"
#include "Zinet/GraphicLayer/ZtGLBufferCopy.h"

#include <utility>

namespace zt::gl
{
    void Queue::create(Device& device, uint32_t queueFamilyIndex)
    {
        // We creating only one queue
        uint32_t queueIndex = 0u;
        internal = std::move(vk::raii::Queue{ device.getInternal(), queueFamilyIndex, queueIndex });
    }

    vk::SubmitInfo Queue::createSubmitInfo(
        std::span<Semaphore*> waitSemaphores,
        vk::PipelineStageFlags& waitPipelineStageFlags,
        std::span<CommandBuffer*> commandBuffers,
        std::span<Semaphore*> signalSemaphores)
    {
        vk::SubmitInfo submitInfo;
        submitInfo.waitSemaphoreCount = waitSemaphores.size();
        submitInfo.pWaitSemaphores = &*waitSemaphores[0]->getInternal();
        submitInfo.pWaitDstStageMask = &waitPipelineStageFlags;
        submitInfo.commandBufferCount = commandBuffers.size();
        submitInfo.pCommandBuffers = &*commandBuffers[0]->getInternal();
        submitInfo.signalSemaphoreCount = signalSemaphores.size();
        submitInfo.pSignalSemaphores = &*signalSemaphores[0]->getInternal();
         
        return submitInfo;
    }

    void Queue::submit(const vk::SubmitInfo& submitInfo, Fence& fence)
    {
        internal.submit(submitInfo, *fence.getInternal());
    }

    void Queue::submit(const vk::SubmitInfo& submitInfo)
    {
        internal.submit(submitInfo);
    }

    vk::PresentInfoKHR Queue::createPresentInfo(
        std::span<Semaphore*> waitSemaphores, 
        std::span<SwapChain*> swapChains, 
        uint32_t& imageIndex)
    {
        vk::PresentInfoKHR presentInfo;
        presentInfo.waitSemaphoreCount = waitSemaphores.size();
        presentInfo.pWaitSemaphores = &*waitSemaphores[0]->getInternal();
        presentInfo.swapchainCount = swapChains.size();
        presentInfo.pSwapchains = &*swapChains[0]->getInternal();
        presentInfo.pImageIndices = &imageIndex;
        presentInfo.pResults = nullptr;

        return presentInfo;
    }

    void Queue::present(vk::PresentInfoKHR& presentInfo)
    {
        [[maybe_unused]] vk::Result result = internal.presentKHR(presentInfo);
    }

    void Queue::copyBufferToBufferWaitIdle(CommandBuffer& commandBuffer, Buffer& sourceBuffer, Buffer& destinationBuffer)
    {
        commandBuffer.begin();

        BufferCopy bufferCopy;
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
}