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

	class ZINET_GRAPHIC_LAYER_API TileMap : public Drawable2DBase
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("TileMap");

	public:

		TileMap() = default;
		TileMap(const TileMap& other) = default;
		TileMap(TileMap&& other) = default;

		TileMap& operator = (const TileMap& other) = default;
		TileMap& operator = (TileMap&& other) = default;

		~TileMap() noexcept = default;

		DrawInfo createDrawInfo(RendererContext& rendererContext) const override;

		const Transform& getTransform() const override { return transform; }
		void setTransform(const Transform& newTransform) override { transform = newTransform; }

		void setTilesCount(const Vector2ui& count) { tilesCount = count; }
		const Vector2ui& getTilesCount() const { return tilesCount; }

		void setDefaultShaderTextureRegion(const TextureRegion& newTextureRegion, const Vector2f& textureSize);
		const TextureRegion& getDefaultShaderTextureRegion() const { return defaultShaderTextureRegion; }

		void setTilesTextureRegions(const std::vector<TextureRegion>& newTilesTextureRegions, const Vector2f& textureSize);
		const std::vector<TextureRegion>& getTilesTextureRegions() const { return tilesTextureRegions; }
		void clearTilesTextureRegions() { tilesTextureRegions.clear(); }

		Vector2ui getAbsoluteSize() const override { return tilesCount; }

		std::vector<RenderStates::Descriptor> createRenderStatesDescriptors() const override;

	protected:

		void createUniformBuffers(std::vector<UniformBuffer>& uniformBuffers, RendererContext& rendererContext) const;
		void createStorageBuffers(std::vector<StorageBuffer>& storageBuffers, RendererContext& rendererContext) const;

		Transform transform;
		Vector2ui tilesCount{ 1u, 1u };
		TextureRegion defaultShaderTextureRegion;
		std::vector<TextureRegion> tilesTextureRegions;
	};

}