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

	class ZINET_GRAPHIC_LAYER_API TileMap : public DrawableObject
	{

	protected:

		inline static ConsoleLogger Logger = ConsoleLogger::Create("TileMap");

	public:

		TileMap();
		TileMap(const TileMap& other) = default;
		TileMap(TileMap&& other) = default;

		TileMap& operator = (const TileMap& other) = default;
		TileMap& operator = (TileMap&& other) = default;

		~TileMap() noexcept = default;

		void create(RendererContext& rendererContext);

		void copyFrom(const TileMap& other, RendererContext& rendererContext);

		const DrawInfo& getDrawInfo() const override;

		void createDrawInfo(std::span<Shader> shaders, const Texture& texture, const Sampler& sampler) override;

		const Transform& getTransform() const override { return transform; }
		void setTransform(const Transform& newTransform);

		UniformBuffer* getMVPUniformBuffer() override;

		const std::vector<UniformBuffer>& getUniformBuffers() const { return uniformBuffers; };

		void setTextureRegion(const TextureRegion& newTextureRegion) { textureRegion = newTextureRegion; }
		const TextureRegion& getTextureRegion() const { return textureRegion; }

	protected:

		void createIndexBuffer(RendererContext& rendererContext);
		void createVertexBuffer(RendererContext& rendererContext);
		void createDescriptors();
		void createUniformBuffers(RendererContext& rendererContext);
		void createMVPUniformBuffer(RendererContext& rendererContext);
		void createTextureRegionUniformBuffer(RendererContext& rendererContext);

		DrawInfo drawInfo;

		VertexBuffer vertexBuffer;
		std::vector<Vertex> vertices;
		IndexBuffer indexBuffer;
		std::vector<std::uint16_t> indices;
		std::vector<DrawInfo::Descriptor> descriptors;
		std::vector<UniformBuffer> uniformBuffers;
		std::vector<DrawInfo::Image> imageDrawInfos;
		TextureRegion textureRegion;
		Transform transform;
	};

}