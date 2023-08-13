#include "Zinet/GraphicLayer/ZtGLTileMap.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"

namespace zt::gl
{
	DrawInfo TileMap::createDrawInfo(RendererContext& rendererContext) const
	{
		auto defaultIndices = getDefaultIndices();

		DrawInfo drawInfo;
		drawInfo.indices = std::vector<std::uint16_t>{ defaultIndices.begin(), defaultIndices.end() };
		createVertexBuffer(drawInfo.vertexBuffer, defaultShaderTextureRegion, rendererContext);
		createIndexBuffer(drawInfo.indexBuffer, drawInfo.indices, rendererContext);
		createStorageBuffers(drawInfo.storageBuffers, rendererContext);
		createUniformBuffers(drawInfo.uniformBuffers, rendererContext);
		drawInfo.MVPBufferIndex = 0u;
		drawInfo.instanceCount = tilesCount.x * tilesCount.y;

		return std::move(drawInfo);
	}

	void TileMap::setDefaultShaderTextureRegion(const TextureRegion& newTextureRegion, const Vector2f& textureSize)
	{
		defaultShaderTextureRegion = newTextureRegion.toShaderTextureRegion(textureSize);
	}

	void TileMap::createUniformBuffers(std::vector<UniformBuffer>& uniformBuffers, RendererContext& rendererContext) const
	{
		uniformBuffers.reserve(2u);

		UniformBuffer& mvpUniformBuffer = uniformBuffers.emplace_back();
		Buffer::CreateInfo mvpBufferCreateInfo{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkBufferCreateInfo = mvpUniformBuffer.createCreateInfo(sizeof(MVP)),
			.allocationCreateInfo = mvpUniformBuffer.createVmaAllocationCreateInfo(false, false)
		};
		mvpUniformBuffer.create(mvpBufferCreateInfo);
		mvpUniformBuffer.setBinding(0u);

		UniformBuffer& tilesCountUniformBuffer = uniformBuffers.emplace_back();
		Buffer::CreateInfo tilesCountBufferCreateInfo{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkBufferCreateInfo = tilesCountUniformBuffer.createCreateInfo(sizeof(Vector2f)),
			.allocationCreateInfo = tilesCountUniformBuffer.createVmaAllocationCreateInfo(false, false)
		};
		tilesCountUniformBuffer.create(tilesCountBufferCreateInfo);
		tilesCountUniformBuffer.setBinding(3u);

		tilesCountUniformBuffer.fillWithObject(Vector2f{tilesCount});
	}

	void TileMap::createStorageBuffers(std::vector<StorageBuffer>& storageBuffers, RendererContext& rendererContext) const
	{
		StorageBuffer& storageBuffer = storageBuffers.emplace_back();
		Buffer::CreateInfo bufferCreateInfo{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkBufferCreateInfo = storageBuffer.createCreateInfo(tilesTextureRegions.size() * VerticesPerTile * sizeof(Vector2f)),
			.allocationCreateInfo = storageBuffer.createVmaAllocationCreateInfo(false, false)
		};
		storageBuffer.create(bufferCreateInfo);
		storageBuffer.setBinding(2u);

		std::vector<Vector2f> uvs;
		for (const TextureRegion& textureRegion : tilesTextureRegions)
		{
			Vector2f UV = textureRegion.offset;
			uvs.push_back(UV);

			UV.x += textureRegion.size.x;
			uvs.push_back(UV);

			UV = textureRegion.offset;
			UV += textureRegion.size;
			uvs.push_back(UV);

			UV = textureRegion.offset;
			UV.y += textureRegion.size.y;
			uvs.push_back(UV);
		}

		storageBuffer.fillWithStdContainer(uvs);
	}

	void TileMap::setTilesTextureRegions(const std::vector<TextureRegion>& newTilesTextureRegions, const Vector2f& textureSize)
	{
		tilesTextureRegions.clear();
		tilesTextureRegions.reserve(newTilesTextureRegions.size());
		for (size_t index = 0u; index < newTilesTextureRegions.size(); ++index)
		{
			TextureRegion textureRegion = newTilesTextureRegions[index].toShaderTextureRegion(textureSize);
			tilesTextureRegions.push_back(textureRegion);
		}
	}

}