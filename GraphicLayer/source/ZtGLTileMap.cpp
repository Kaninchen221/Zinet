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
		drawInfo.MVPBufferIndex = 0u;

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
		std::vector<std::uint16_t> indices;
		auto addTile = [&indices](std::uint16_t offset)
		{
			std::initializer_list<std::uint16_t> indicesPerTile = 
			{ 
				0u + offset,
				1u + offset,
				2u + offset,
				2u + offset,
				3u + offset,
				0u + offset
			};

			indices.insert(indices.end(), indicesPerTile);
		};

		const std::uint16_t verticesPerTile = 4u;
		const std::uint16_t count = static_cast<std::uint16_t>(tilesCount.x * tilesCount.y);
		indices.reserve(verticesPerTile * count);
		for (std::uint16_t index = 0; index < count; ++index)
		{
			addTile(index * verticesPerTile);
		}

		return indices;
	}

	void TileMap::createIndexBuffer(IndexBuffer& indexBuffer, std::vector<std::uint16_t>& indices, RendererContext& rendererContext) const
	{
		std::uint64_t size = sizeof(std::uint16_t) * indices.size();

		Buffer::CreateInfo bufferCreateInfo{
			rendererContext.getDevice(),
				rendererContext.getVma(),
				indexBuffer.createCreateInfo(size),
				indexBuffer.createVmaAllocationCreateInfo(false, true)
		};

		indexBuffer.create(bufferCreateInfo);
		indexBuffer.fillWithStdContainer(indices);
	}

	void TileMap::createVertexBuffer(VertexBuffer& vertexBuffer, RendererContext& rendererContext) const
	{
		std::vector<Vertex> vertices;

		auto addTile = [&vertices](const TextureRegion& textureRegion, const Vector3f& offset)
		{
			Vector2f UV = textureRegion.offset;

			Vertex vertex;
			Vector3f position = { 0.f, 0.f, 0.f };
			position.x += offset.x;
			position.y -= offset.y;
			vertex.setPosition(position);
			vertex.setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
			vertex.setTextureCoordinates(UV);
			vertices.push_back(vertex);

			position = { 1.f, 0.f, 0.f };
			position.x += offset.x;
			position.y -= offset.y;
			vertex.setPosition(position);
			vertex.setColor({ 0.0f, 1.0f, 0.0f, 1.0f });
			UV.x += textureRegion.size.x;
			vertex.setTextureCoordinates(UV);
			vertices.push_back(vertex);

			position = { 1.f, -1.f, 0.f };
			position.x += offset.x;
			position.y -= offset.y;
			vertex.setPosition(position);
			vertex.setColor({ 0.0f, 0.0f, 1.0f, 1.0f });
			UV = textureRegion.offset;
			UV += textureRegion.size;
			vertex.setTextureCoordinates(UV);
			vertices.push_back(vertex);

			position = { 0.f, -1.f, 0.f };
			position.x += offset.x;
			position.y -= offset.y;
			vertex.setPosition(position);
			vertex.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
			UV = textureRegion.offset;
			UV.y += textureRegion.size.y;
			vertex.setTextureCoordinates(UV);
			vertices.push_back(vertex);
		};

		vertices.reserve(tilesCount.x * tilesCount.y * 4u);
		Vector2ui tileIndex = { 0u, 0u };
		for (tileIndex.y; tileIndex.y < tilesCount.y; ++tileIndex.y)
		{
			for (tileIndex.x = 0u; tileIndex.x < tilesCount.x; ++tileIndex.x)
			{
				Vector3f positionOffset = { tileIndex.x, tileIndex.y, 0.f };
				size_t shaderTextureRegionIndex = tilesCount.x * tileIndex.y + tileIndex.x;
				if (shaderTextureRegionIndex < tilesTextureRegions.size())
				{
					const TextureRegion& shaderTextureRegion = tilesTextureRegions[shaderTextureRegionIndex];
					addTile(shaderTextureRegion, positionOffset);
				}
				else
				{
					addTile(defaultShaderTextureRegion, positionOffset);
				}
			}
		}

		Buffer::CreateInfo bufferCreateInfo{
			rendererContext.getDevice(),
				rendererContext.getVma(),
				vertexBuffer.createCreateInfo(vertices.size() * sizeof(Vertex)),
				vertexBuffer.createVmaAllocationCreateInfo(false, true)
		};

		vertexBuffer.create(bufferCreateInfo);
		vertexBuffer.fillWithStdContainer(vertices);
	}

	void TileMap::createUniformBuffers(std::vector<UniformBuffer>& uniformBuffers, RendererContext& rendererContext) const
	{
		UniformBuffer& uniformBuffer = uniformBuffers.emplace_back();
		Buffer::CreateInfo bufferCreateInfo{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkBufferCreateInfo = uniformBuffer.createCreateInfo(sizeof(MVP)),
			.allocationCreateInfo = uniformBuffer.createVmaAllocationCreateInfo(false, true)
		};
		uniformBuffer.create(bufferCreateInfo);
		uniformBuffer.setBinding(0u);
	}

	void TileMap::setTilesTextureRegions(const std::vector<TextureRegion>& newTilesTextureRegions, const Vector2f& textureSize)
	{
		tilesTextureRegions.reserve(newTilesTextureRegions.size());
		for (size_t index = 0; index < newTilesTextureRegions.size(); ++index)
		{
			TextureRegion textureRegion = newTilesTextureRegions[index].toShaderTextureRegion(textureSize);
			tilesTextureRegions.push_back(textureRegion);
		}
	}

}