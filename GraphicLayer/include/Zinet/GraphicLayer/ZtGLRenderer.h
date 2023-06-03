#pragma once

#include "Zinet/GraphicLayer/ZtGLRendererContext.h"

#include "Zinet/GraphicLayer/ZtGLDrawInfo.h"
#include "Zinet/GraphicLayer/ZtGLSemaphore.h"
#include "Zinet/GraphicLayer/ZtGLFence.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLRendererPipeline.h"
#include "Zinet/GraphicLayer/ZtGLRenderTarget.h"
#include "Zinet/GraphicLayer/ZtGLCamera.h"

#include "Zinet/Core/ZtLogger.h"

#include <plf_colony.h>
#include <memory>

namespace zt::gl
{
	class DrawableObject;

	// TODO (Mid) Instanced rendering
	// TODO (Mid) Fix memory leak: The problem is probably Pipeline, PipelineLayout or/and validation layers. We should compile Vulkan API/Validation layers by the hand
	class ZINET_GRAPHIC_LAYER_API Renderer
	{

	protected:

		inline static ConsoleLogger Logger = ConsoleLogger::Create("Renderer");

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

}