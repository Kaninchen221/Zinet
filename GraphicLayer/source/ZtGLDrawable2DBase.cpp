#include "Zinet/GraphicLayer/ZtGLDrawable2DBase.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLTextureRegion.h"

namespace zt::gl
{
	void Drawable2DBase::createIndexBuffer(IndexBuffer& indexBuffer, const std::span<std::uint16_t>& indices, RendererContext& rendererContext) const
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

	void Drawable2DBase::createVertexBuffer(VertexBuffer& vertexBuffer, const TextureRegion& textureRegion, RendererContext& rendererContext) const
	{
		Vector2f UV = textureRegion.offset;

		std::vector<Vertex> vertices;
		Vertex vertex;
		vertex.setPosition({ 0.0f, 0.0f, 0.f });
		vertex.setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		vertex.setTextureCoordinates(UV);
		vertices.push_back(vertex);

		vertex.setPosition({ 1.0f, 0.0f, 0.f });
		vertex.setColor({ 0.0f, 1.0f, 0.0f, 1.0f });
		UV.x += textureRegion.size.x;
		vertex.setTextureCoordinates(UV);
		vertices.push_back(vertex);

		vertex.setPosition({ 1.0f, -1.0f, 0.f });
		vertex.setColor({ 0.0f, 0.0f, 1.0f, 1.0f });
		UV = textureRegion.offset;
		UV += textureRegion.size;
		vertex.setTextureCoordinates(UV);
		vertices.push_back(vertex);

		vertex.setPosition({ 00.f, -1.0f, 0.f });
		vertex.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		UV = textureRegion.offset;
		UV.y += textureRegion.size.y;
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

}