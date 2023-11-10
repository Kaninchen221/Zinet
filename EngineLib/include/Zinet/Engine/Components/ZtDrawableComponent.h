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

		gl::DrawInfo getDrawInfo(gl::RendererContext& rendererContext) const;

		gl::RenderStates getRenderStates() const;

		template<std::derived_from<gl::DrawableBase> DrawableType>
		void create();

		const gl::DrawableBase* getDrawable() const { return drawable.get(); };
		gl::DrawableBase* getDrawable() { return drawable.get(); };

		bool isDataValid() const override { return false; }

	protected:

		std::unique_ptr<gl::DrawableBase> drawable;

	};

	template<std::derived_from<gl::DrawableBase> DrawableType>
	inline void engine::DrawableComponent::create()
	{
		drawable = std::make_unique<DrawableType>();
	}

}

