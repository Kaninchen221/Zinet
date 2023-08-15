#pragma once

#include "Zinet/GraphicLayer/ZtGLRendererContext.h"

#include "Zinet/GraphicLayer/ZtGLDrawInfo.h"
#include "Zinet/GraphicLayer/ZtGLSemaphore.h"
#include "Zinet/GraphicLayer/ZtGLFence.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLRendererPipeline.h"
#include "Zinet/GraphicLayer/ZtGLRenderTarget.h"
#include "Zinet/GraphicLayer/ZtGLCamera.h"
#include "Zinet/GraphicLayer/ZtGLDrawableObject.h"

#include "Zinet/Core/ZtLogger.h"

#include <plf_colony.h>
#include <memory>

namespace zt::gl
{
	class ZINET_GRAPHIC_LAYER_API Renderer
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Renderer");

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
		void draw(const DrawableObject& drawableObject, RenderStates& renderStates);

		void postDraw();

		void informAboutWindowResize(int width, int height);

		typedef void (*InformAboutWindowResizeCallback)(int width, int height);
		void setInformAboutWindowResizeCallback(InformAboutWindowResizeCallback callback);

		typedef void (*SubmitCommandsWaitIdleFunction)(CommandBuffer& commandBuffer);
		void submitCommandsWaitIdle(SubmitCommandsWaitIdleFunction function);

	protected:

		void submit();
		void present(uint32_t& image);

		template<typename VertexType>
		void createRendererPipeline(const RenderStates& renderStates, const DrawInfo& drawInfo);

		void updateMVPUniformBuffer(RenderStates& renderStates, DrawInfo& drawInfo);

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

		InformAboutWindowResizeCallback informAboutWindowResizeCallback = nullptr;

		std::vector<DrawInfo> drawInfos;
	};

	template<class VertexType>
	void Renderer::draw(const DrawableObject& drawableObject, RenderStates& renderStates)
	{
		DrawInfo& drawInfo = drawInfos.emplace_back(std::move(drawableObject.createDrawInfo(rendererContext)));
		createRendererPipeline<VertexType>(renderStates, drawInfo);

		drawableObject.updateUniformBuffers(drawInfo.uniformBuffers);
		drawableObject.updateStorageBuffers(drawInfo.storageBuffers);

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