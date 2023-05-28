#include "Zinet/GraphicLayer/ZtGLTileMap.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"

namespace zt::gl
{
	TileMap::TileMap()
		: drawInfo{ .vertexBuffer = vertexBuffer, .indexBuffer = indexBuffer }
	{
		drawInfo.modelMatrix = transform.toMatrix();
	}

	const DrawInfo& TileMap::getDrawInfo() const
	{
		return drawInfo;
	}

	void TileMap::createDrawInfo(std::span<Shader> shaders, const Texture& texture, const Sampler& sampler)
	{
		DrawInfo::Image& imageDrawInfo = imageDrawInfos.emplace_back(texture.createImageDrawInfo(sampler));
		imageDrawInfo.binding = 1;

		drawInfo.indices = indices;
		drawInfo.shaders = shaders;
		drawInfo.descriptors = descriptors;
		drawInfo.uniformBuffers = uniformBuffers;
		drawInfo.images = imageDrawInfos;

		Vector2f textureSize = { texture.getImage().getWidth(), texture.getImage().getHeight() };
		TextureRegion shaderTextureRegion = textureRegion.toShaderTextureRegion(textureSize);
		uniformBuffers[1].fillWithObject(shaderTextureRegion);
	}

	void TileMap::create(RendererContext& rendererContext)
	{
		createDescriptors();
		createVertexBuffer(rendererContext);
		createIndexBuffer(rendererContext);
		createUniformBuffers(rendererContext);
	}

	void TileMap::createDescriptors()
	{
		DrawInfo::Descriptor descriptor;
		
		// MVP
		descriptor.binding = 0;
		descriptor.descriptorType = vk::DescriptorType::eUniformBuffer;
		descriptor.count = 1;
		descriptor.shaderType = ShaderType::Vertex;
		descriptors.push_back(descriptor);

		// TextureRegion
		descriptor.binding = 2;
		descriptor.descriptorType = vk::DescriptorType::eUniformBuffer;
		descriptor.count = 1;
		descriptor.shaderType = ShaderType::Vertex;
		descriptors.push_back(descriptor);

		// Texture
		descriptor.binding = 1;
		descriptor.descriptorType = vk::DescriptorType::eCombinedImageSampler;
		descriptor.count = 1;
		descriptor.shaderType = ShaderType::Fragment;
		descriptors.push_back(descriptor);
	}

	void TileMap::createVertexBuffer(RendererContext& rendererContext)
	{
		auto createTile = [&](const Vector3f& positionOffset)
		{
			Vertex vertex;
			vertex.setPosition(Vector3f{ 0.f, 0.f, 0.f } + positionOffset);
			vertex.setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
			vertex.setTextureCoordinates({ 0.0f, 0.0f });
			vertices.push_back(vertex);

			vertex.setPosition(Vector3f{ 1.f, 0.f, 0.f } + positionOffset);
			vertex.setColor({ 0.0f, 1.0f, 0.0f, 1.0f });
			vertex.setTextureCoordinates({ 1.0f, 0.0f });
			vertices.push_back(vertex);

			vertex.setPosition(Vector3f{ 1.f, -1.f, 0.f } + positionOffset);
			vertex.setColor({ 0.0f, 0.0f, 1.0f, 1.0f });
			vertex.setTextureCoordinates({ 1.0f, 1.0f });
			vertices.push_back(vertex);

			vertex.setPosition(Vector3f{ 0.f, -1.f, 0.f } + positionOffset);
			vertex.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
			vertex.setTextureCoordinates({ 0.0f, 1.0f });
			vertices.push_back(vertex);
		};

		for (float x = 0.f; x < tilesCount.x; x++)
		{
			float xOffset = x;
			for (float y = 0.f; y < tilesCount.y; y++)
			{
				float yOffset = y;
				createTile({ xOffset, yOffset, 0.f });
			}
		}

		BufferCreateInfo bufferCreateInfo{
			rendererContext.getDevice(),
			rendererContext.getVma(),
			vertexBuffer.createCreateInfo(vertices.size() * sizeof(Vertex)),
			vertexBuffer.createVmaAllocationCreateInfo(false, true)
		};

		vertexBuffer.create(bufferCreateInfo);
		vertexBuffer.fillWithStdContainer(vertices);
	}

	void TileMap::createIndexBuffer(RendererContext& rendererContext)
	{
		auto createTile = [&](std::uint16_t offset)
		{
			std::initializer_list<std::uint16_t> newIndices =
			{
				0u + offset,
				1u + offset,
				2u + offset,
				2u + offset,
				3u + offset,
				0u + offset
			};
			indices.insert(indices.end(), newIndices);
		};

		std::uint16_t verticesPerTile = 4u;
		std::uint16_t count = static_cast<std::uint16_t>( vertices.size() ) / verticesPerTile;
		for (std::uint16_t index = 0u; index < count; index++)
		{
			createTile(index * verticesPerTile);
		}

		std::uint64_t size = sizeof(decltype(indices)::value_type) * indices.size();

		BufferCreateInfo bufferCreateInfo{
			rendererContext.getDevice(),
			rendererContext.getVma(),
			indexBuffer.createCreateInfo(size),
			indexBuffer.createVmaAllocationCreateInfo(false, true)
		};

		indexBuffer.create(bufferCreateInfo);
		indexBuffer.fillWithStdContainer(indices);
	}

	void TileMap::createUniformBuffers(RendererContext& rendererContext)
	{
		uniformBuffers.reserve(2u);

		createMVPUniformBuffer(rendererContext);
		createTextureRegionUniformBuffer(rendererContext);
	}

	void TileMap::createTextureRegionUniformBuffer(RendererContext& rendererContext)
	{
		UniformBuffer& uniformBuffer = uniformBuffers.emplace_back();
		BufferCreateInfo bufferCreateInfo{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkBufferCreateInfo = uniformBuffer.createCreateInfo(sizeof(decltype(textureRegion))),
			.allocationCreateInfo = uniformBuffer.createVmaAllocationCreateInfo(false, true)
		};
		uniformBuffer.create(bufferCreateInfo);
		uniformBuffer.setBinding(2u);
	}

	UniformBuffer* TileMap::getMVPUniformBuffer()
	{
		if (uniformBuffers.size() < 1)
		{
			Logger->error("Uniform buffers are not created");
			return nullptr;
		}

		return &uniformBuffers[0];
	}

	void TileMap::setTransform(const Transform& newTransform)
	{
		transform = newTransform;
		drawInfo.modelMatrix = transform.toMatrix();
	}

	void TileMap::createMVPUniformBuffer(RendererContext& rendererContext)
	{
		UniformBuffer& uniformBuffer = uniformBuffers.emplace_back();
		BufferCreateInfo bufferCreateInfo{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkBufferCreateInfo = uniformBuffer.createCreateInfo(sizeof(MVP)),
			.allocationCreateInfo = uniformBuffer.createVmaAllocationCreateInfo(false, true)
		};
		uniformBuffer.create(bufferCreateInfo);
		uniformBuffer.setBinding(0u);
	}

	void TileMap::copyFrom(const TileMap& other, RendererContext& rendererContext)
	{
		create(rendererContext);
		transform = other.getTransform();
		textureRegion = other.getTextureRegion();
	}

}