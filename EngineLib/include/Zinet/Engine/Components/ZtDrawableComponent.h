#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"
#include "Zinet/Engine/ECS/ZtComponent.h"

#include "Zinet/GraphicLayer/ZtGLDrawInfo.h"

namespace zt::gl
{
	class DrawableBase;
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

		gl::DrawInfo getDrawInfo() const;

		gl::RenderStates getRenderStates() const;

		// Use perhaps variant?

	};

}

