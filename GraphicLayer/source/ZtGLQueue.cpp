#include "Zinet/GraphicLayer/ZtGLQueue.h"

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

}