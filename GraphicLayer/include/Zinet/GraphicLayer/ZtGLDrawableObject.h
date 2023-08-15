#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLDrawInfo.h"
#include "Zinet/GraphicLayer/ZtGLTransform.h"

#include "Zinet/Core/ZtLogger.h"
#include "Zinet/Core/ZtTypeTraits.h"

#include <span>
#include <ranges>
#include <xutility>

namespace zt::gl
{
	class RendererContext;
	class Texture;
	class Sampler;

	class ZINET_GRAPHIC_LAYER_API DrawableObject
	{
		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("DrawableObject");

	public:

		DrawableObject() = default;
		DrawableObject(const DrawableObject& other) = default;
		DrawableObject(DrawableObject&& other) = default;

		DrawableObject& operator = (const DrawableObject& other) = default;
		DrawableObject& operator = (DrawableObject&& other) = default;

		virtual ~DrawableObject() noexcept = default;

		virtual DrawInfo createDrawInfo(RendererContext& rendererContext) const = 0;

		virtual const Transform& getTransform() const = 0;

		virtual void setTransform(const Transform& newTransform) = 0;

		virtual Vector2ui getAbsoluteSize() const = 0;

		virtual std::vector<RenderStates::Descriptor> createRenderStatesDescriptors() const { return {}; }

		std::vector<RenderStates::Image> createRenderStatesImages(
			std::span<std::reference_wrapper<const Texture>> textures,
			std::span<std::reference_wrapper<const Sampler>> samplers,
			std::span<size_t> bindings) const;
	};
}