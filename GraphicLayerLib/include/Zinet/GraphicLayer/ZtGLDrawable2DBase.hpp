#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLDrawableBase.hpp"

#include "Zinet/Core/ZtLogger.hpp"

#include <span>

namespace zt::gl
{
	class RendererContext;
	struct TextureRegion;

	class ZINET_GRAPHIC_LAYER_API Drawable2DBase : public DrawableBase
	{

	public:

		Drawable2DBase() = default;
		Drawable2DBase(const Drawable2DBase& other) = default;
		Drawable2DBase(Drawable2DBase&& other) = default;

		Drawable2DBase& operator = (const Drawable2DBase& other) = default;
		Drawable2DBase& operator = (Drawable2DBase&& other) = default;

		~Drawable2DBase() noexcept = default;

		Vector2ui getAbsoluteSize() const override { return { 1u, 1u }; }

		const Vector4f& getColor() const { return color; }
		void setColor(const Vector4f& newColor) { color = newColor; }

		static constexpr std::array<std::uint16_t, 6u> GetDefaultIndices() { return { 0u, 1u, 2u, 2u, 3u,0u }; }

		static constexpr size_t GetDefaultVerticesCount() { return 4u; }

		virtual void createIndexBuffer(IndexBuffer& indexBuffer, const std::span<std::uint16_t>& indices, RendererContext& rendererContext) const;

		virtual void createVertexBuffer(VertexBuffer& vertexBuffer, const TextureRegion& textureRegion, RendererContext& rendererContext) const;

	protected:

		Vector4f color{};

	};
}