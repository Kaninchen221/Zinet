#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"
#include "Zinet/Engine/Components/ZtDrawableComponent.h"
#include "Zinet/Engine/ECS/ZtSystem.h"

#include "Zinet/GraphicLayer/ZtGLRenderer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::engine
{
	class ZINET_ENGINE_API RendererSystem : public ecs::System<DrawableComponent>
	{
	private:

		inline static auto Logger = core::ConsoleLogger::Create("RendererSystem");

	public:

		using BaseT = ecs::System<DrawableComponent>;

		RendererSystem() = default;
		RendererSystem(const RendererSystem& other) = default;
		RendererSystem(RendererSystem&& other) = default;
		
		RendererSystem& operator = (const RendererSystem& other) = default;
		RendererSystem& operator = (RendererSystem&& other) = default;
		
		~RendererSystem() noexcept = default;
	
		gl::Renderer& getRenderer() { return renderer; }
		const gl::Renderer& getRenderer() const { return renderer; }

		bool initialize() override;

		void preUpdate(core::Time timeElapsed) override;
		void update(core::Time timeElapsed) override;
		void postUpdate(core::Time timeElapsed) override;

		void setCamera(const gl::Camera& newCamera) { camera = newCamera; }

	protected:

		gl::Renderer renderer;
		gl::Camera camera;
		std::vector<gl::RenderStates> savedRenderStates;

	};

}

