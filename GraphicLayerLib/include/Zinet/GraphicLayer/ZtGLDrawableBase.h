#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.h"
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

	class ZINET_GRAPHIC_LAYER_API DrawableBase
	{
		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("DrawableBase");

	public:

		DrawableBase() = default;
		DrawableBase(const DrawableBase& other) = default;
		DrawableBase(DrawableBase&& other) = default;

		DrawableBase& operator = (const DrawableBase& other) = default;
		DrawableBase& operator = (DrawableBase&& other) = default;

		virtual ~DrawableBase() noexcept = default;

		virtual DrawInfo createDrawInfo(RendererContext& rendererContext) const = 0;

		virtual const Transform& getTransform() const = 0;

		virtual void setTransform(const Transform& newTransform) = 0;

		virtual Vector2ui getAbsoluteSize() const = 0;

		virtual std::vector<RenderStates::Descriptor> createRenderStatesDescriptors() const { return {}; }

		std::vector<RenderStates::Image> createRenderStatesImages(
			const std::vector<std::reference_wrapper<const Texture>>& textures,
			const std::vector<std::reference_wrapper<const Sampler>>& samplers,
			const std::vector<size_t>& bindings) const;

		virtual void updateUniformBuffers(std::span<UniformBuffer> uniformBuffers) const {}
		virtual void updateStorageBuffers(std::span<StorageBuffer> storageBuffers) const {}
	};
}