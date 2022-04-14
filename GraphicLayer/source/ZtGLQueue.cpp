#include "Zinet/GraphicLayer/ZtGLQueue.h"
#include "Zinet/GraphicLayer/ZtGLSemaphore.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLFence.h"
#include "Zinet/GraphicLayer/ZtGLSwapChain.h"

#include <utility>

namespace zt::gl
{

    Queue::Queue(vk::raii::Queue&& queue)
    {
        internal = std::move(queue); // TODO: Check if it's needed
    }

    vk::SubmitInfo Queue::CreateSubmitInfo(
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

    Queue::Queue()
    {
    }

    void Queue::submit(std::span<vk::SubmitInfo> submitInfo, Fence& fence)
    {
        internal.submit(submitInfo, *fence.getInternal());
    }

    vk::PresentInfoKHR Queue::CreatePresentInfo(
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
        internal.presentKHR(presentInfo);
    }
}