#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"
#include "Zinet/GraphicLayer/ZtGLDrawableBase.hpp"
#include "Zinet/GraphicLayer/ZtGLVertex.hpp"
#include "Zinet/GraphicLayer/ZtGLMVP.hpp"
#include "Zinet/GraphicLayer/ZtGLTextureRegion.hpp"
#include "Zinet/GraphicLayer/ZtGLDrawable2DBase.hpp"

#include "Zinet/Core/ZtLogger.hpp"

namespace zt::gl
{
	class RendererContext;

	class ZINET_GRAPHIC_LAYER_API Sprite : public Drawable2DBase
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Sprite");

	public:

		Sprite() = default;
		Sprite(const Sprite& other) = default;
		Sprite(Sprite&& other) = default;

		Sprite& operator = (const Sprite& other) = default;
		Sprite& operator = (Sprite&& other) = default;

		~Sprite() noexcept = default;

		DrawInfo createDrawInfo(RendererContext& rendererContext) const override;

		const Transform& getTransform() const override { return transform; }
		void setTransform(const Transform& newTransform) override { transform = newTransform; }

		void setTextureRegion(const TextureRegion& newTextureRegion, const Vector2f& textureSize);
		const TextureRegion& getTextureRegion() const { return textureRegion; }

		std::vector<RenderStates::Descriptor> createRenderStatesDescriptors() const override;

	protected:

		void createUniformBuffers(std::vector<UniformBuffer>& uniformBuffers, RendererContext& rendererContext) const;

		Transform transform;
		TextureRegion textureRegion;
	};
}