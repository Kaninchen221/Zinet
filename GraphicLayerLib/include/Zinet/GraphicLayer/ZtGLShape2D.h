#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGLDrawableBase.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLMVP.h"
#include "Zinet/GraphicLayer/ZtGLTextureRegion.h"
#include "Zinet/GraphicLayer/ZtGLDrawable2DBase.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class RendererContext;

	class ZINET_GRAPHIC_LAYER_API Shape2D : public Drawable2DBase
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Shape2D");

	public:

		Shape2D() = default;
		Shape2D(const Shape2D& other) = default;
		Shape2D(Shape2D&& other) = default;

		Shape2D& operator = (const Shape2D& other) = default;
		Shape2D& operator = (Shape2D&& other) = default;

		~Shape2D() noexcept = default;

		DrawInfo createDrawInfo(RendererContext& rendererContext) const override;

		const Transform& getTransform() const override { return transform; }
		void setTransform(const Transform& newTransform) override { transform = newTransform; }

		std::vector<RenderStates::Descriptor> createRenderStatesDescriptors() const override;

	protected:

		void createUniformBuffers(std::vector<UniformBuffer>& uniformBuffers, RendererContext& rendererContext) const;

		Transform transform;
		TextureRegion textureRegion;
	};
}