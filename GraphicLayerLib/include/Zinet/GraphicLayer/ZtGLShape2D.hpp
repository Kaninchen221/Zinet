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

		std::vector<RenderStates::Descriptor> createRenderStatesDescriptors() const override;
		
		const Transform& getTransform() const override { return transform; }
		void setTransform(const Transform& newTransform) override { transform = newTransform; }

	protected:

		void createUniformBuffers(std::vector<UniformBuffer>& uniformBuffers, RendererContext& rendererContext) const;

		Transform transform;
	};
}