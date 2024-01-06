#pragma once

#include "Zinet/Engine/ZtEngineConfig.hpp"
#include "Zinet/Engine/Components/ZtDrawableComponent.hpp"
#include "Zinet/Engine/ECS/ZtSystem.hpp"

#include "Zinet/GraphicLayer/ZtGLDrawInfo.hpp"
#include "Zinet/GraphicLayer/ZtGLRenderer.hpp"

#include "Zinet/Core/ZtLogger.hpp"

#include <vector>

namespace zt::engine
{
	class ZINET_ENGINE_API RendererSystem : public ecs::System<DrawableComponent>
	{
	private:

		inline static auto Logger = core::ConsoleLogger::Create("RendererSystem");

		struct ComponentDrawInfo
		{
			gl::DrawInfo drawInfo;
			gl::RenderStates renderStates;
		};

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

		void createDrawInputs();

		gl::Renderer renderer;
		gl::Camera camera;
		std::vector<ComponentDrawInfo> componentsDrawInputs;
	};

}

