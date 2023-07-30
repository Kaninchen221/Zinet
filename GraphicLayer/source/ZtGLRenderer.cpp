#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLDrawableObject.h"
#include "Zinet/GraphicLayer/ZtGLMVP.h"

#include <map>

namespace zt::gl
{

	Renderer::Renderer()
	{
		GLFW::Init();
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
		GLFW::Deinit();
	}

	void Renderer::initialize()
	{
		rendererContext.initialize();
		Window::SetRenderer(*this);

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
		vk::ClearValue depthBufferClearColor;
		depthBufferClearColor.color = vk::ClearColorValue{ 1.f, 1.f, 1.f, 1.f };
		depthBufferClearColor.depthStencil = vk::ClearDepthStencilValue{ 1.0f, 0u };
		std::array<vk::ClearValue, 2u> clearColors{clearColor, depthBufferClearColor};

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

	void Renderer::draw(const DrawableObject& drawableObject, RenderStates& renderStates)
	{
		DrawInfo& drawInfo = drawInfos.emplace_back(std::move(drawableObject.createDrawInfo(rendererContext)));
		createRendererPipeline(renderStates, drawInfo);

		updateMVPUniformBuffer(renderStates, drawInfo);

		drawCommandBuffer.bindPipeline(rendererPipelines.back().getPipeline());
		drawCommandBuffer.bindVertexBuffer(0u, drawInfo.vertexBuffer, vk::DeviceSize{ 0 });

		vk::DeviceSize indexBufferOffset{ 0 };
		drawCommandBuffer.bindIndexBuffer(drawInfo.indexBuffer, indexBufferOffset, vk::IndexType::eUint16);

		if (rendererPipelines.back().getDescriptorSets().has_value())
		{
			RendererPipeline& rendererPipeline = rendererPipelines.back();
			CommandBuffer::BindDescriptorSetsInfo bindDescriptorSetsInfo
			{
				.bindPoint = vk::PipelineBindPoint::eGraphics,
				.pipelineLayout = rendererPipeline.getPipelineLayout(),
				.firstSet = 0,
				.descriptorSets = rendererPipeline.getDescriptorSets().value(),
				.dynamicOffsets = {}
			};

			drawCommandBuffer.bindDescriptorSets(bindDescriptorSetsInfo);
		}

		drawCommandBuffer->drawIndexed(static_cast<std::uint32_t>(drawInfo.indices.size()), 1, 0, 0, 0);
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

	void Renderer::informAboutWindowResize(int width, int height)
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

		rendererContext.informAboutWindowResize(width, height);

		if (informAboutWindowResizeCallback != nullptr)
			std::invoke(informAboutWindowResizeCallback, width, height);
	}

	void Renderer::createRendererPipeline(const RenderStates& renderStates, const DrawInfo& drawInfo)
	{
		RendererPipeline& newRendererPipeline = rendererPipelines.emplace_back();
		RendererPipeline::CreateInfo rendererPipelineCreateInfo
		{
			.renderStates = renderStates,
			.drawInfo = drawInfo,
			.device = rendererContext.getDevice(),
			.renderPass = rendererContext.getRenderPass(),
			.commandPool = rendererContext.getCommandPool(),
			.swapExtent = rendererContext.getSwapExtent()
		};
		newRendererPipeline.create(rendererPipelineCreateInfo);

		newRendererPipeline.updateDescriptorSets(rendererContext.getDevice());
	}

	void Renderer::updateMVPUniformBuffer(RenderStates& renderStates, DrawInfo& drawInfo)
	{
		if (drawInfo.uniformBuffers.size() == 0)
			return;

		UniformBuffer& MVPUniformBuffer = drawInfo.uniformBuffers[drawInfo.MVPBufferIndex];
		if (MVPUniformBuffer != nullptr)
		{
			MVP mvp;
			mvp.model = renderStates.modelMatrix;
			mvp.view = renderStates.camera.viewMatrix();
			mvp.proj = renderStates.camera.perspectiveMatrix();
			MVPUniformBuffer.fillWithObject(mvp);
		}
	}

	void Renderer::submitCommandsWaitIdle(SubmitCommandsWaitIdleFunction function)
	{
		CommandBuffer commandBuffer;
		commandBuffer.allocateCommandBuffer(rendererContext.getDevice(), rendererContext.getCommandPool());

		rendererContext.getQueue().submitWaitIdle(commandBuffer, function);
	}

	void Renderer::setInformAboutWindowResizeCallback(InformAboutWindowResizeCallback callback)
	{
		if (callback != nullptr)
		{
			informAboutWindowResizeCallback = callback;
		}
	}

}