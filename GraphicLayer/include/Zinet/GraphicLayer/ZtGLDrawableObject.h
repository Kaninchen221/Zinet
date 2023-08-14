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
			std::ranges::sized_range auto& textures,
			std::ranges::sized_range auto& samplers,
			std::ranges::sized_range auto& bindings) const;
	};
	
	std::vector<RenderStates::Image> DrawableObject::createRenderStatesImages(
		std::ranges::sized_range auto& textures,
		std::ranges::sized_range auto& samplers,
		std::ranges::sized_range auto& bindings) const
	{
		if (textures.size() != samplers.size() || textures.size() != bindings.size())
		{
			Logger->error("All of the containers must have the same size");
			return {};
		}

		std::vector<RenderStates::Image> result;
		result.reserve(textures.size());

		auto samplerIt = samplers.begin();
		auto bindingIt = bindings.begin();
		for (const Texture& texture : textures)
		{
			result.emplace_back(
				texture.getImageBuffer(),
				*samplerIt,
				texture.getImageView(),
				texture.getImage().getImageLayouts().front(),
				static_cast<std::uint32_t>(*bindingIt)
			);

			++samplerIt;
			++bindingIt;
		}

		return result;
	}
}