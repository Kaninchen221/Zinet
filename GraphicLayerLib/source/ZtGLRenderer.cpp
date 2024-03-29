#include "Zinet/GraphicLayer/ZtGLRenderer.hpp"

#include "Zinet/GraphicLayer/ZtGLInstance.hpp"
#include "Zinet/GraphicLayer/ZtGLMVP.hpp"

#include "Zinet/Window/ZtGLFW.hpp"
#include "Zinet/Window/ZtWindow.hpp"

#include <map>

namespace zt::gl
{

	Renderer::Renderer()
	{
		wd::GLFW::Init();
	}

	Renderer::~Renderer() noexcept
	{
		Queue& queue = rendererContext.getQueue();
		if (queue != nullptr)
			queue->waitIdle();

		Device& device = rendererContext.getDevice();
		if (device != nullptr)
			device->waitIdle();

		if (drawFence != nullptr && drawFence.getStatus() != vk::Result::eNotReady)
			device.waitForFence(drawFence);

		rendererPipelines.clear();
		wd::GLFW::Deinit();
	}

	void Renderer::initialize()
	{
		rendererContext.initialize();

		rendererContext.getWindow().setWindowResizedCallback(this, &Renderer::WindowResizeCallback);

		Device& device = rendererContext.getDevice();
		imageAvailableSemaphore.create(device);
		renderingFinishedSemaphore.create(device);

		vk::FenceCreateInfo fenceCreateInfo = drawFence.createSignaledFenceCreateInfo();
		drawFence.create(device, fenceCreateInfo);
		
		drawCommandBuffer.allocateCommandBuffer(device, rendererContext.getCommandPool());
	}

	void Renderer::preDraw()
	{
		Device& device = rendererContext.getDevice();
		device.waitForFence(drawFence);
		device.resetFence(drawFence);

		std::uint16_t nextImageTimeout = std::numeric_limits<std::uint16_t>::max();
		Fence acquireNextImageFence;
		nextImageToDraw = rendererContext.getSwapChain().acquireNextImage(nextImageTimeout, imageAvailableSemaphore, acquireNextImageFence);
		if (nextImageToDraw.first != vk::Result::eSuccess)
			Logger->error("Failed to acquire next image from swap chain");

		rendererPipelines.clear();
		submitCommandBuffers.clear();

		drawCommandBuffer.reset();
		drawCommandBuffer.begin();

		vk::Rect2D renderArea;
		renderArea.offset = vk::Offset2D{ 0, 0 };
		renderArea.extent = rendererContext.getSwapExtent();

		vk::ClearValue clearColor = vk::ClearColorValue{ std::array<float, 4>{ 0.5f, 0.5f, 0.5f, 0.f } };
		vk::ClearValue depthStencilBufferClearColor;
		depthStencilBufferClearColor.color = vk::ClearColorValue{ 1.f, 1.f, 1.f, 1.f };
		depthStencilBufferClearColor.depthStencil = vk::ClearDepthStencilValue{ 1.0f, 0u };
		std::array<vk::ClearValue, 2u> clearColors{clearColor, depthStencilBufferClearColor};

		CommandBuffer::BeginRenderPassInfo beginRenderPassInfo
		{
			.renderPass = rendererContext.getRenderPass(),
			.framebuffer = rendererContext.getRenderTargets()[nextImageToDraw.second].getFramebuffer(),
			.renderArea = renderArea,
			.clearValues = clearColors
		};
		drawCommandBuffer.beginRenderPass(beginRenderPassInfo);

		drawInfos.clear();
	}

	void Renderer::postDraw()
	{
		if (drawCommandBuffer.getIsCommandBufferInvalid())
		{
			drawCommandBuffer.clear();
			drawCommandBuffer.allocateCommandBuffer(rendererContext.getDevice(), rendererContext.getCommandPool());
			drawCommandBuffer.setIsCommandBufferInvalid(false);
			return;
		}

		drawCommandBuffer.endRenderPass();
		drawCommandBuffer.end();

		submit();
		present(nextImageToDraw.second);
	}

	void Renderer::submit()
	{
		submitCommandBuffers.push_back(*drawCommandBuffer.getInternal());

		submitWaitSemaphores = { &imageAvailableSemaphore };
		submitWaitPipelineStageFlags = vk::PipelineStageFlagBits::eColorAttachmentOutput;
		submitSignalSemaphores = { &renderingFinishedSemaphore };

		submitInfo = rendererContext.getQueue().createSubmitInfo(
			submitWaitSemaphores,
			submitWaitPipelineStageFlags,
			submitCommandBuffers,
			submitSignalSemaphores);

		rendererContext.getQueue().submitWithFence(submitInfo, drawFence);
	}

	void Renderer::present(uint32_t& image)
	{
		vk::Result results[1];
		presentWaitSemaphores = { &renderingFinishedSemaphore };
		presentSwapChains = { &rendererContext.getSwapChain() };
		presentInfo = rendererContext.getQueue().createPresentInfo(
			presentWaitSemaphores,
			presentSwapChains,
			image);
		presentInfo.pResults = results;

		rendererContext.getQueue().present(presentInfo);
		if (results[0] != vk::Result::eSuccess)
			Logger->error("present return non success vk::Result");
	}

	void Renderer::updateMVPUniformBuffer(const RenderStates& renderStates, DrawInfo& drawInfo)
	{
		if (drawInfo.uniformBuffers.size() == 0)
			return;

		UniformBuffer& MVPUniformBuffer = drawInfo.uniformBuffers[drawInfo.MVPBufferIndex];
		if (MVPUniformBuffer != nullptr)
		{
			MVPUniformBuffer.fillWithObject(renderStates.mvp);
		}
	}

	void Renderer::submitCommandsWaitIdle(SubmitCommandsWaitIdleFunction function)
	{
		CommandBuffer commandBuffer;
		commandBuffer.allocateCommandBuffer(rendererContext.getDevice(), rendererContext.getCommandPool());

		rendererContext.getQueue().submitWaitIdle(commandBuffer, function);
	}

	void Renderer::windowResizeCallback_Internal(const Vector2ui& size)
	{
		drawCommandBuffer.setIsCommandBufferInvalid(true);

		while (rendererContext.getWindow().isMinimized())
		{
			glfwWaitEvents();
		}

		rendererContext.getDevice()->waitIdle();
		drawFence.clear();
		vk::FenceCreateInfo fenceCreateInfo = drawFence.createSignaledFenceCreateInfo();
		drawFence.create(rendererContext.getDevice(), fenceCreateInfo);

		imageAvailableSemaphore.clear();
		imageAvailableSemaphore.create(rendererContext.getDevice());

		renderingFinishedSemaphore.clear();
		renderingFinishedSemaphore.create(rendererContext.getDevice());

		rendererContext.informAboutWindowResize(size);
	}

	void Renderer::WindowResizeCallback(void* userPointer, const Vector2ui& size)
	{
		Renderer* renderer = static_cast<Renderer*>(userPointer);
		renderer->windowResizeCallback_Internal(size);
	}

}