#pragma once

#include "Zinet/GraphicLayer/ZtGLRendererContext.hpp"

#include "Zinet/GraphicLayer/ZtGLDrawInfo.hpp"
#include "Zinet/GraphicLayer/ZtGLSemaphore.hpp"
#include "Zinet/GraphicLayer/ZtGLFence.hpp"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.hpp"
#include "Zinet/GraphicLayer/ZtGLRendererPipeline.hpp"
#include "Zinet/GraphicLayer/ZtGLRenderTarget.hpp"
#include "Zinet/GraphicLayer/ZtGLCamera.hpp"
#include "Zinet/GraphicLayer/ZtGLDrawableBase.hpp"

#include "Zinet/Core/ZtLogger.hpp"

#include <plf_colony.h>
#include <memory>

namespace zt::gl
{
	class ZINET_GRAPHIC_LAYER_API Renderer
	{

	protected:

		inline static core::ConsoleLogger Logger = core::ConsoleLogger::Create("Renderer");

	public:

		Renderer();
		Renderer(const Renderer& other) = default;
		Renderer(Renderer&& other) = default;

		Renderer& operator = (const Renderer& other) = default;
		Renderer& operator = (Renderer&& other) = default;

		~Renderer() noexcept;

		RendererContext& getRendererContext() { return rendererContext; }
		const RendererContext& getRendererContext() const { return rendererContext; }

		CommandBuffer& getDrawCommandBuffer() { return drawCommandBuffer; }
		const CommandBuffer& getDrawCommandBuffer() const { return drawCommandBuffer; }

		void initialize();

		void preDraw();

		template<class VertexType>
		void draw(DrawInfo&& newDrawInfo, RenderStates& renderStates);

		void postDraw();

		typedef void (*SubmitCommandsWaitIdleFunction)(CommandBuffer& commandBuffer);
		void submitCommandsWaitIdle(SubmitCommandsWaitIdleFunction function);

	protected:

		inline static void WindowResizeCallback(void* userPointer, const Vector2ui& size);

		void windowResizeCallback_Internal(const Vector2ui& size);

		void submit();
		void present(uint32_t& image);

		template<typename VertexType>
		void createRendererPipeline(const RenderStates& renderStates, const DrawInfo& drawInfo);

		/// You need to update manually uniform and storage buffers before calling this function
		template<class VertexType>
		void draw_internal(DrawInfo& drawable, RenderStates& renderStates);

		void updateMVPUniformBuffer(const RenderStates& renderStates, DrawInfo& drawInfo);

		RendererContext rendererContext;

		std::pair<vk::Result, uint32_t> nextImageToDraw;

		Semaphore imageAvailableSemaphore;
		Semaphore renderingFinishedSemaphore;
		Fence drawFence;

		std::vector<RendererPipeline> rendererPipelines;
		CommandBuffer drawCommandBuffer;

		// Submit info
		std::array<Semaphore*, 1> submitWaitSemaphores;
		vk::PipelineStageFlags submitWaitPipelineStageFlags;
		std::vector<vk::CommandBuffer> submitCommandBuffers;
		std::array<Semaphore*, 1> submitSignalSemaphores;
		vk::SubmitInfo submitInfo;

		// Present info
		std::array<Semaphore*, 1> presentWaitSemaphores = { &renderingFinishedSemaphore };
		std::array<SwapChain*, 1> presentSwapChains = { &rendererContext.getSwapChain() };
		vk::PresentInfoKHR presentInfo;

		std::vector<DrawInfo> drawInfos;
	};

	template<class VertexType>
	void Renderer::draw(DrawInfo&& newDrawInfo, RenderStates& renderStates)
	{
		DrawInfo& drawInfo = drawInfos.emplace_back(std::move(newDrawInfo));

		draw_internal<VertexType>(drawInfo, renderStates);
	}

	template<class VertexType>
	void Renderer::draw_internal(DrawInfo& drawInfo, RenderStates& renderStates)
	{
		createRendererPipeline<VertexType>(renderStates, drawInfo);

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

		drawCommandBuffer->drawIndexed(static_cast<std::uint32_t>(drawInfo.indices.size()), drawInfo.instanceCount, 0, 0, 0);
	}

	template<typename VertexType>
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
		newRendererPipeline.create<VertexType>(rendererPipelineCreateInfo);

		newRendererPipeline.updateDescriptorSets(rendererContext.getDevice());
	}
}