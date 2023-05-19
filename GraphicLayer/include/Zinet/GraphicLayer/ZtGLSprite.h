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
	class Renderer;

	class ZINET_GRAPHIC_LAYER_API Sprite : public DrawableObject
	{

	protected:

		inline static ConsoleLogger Logger = ConsoleLogger::Create("Sprite");

	public:

		Sprite();
		Sprite(const Sprite& other) = default;
		Sprite(Sprite&& other) = default;

		Sprite& operator = (const Sprite& other) = default;
		Sprite& operator = (Sprite&& other) = default;

		~Sprite() noexcept = default;

		void create(Renderer& renderer);

		void copyFrom(const Sprite& other, Renderer& renderer);

		const DrawInfo& getDrawInfo() const override;

		void createDrawInfo(std::span<Shader> shaders, const Texture& texture, const Sampler& sampler) override;

		const Transform& getTransform() const override { return transform; }
		void setTransform(const Transform& newTransform);

		UniformBuffer* getMVPUniformBuffer() override;

		const std::vector<UniformBuffer>& getUniformBuffers() const { return uniformBuffers; };

		void setTextureRegion(const TextureRegion& newTextureRegion) { textureRegion = newTextureRegion; }
		const TextureRegion& getTextureRegion() const { return textureRegion; }

	protected:

		void createIndexBuffer(Renderer& renderer);
		void createVertexBuffer(Renderer& renderer);
		void createDescriptors();
		void createUniformBuffers(Renderer& renderer);
		void createMVPUniformBuffer(Renderer& renderer);
		void createTextureRegionUniformBuffer(Renderer& renderer);

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