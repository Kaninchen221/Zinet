#include "Zinet/GraphicLayer/ZtGLSprite.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"

namespace zt::gl
{
	Sprite::Sprite()
		: drawInfo{ .vertexBuffer = vertexBuffer, .indexBuffer = indexBuffer }
	{}

	const DrawInfo& Sprite::getDrawInfo() const
	{
		return drawInfo;
	}

	void Sprite::createDrawInfo(std::span<Shader> shaders, const Texture& texture, const Sampler& sampler)
	{
		imageDrawInfos.push_back(texture.createImageDrawInfo(sampler));

		drawInfo.indices = indices;
		drawInfo.shaders = shaders;
		drawInfo.descriptors = descriptors;
		drawInfo.uniformBuffers = uniformBuffers;
		drawInfo.images = imageDrawInfos;
	}

	void Sprite::create(Renderer& renderer)
	{
		createDescriptors();
		createVertexBuffer(renderer);
		createIndexBuffer(renderer);
		createUniformBuffers(renderer);
	}

	void Sprite::createDescriptors()
	{
		DrawInfo::Descriptor descriptor;
		
		// MVP
		descriptor.binding = 0;
		descriptor.descriptorType = vk::DescriptorType::eUniformBuffer;
		descriptor.count = 1;
		descriptor.shaderType = ShaderType::Vertex;
		descriptors.push_back(descriptor);

		// TextureRegion
		//descriptor.binding = 0;
		//descriptor.descriptorType = vk::DescriptorType::eUniformBuffer;
		//descriptor.count = 1;
		//descriptor.shaderType = ShaderType::Vertex;
		//descriptors.push_back(descriptor);

		// Texture
		descriptor.binding = 1;
		descriptor.descriptorType = vk::DescriptorType::eCombinedImageSampler;
		descriptor.count = 1;
		descriptor.shaderType = ShaderType::Fragment;
		descriptors.push_back(descriptor);
	}

	void Sprite::createVertexBuffer(Renderer& renderer)
	{
		Vertex vertex;
		vertex.setPosition({ -0.5f, -0.5f, 0.f });
		vertex.setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		vertex.setTextureCoordinates({ 1.0f, 0.0f });
		vertices.push_back(vertex);

		vertex.setPosition({ 0.5f, -0.5f, 0.f });
		vertex.setColor({ 0.0f, 1.0f, 0.0f, 1.0f });
		vertex.setTextureCoordinates({ 0.0f, 0.0f });
		vertices.push_back(vertex);

		vertex.setPosition({ 0.5f, 0.5f, 0.f });
		vertex.setColor({ 0.0f, 0.0f, 1.0f, 1.0f });
		vertex.setTextureCoordinates({ 0.0f, 1.0f });
		vertices.push_back(vertex);

		vertex.setPosition({ -0.5f, 0.5f, 0.f });
		vertex.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		vertex.setTextureCoordinates({ 1.0f, 1.0f });
		vertices.push_back(vertex);

		BufferCreateInfo bufferCreateInfo{
			renderer.getDevice(),
			renderer.getVma(),
			vertexBuffer.createCreateInfo(vertices.size() * sizeof(Vertex)),
			vertexBuffer.createVmaAllocationCreateInfo(false, true)
		};

		vertexBuffer.create(bufferCreateInfo);
		vertexBuffer.fillWithStdContainer(vertices);
	}

	void Sprite::createIndexBuffer(Renderer& renderer)
	{
		indices = { 0, 1, 2, 2, 3, 0 };
		std::uint64_t size = sizeof(decltype(indices)::value_type) * indices.size();

		BufferCreateInfo bufferCreateInfo{
			renderer.getDevice(),
			renderer.getVma(),
			indexBuffer.createCreateInfo(size),
			indexBuffer.createVmaAllocationCreateInfo(false, true)
		};

		indexBuffer.create(bufferCreateInfo);
		indexBuffer.fillWithStdContainer(indices);
	}

	void Sprite::createUniformBuffers(Renderer& renderer)
	{
		uniformBuffers.reserve(2u);

		// MVP
		UniformBuffer& uniformBuffer = uniformBuffers.emplace_back();
		BufferCreateInfo bufferCreateInfo{
			.device = renderer.getDevice(),
			.vma = renderer.getVma(),
			.vkBufferCreateInfo = uniformBuffer.createCreateInfo(sizeof(decltype(mvp))),
			.allocationCreateInfo = uniformBuffer.createVmaAllocationCreateInfo(false, true)
		};
		uniformBuffer.create(bufferCreateInfo);
		uniformBuffer.fillWithObject(mvp);

		//createTextureRegionUniformBuffer(renderer);
	}

	void Sprite::rotate()
	{
		float time = static_cast<float>(glfwGetTime());
		mvp.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		mvp.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, -1.f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		mvp.proj = glm::perspective(glm::radians(45.0f), 800.f / 400.f, 0.1f, 10.0f);
		mvp.proj[1][1] *= -1;

		uniformBuffers[0].fillWithObject(mvp);
	}

	void Sprite::rotate2()
	{
		float time = -1.f;
		time *= static_cast<float>(glfwGetTime());
		mvp.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		mvp.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 1.f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		mvp.proj = glm::perspective(glm::radians(45.0f), 800.f / 400.f, 0.1f, 10.0f);
		mvp.proj[1][1] *= -1;

		uniformBuffers[0].fillWithObject(mvp);
	}

	void Sprite::createTextureRegionUniformBuffer(Renderer& renderer)
	{
		UniformBuffer& uniformBuffer = uniformBuffers.emplace_back();
		BufferCreateInfo bufferCreateInfo{
			.device = renderer.getDevice(),
			.vma = renderer.getVma(),
			.vkBufferCreateInfo = uniformBuffer.createCreateInfo(sizeof(decltype(textureRegion))),
			.allocationCreateInfo = uniformBuffer.createVmaAllocationCreateInfo(false, true)
		};
		uniformBuffer.create(bufferCreateInfo);
		uniformBuffer.fillWithObject(textureRegion);
	}

}