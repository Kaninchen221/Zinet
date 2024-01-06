#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"
#include "Zinet/GraphicLayer/ZtGLDrawableBase.hpp"
#include "Zinet/GraphicLayer/ZtGLVertex.hpp"
#include "Zinet/GraphicLayer/ZtGLMVP.hpp"
#include "Zinet/GraphicLayer/ZtGLTextureRegion.hpp"
#include "Zinet/GraphicLayer/ZtGLDrawable2DBase.hpp"

#include "Zinet/Core/ZtLogger.hpp"
#include "Zinet/Core/ZtTime.hpp"

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

		bool update(const zt::core::Time& elapsedTime);

		Flipbook::State getCurrentState() const { return currentState; }

		void play();

		void pause();

		std::vector<RenderStates::Descriptor> createRenderStatesDescriptors() const override;

		void updateStorageBuffers(std::span<StorageBuffer> storageBuffers) const override;

	protected:

 		Transform transform;
		std::vector<Frame> frames;
		size_t currentFrameIndex = 0u;
		Flipbook::State currentState = Flipbook::State::Pause;
		zt::core::Time totalElapsedTime;

		void createUniformBuffers(std::vector<UniformBuffer>& uniformBuffers, RendererContext& rendererContext) const;
		void createStorageBuffers(std::vector<StorageBuffer>& storageBuffers, RendererContext& rendererContext) const;
	};

}