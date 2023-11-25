#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"
#include "Zinet/Engine/ECS/ZtComponent.h"

#include "Zinet/GraphicLayer/ZtGLDrawInfo.h"

namespace zt::gl
{
	class DrawableBase;
	class RendererContext;
}

namespace zt::engine
{
	class ZINET_ENGINE_API DrawableComponent : public ecs::Component
	{
	public:

		DrawableComponent() = default;
		DrawableComponent(core::UniqueID&& uniqueID, core::ID entityID) : Component(std::move(uniqueID), entityID) {}
		DrawableComponent(const DrawableComponent& other)  = default;
		DrawableComponent(DrawableComponent&& other) = default;

		DrawableComponent& operator = (const DrawableComponent& other) = default;
		DrawableComponent& operator = (DrawableComponent&& other) = default;

		~DrawableComponent() noexcept = default;

		gl::DrawInfo createDrawInfo(gl::RendererContext& rendererContext) const;

		gl::RenderStates createRenderStates() const;

		template<std::derived_from<gl::DrawableBase> DrawableType>
		void create();

		const gl::DrawableBase* getDrawable() const { return drawable.get(); };
		gl::DrawableBase* getDrawable() { return drawable.get(); };

		bool isReadyToUse() const override { return drawable.operator bool(); }

		const std::vector<gl::Shader>& getShaders() const { return shaders; };
		void setShaders(const std::vector<gl::Shader>& newShaders) { shaders = newShaders; }

	protected:

		std::unique_ptr<gl::DrawableBase> drawable;
		std::vector<gl::Shader> shaders;

	};

	template<std::derived_from<gl::DrawableBase> DrawableType>
	inline void engine::DrawableComponent::create()
	{
		drawable = std::make_unique<DrawableType>();
	}

}

