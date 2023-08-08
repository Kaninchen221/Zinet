#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLDrawableObject.h"

#include "Zinet/Core/ZtLogger.h"

#include <span>

namespace zt::gl
{
	class RendererContext;
	struct TextureRegion;

	class ZINET_GRAPHIC_LAYER_API Drawable2DBase : public DrawableObject
	{

	public:

		Drawable2DBase() = default;
		Drawable2DBase(const Drawable2DBase& other) = default;
		Drawable2DBase(Drawable2DBase&& other) = default;

		Drawable2DBase& operator = (const Drawable2DBase& other) = default;
		Drawable2DBase& operator = (Drawable2DBase&& other) = default;

		~Drawable2DBase() noexcept = default;

		Vector2ui getAbsoluteSize() const override { return { 1u, 1u }; }

		std::array<std::uint16_t, 6u> getDefaultIndices() const;

		void createIndexBuffer(IndexBuffer& indexBuffer, const std::span<std::uint16_t>& indices, RendererContext& rendererContext) const;

		void createVertexBuffer(VertexBuffer& vertexBuffer, const TextureRegion& textureRegion, RendererContext& rendererContext) const;

	};

}