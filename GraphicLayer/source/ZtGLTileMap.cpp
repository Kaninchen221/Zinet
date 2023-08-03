#include "Zinet/GraphicLayer/ZtGLTileMap.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"

namespace zt::gl
{
	DrawInfo TileMap::createDrawInfo(RendererContext& rendererContext) const
	{
		DrawInfo drawInfo;
		drawInfo.indices = getIndices();
		createIndexBuffer(drawInfo.indexBuffer, drawInfo.indices, rendererContext);
		createVertexBuffer(drawInfo.vertexBuffer, rendererContext);
		createUniformBuffers(drawInfo.uniformBuffers, rendererContext);
		createStorageBuffers(drawInfo.storageBuffers, rendererContext);
		drawInfo.MVPBufferIndex = 0u;
		drawInfo.instanceCount = tilesCount.x * tilesCount.y;

		return std::move(drawInfo);
	}

	void TileMap::setTransform(const Transform& newTransform)
	{
		transform = newTransform;
	}

	void TileMap::setDefaultShaderTextureRegion(const TextureRegion& newTextureRegion, const Vector2f& textureSize)
	{
		defaultShaderTextureRegion = newTextureRegion.toShaderTextureRegion(textureSize);
	}

	std::vector<std::uint16_t> TileMap::getIndices() const
	{
		return 
		{
			0u,
			1u,
			2u,
			2u,
			3u,
			0u
		};
	}

	void TileMap::createIndexBuffer(IndexBuffer& indexBuffer, std::vector<std::uint16_t>& indices, RendererContext& rendererContext) const
	{
		std::uint64_t size = sizeof(std::uint16_t) * indices.size();

		Buffer::CreateInfo bufferCreateInfo{
			rendererContext.getDevice(),
				rendererContext.getVma(),
				indexBuffer.createCreateInfo(size),
				indexBuffer.createVmaAllocationCreateInfo(false, false)
		};

		indexBuffer.create(bufferCreateInfo);
		indexBuffer.fillWithStdContainer(indices);
	}

	void TileMap::createVertexBuffer(VertexBuffer& vertexBuffer, RendererContext& rendererContext) const
	{
		Vector2f UV = defaultShaderTextureRegion.offset;

		std::vector<Vertex> vertices;
		Vertex vertex;
		vertex.setPosition({ -0.5f, 0.5f, 0.f });
		vertex.setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		vertex.setTextureCoordinates(UV);
		vertices.push_back(vertex);

		vertex.setPosition({ 0.5f, 0.5f, 0.f });
		vertex.setColor({ 0.0f, 1.0f, 0.0f, 1.0f });
		UV.x += defaultShaderTextureRegion.size.x;
		vertex.setTextureCoordinates(UV);
		vertices.push_back(vertex);

		vertex.setPosition({ 0.5f, -0.5f, 0.f });
		vertex.setColor({ 0.0f, 0.0f, 1.0f, 1.0f });
		UV = defaultShaderTextureRegion.offset;
		UV += defaultShaderTextureRegion.size;
		vertex.setTextureCoordinates(UV);
		vertices.push_back(vertex);

		vertex.setPosition({ -0.5f, -0.5f, 0.f });
		vertex.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		UV = defaultShaderTextureRegion.offset;
		UV.y += defaultShaderTextureRegion.size.y;
		vertex.setTextureCoordinates(UV);
		vertices.push_back(vertex);

		Buffer::CreateInfo bufferCreateInfo{
			rendererContext.getDevice(),
				rendererContext.getVma(),
				vertexBuffer.createCreateInfo(vertices.size() * sizeof(Vertex)),
				vertexBuffer.createVmaAllocationCreateInfo(false, false)
		};

		vertexBuffer.create(bufferCreateInfo);
		vertexBuffer.fillWithStdContainer(vertices);
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
			.vkBufferCreateInfo = tilesCountUniformBuffer.createCreateInfo(sizeof(decltype(tilesCount))),
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