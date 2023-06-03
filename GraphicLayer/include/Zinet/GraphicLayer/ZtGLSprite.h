#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGLDrawableObject.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLMVP.h"
#include "Zinet/GraphicLayer/ZtGLTextureRegion.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class RendererContext;

	// TODO (Mid)
	// Refactor Sprite
	// The class should contains only info that is need to create DrawInfo
	// The class shouldn't contains data that is already in DrawInfo
	class ZINET_GRAPHIC_LAYER_API Sprite : public DrawableObject
	{

	protected:

		inline static ConsoleLogger Logger = ConsoleLogger::Create("Sprite");

	public:

		Sprite();
		Sprite(const Sprite& other) = default;
		Sprite(Sprite&& other) = default;

		Sprite& operator = (const Sprite& other) = default;
		Sprite& operator = (Sprite&& other) = default;

		~Sprite() noexcept = default;

		DrawInfo createDrawInfo(RendererContext& rendererContext) const override;

		const Transform& getTransform() const override { return transform; }
		void setTransform(const Transform& newTransform);

		void setTextureRegion(const TextureRegion& newTextureRegion, const Vector2f& textureSize);
		const TextureRegion& getTextureRegion() const { return textureRegion; }

		std::vector<std::uint16_t> getIndices() const;

	protected:

		void createIndexBuffer(IndexBuffer& indexBuffer, RendererContext& rendererContext) const;
		void createVertexBuffer(VertexBuffer& vertexBuffer, RendererContext& rendererContext) const;
		void createUniformBuffers(std::vector<UniformBuffer>& uniformBuffers, RendererContext& rendererContext) const;

		TextureRegion textureRegion;
		Transform transform;
	};

}