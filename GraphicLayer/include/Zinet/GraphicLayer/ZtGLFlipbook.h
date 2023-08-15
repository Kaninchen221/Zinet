#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGLDrawableObject.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLMVP.h"
#include "Zinet/GraphicLayer/ZtGLTextureRegion.h"
#include "Zinet/GraphicLayer/ZtGLDrawable2DBase.h"

#include "Zinet/Core/ZtLogger.h"
#include "Zinet/Core/ZtTime.h"

namespace zt::gl
{
	class RendererContext;

	class ZINET_GRAPHIC_LAYER_API Flipbook : public Drawable2DBase
	{

	public:

		struct Frame
		{
			zt::core::Time time;
			TextureRegion shaderTextureRegion;

			auto operator <=> (const Frame& other) const = default;
		};

		enum class State
		{
			Playing,
			Pause
		};

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Flipbook");

	public:

		Flipbook() = default;
		Flipbook(const Flipbook& other) = default;
		Flipbook(Flipbook&& other) = default;

		Flipbook& operator = (const Flipbook& other) = default;
		Flipbook& operator = (Flipbook&& other) = default;

		~Flipbook() noexcept = default;

 		DrawInfo createDrawInfo(RendererContext& rendererContext) const override;
 
		const Transform& getTransform() const override { return transform; }
		void setTransform(const Transform& newTransform) override { transform = newTransform; }

		void setFrames(const std::vector<Frame>& newFrames) { frames = newFrames; }
		const std::vector<Frame>& getFrames() const { return frames; }

		size_t getCurrentFrameIndex() const { return currentFrameIndex; }

		bool update(const zt::core::Time& currentTime);

		Flipbook::State getCurrentState() const { return currentState; }

		void play();

		void pause();

		std::vector<RenderStates::Descriptor> createRenderStatesDescriptors() const override;

	protected:

 		Transform transform;
		std::vector<Frame> frames;
		size_t currentFrameIndex = 0u;
		Flipbook::State currentState = Flipbook::State::Pause;
		zt::core::Time lastTimeUpdated{ 0.f };

		void createUniformBuffers(std::vector<UniformBuffer>& uniformBuffers, RendererContext& rendererContext) const;
		void createStorageBuffers(std::vector<StorageBuffer>& storageBuffers, RendererContext& rendererContext) const;

		void updateStorageBuffers(std::span<StorageBuffer> storageBuffers) const override;

	};

}