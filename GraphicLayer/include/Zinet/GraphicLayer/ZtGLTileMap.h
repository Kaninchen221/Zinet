#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGLDrawableObject.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLMVP.h"
#include "Zinet/GraphicLayer/ZtGLTextureRegion.h"
#include "Zinet/GraphicLayer/ZtGLDrawable2DBase.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class RendererContext;

	class ZINET_GRAPHIC_LAYER_API TileMap : public Drawable2DBase
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("TileMap");

		const constexpr inline static size_t VerticesPerTile = 4u;

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

	protected:

		void createUniformBuffers(std::vector<UniformBuffer>& uniformBuffers, RendererContext& rendererContext) const;
		void createStorageBuffers(std::vector<StorageBuffer>& storageBuffers, RendererContext& rendererContext) const;

		Transform transform;
		Vector2ui tilesCount{ 1u, 1u };
		TextureRegion defaultShaderTextureRegion;
		std::vector<TextureRegion> tilesTextureRegions;
	};

}