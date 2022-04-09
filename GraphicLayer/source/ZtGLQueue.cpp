#include "Zinet/GraphicLayer/ZtGLQueue.h"
#include "Zinet/GraphicLayer/ZtGLSemaphore.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLFence.h"

#include <utility>

namespace zt::gl
{
    Queue::Queue()
        : internal(std::nullptr_t())
    {

    }

    Queue::Queue(vk::raii::Queue&& queue)
        : internal(std::move(queue))
    {

    }

    const vk::raii::Queue& Queue::getInternal() const
    {
        return internal;
    }

    vk::SubmitInfo Queue::CreateSubmitInfo(
        std::span<Semaphore> waitSemaphores,
        vk::PipelineStageFlags& waitPipelineStageFlags,
        std::span<CommandBuffer> commandBuffers,
        std::span<Semaphore> signalSemaphores)
    {
        vk::SubmitInfo submitInfo;
        submitInfo.waitSemaphoreCount = waitSemaphores.size();
        submitInfo.pWaitSemaphores = &*waitSemaphores.data()->getInternal();
        submitInfo.pWaitDstStageMask = &waitPipelineStageFlags;
        submitInfo.commandBufferCount = commandBuffers.size();
        submitInfo.pCommandBuffers = &*commandBuffers.data()->getInternal();
        submitInfo.signalSemaphoreCount = signalSemaphores.size();
        submitInfo.pSignalSemaphores = &*signalSemaphores.data()->getInternal();

        return submitInfo;
    }

    void Queue::submit(std::span<vk::SubmitInfo> submitInfo, Fence& fence)
    {
        internal.submit(submitInfo, *fence.getInternal());
    }
}