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

	// TODO (Low) Fix it after DrawInfo refactor
	class ZINET_GRAPHIC_LAYER_API TileMap : public DrawableObject
	{

	protected:

		inline static ConsoleLogger Logger = ConsoleLogger::Create("TileMap");

	public:

		const inline static std::uint16_t VerticesPerTile = 4u;

		TileMap();
		TileMap(const TileMap& other) = default;
		TileMap(TileMap&& other) = default;

		TileMap& operator = (const TileMap& other) = default;
		TileMap& operator = (TileMap&& other) = default;

		~TileMap() noexcept = default;

		DrawInfo createDrawInfo(RendererContext& rendererContext) const override;

		const Transform& getTransform() const override { return transform; }
		void setTransform(const Transform& newTransform);

		const std::vector<UniformBuffer>& getUniformBuffers() const { return uniformBuffers; };

		void setTextureRegion(const TextureRegion& newTextureRegion, const Vector2f& textureSize);
		const TextureRegion& getTextureRegion() const { return textureRegion; }

		void setTilesCount(const Vector2ui& count) { tilesCount = count; }
		const Vector2ui& getTilesCount() const { return tilesCount; }

	protected:

		void createIndexBuffer(RendererContext& rendererContext);
		VertexBuffer createVertexBuffer(RendererContext& rendererContext) const;
		void createDescriptors();
		void createUniformBuffers(RendererContext& rendererContext);
		void createMVPUniformBuffer(RendererContext& rendererContext);
		void createTextureRegionUniformBuffer(RendererContext& rendererContext);

		IndexBuffer indexBuffer;
		std::vector<std::uint16_t> indices;
		std::vector<RenderStates::Descriptor> descriptors;
		std::vector<UniformBuffer> uniformBuffers;
		std::vector<RenderStates::Image> imageDrawInfos;
		TextureRegion textureRegion;
		Transform transform;
		Vector2ui tilesCount{ 1u, 1u };
	};

}