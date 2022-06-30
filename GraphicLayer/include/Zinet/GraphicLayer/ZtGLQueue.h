#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

#include <span>

namespace zt::gl
{
	class Semaphore;
	class CommandBuffer;
	class Fence;
	class SwapChain;
	class Device;
	class PhysicalDevice;
	class Surface;
	class Buffer;

	class ZINET_GRAPHIC_LAYER_API Queue : public VulkanObject<vk::raii::Queue>
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Queue");

	public:

		Queue() = default;
		Queue(const Queue& other) = default;
		Queue(Queue&& other) = default;

		Queue& operator = (const Queue& other) = default;
		Queue& operator = (Queue&& other) = default;

		~Queue() noexcept = default;

		void create(Device& device, uint32_t queueFamilyIndex);

		vk::SubmitInfo createSubmitInfo(
			std::span<Semaphore*> waitSemaphores,
			vk::PipelineStageFlags& waitPipelineStageFlags,
			std::span<CommandBuffer*> commandBuffers,
			std::span<Semaphore*> signalSemaphores);

		void submit(const vk::SubmitInfo& submitInfo, Fence& fence);

		void submit(const vk::SubmitInfo& submitInfo);

		static vk::PresentInfoKHR createPresentInfo(
			std::span<Semaphore*> waitSemaphores,
			std::span<SwapChain*> swapChains,
			uint32_t& imageIndex);

		void present(vk::PresentInfoKHR& presentInfo);

		void copyBufferToBufferWaitIdle(CommandBuffer& commandBuffer, Buffer& sourceBuffer, Buffer& destinationBuffer);
	};

}