#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLSTBImage.h"
#include "Zinet/GraphicLayer/ZtGLMVP.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"
#include "Zinet/GraphicLayer/ZtGLDrawableObject.h"

#include "Zinet/Core/ZtClock.h"

#include <gtest/gtest.h>

#include <filesystem>
#include <vector>
#include <chrono>

namespace zt::gl::tests
{

	class RendererTests : public ::testing::Test
	{
	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("RendererTests");

		const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

		Renderer renderer;

		// TODO Refactor this class to Drawable Object, Sprite
		struct Sprite : public DrawableObject
		{
			Sprite() = delete;
			Sprite(const Sprite& other) = delete;
			Sprite(Sprite&& other) = default;
			Sprite& operator = (const Sprite& other) = delete;
			Sprite& operator = (Sprite& other) = default;
			~Sprite() noexcept;
			Sprite(Renderer& rendererRef) : renderer(rendererRef) {}

			std::vector<Shader> shaders;
			std::vector<DrawInfo::Descriptor> descriptors;
			VertexBuffer vertexBuffer;
			std::vector<Vertex> vertices;
			IndexBuffer indexBuffer;
			std::vector<std::uint16_t> indices;
			std::vector<UniformBuffer> uniformBuffers;

			std::vector<DrawInfo::Image> imageDrawInfos;
			std::vector<Sampler> samplers;

			STBImage stbImage;
			Texture texture;

			MVP mvp;
			Renderer& renderer;

			void createShaders();
			void createDescriptors();
			void createVertexBuffer();
			void createIndexBuffer();
			void createUniformBuffers();
			void createImageDrawInfos();

			void createDrawInfo() override;

			void rotateImage();
			void rotateImage2();

			const DrawInfo& getDrawInfo() const override { return drawInfo; }

			DrawInfo drawInfo{ .vertexBuffer = vertexBuffer, .indexBuffer = indexBuffer };
		};

	};

	TEST_F(RendererTests, Draw)
	{
		zt::gl::GLFW::UnhideWindow();
		typedef void(Renderer::* ExpectedFunctionDeclaration)(const DrawInfo&);
		using FunctionDeclaration = decltype(&Renderer::draw);

		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		renderer.initialize();

		int count = 2;
		plf::colony<Sprite> sprites;
		sprites.reserve(count);
		for (size_t i = 0u; i < count; ++i)
		{
			auto sprite = sprites.emplace(renderer);
			sprite->createShaders();
			sprite->createDescriptors();
			sprite->createVertexBuffer();
			sprite->createIndexBuffer();
			sprite->createUniformBuffers();
			sprite->createImageDrawInfos();
			sprite->createDrawInfo();
		}

		zt::Clock clock;
		clock.start();

		while (!renderer.getWindow().shouldBeClosed())
		{
			//Logger->info("preDraw");
			renderer.preDraw();

			//Logger->info("Draw 0");
			auto sprite = sprites.begin();
			sprite->rotateImage();
			renderer.draw(sprite->getDrawInfo());

			//Logger->info("Draw 1");
			sprite = sprites.begin();
			sprite++;
			sprite->rotateImage2();
			renderer.draw(sprite->getDrawInfo());

			glfwPollEvents();

			//Logger->info("postDraw");
			renderer.postDraw();

			if (clock.getElapsedTime().getAsSeconds() > 4)
			{
				// TODO Add close window function to Window class
				glfwSetWindowShouldClose(renderer.getWindow().getInternal(), true);
			}
		}

		renderer.getQueue()->waitIdle();
		renderer.getDevice()->waitIdle();
	}

	RendererTests::Sprite::~Sprite() noexcept
	{
		shaders.clear();
		descriptors.clear();
		vertexBuffer.~VertexBuffer();
		indexBuffer.~IndexBuffer();
		uniformBuffers.clear();

		imageDrawInfos.clear();
		samplers.clear();
		stbImage.~STBImage();
	}

	void RendererTests::Sprite::createShaders()
	{
		shaders.emplace_back();
		shaders[0].setType(ShaderType::Vertex);
		shaders[0].loadFromFile((ContentPath / "shader.vert").string());
		shaders[0].compile();

		shaders.emplace_back();
		shaders[1].setType(ShaderType::Fragment);
		shaders[1].loadFromFile((ContentPath / "shader.frag").string());
		shaders[1].compile();
	}

	void RendererTests::Sprite::createDescriptors()
	{
		DrawInfo::Descriptor descriptor;
		descriptor.binding = 0;
		descriptor.descriptorType = vk::DescriptorType::eUniformBuffer;
		descriptor.count = 1;
		descriptor.shaderType = ShaderType::Vertex;
		descriptors.push_back(descriptor);

		descriptor.binding = 1;
		descriptor.descriptorType = vk::DescriptorType::eCombinedImageSampler;
		descriptor.count = 1;
		descriptor.shaderType = ShaderType::Fragment;
		descriptors.push_back(descriptor);
	}

	void RendererTests::Sprite::createVertexBuffer()
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

	void RendererTests::Sprite::createIndexBuffer()
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

	void RendererTests::Sprite::createUniformBuffers()
	{
		UniformBuffer& uniformBuffer = uniformBuffers.emplace_back();
		BufferCreateInfo bufferCreateInfo{
			.device = renderer.getDevice(),
			.vma = renderer.getVma(),
			.vkBufferCreateInfo = uniformBuffer.createCreateInfo(sizeof(decltype(mvp))),
			.allocationCreateInfo = uniformBuffer.createVmaAllocationCreateInfo(false, true)
		};
		uniformBuffer.create(bufferCreateInfo);
		uniformBuffer.fillWithObject(mvp);
	}

	void RendererTests::Sprite::createImageDrawInfos()
	{
		if (!stbImage.load((ContentPath / "texture.png").string()))
		{
			FAIL() << "Can't load texture image";
			return;
		}

		Sampler& sampler = samplers.emplace_back();
		vk::SamplerCreateInfo samplerCreateInfo = sampler.createCreateInfo();
		sampler.create(renderer.getDevice(), samplerCreateInfo);

		texture.create(stbImage, renderer);
		imageDrawInfos.push_back(texture.createImageDrawInfo(sampler));
	}

	void RendererTests::Sprite::createDrawInfo()
	{
		drawInfo.indices = indices;
		drawInfo.shaders = shaders;
		drawInfo.descriptors = descriptors;
		drawInfo.uniformBuffers = uniformBuffers;
		drawInfo.images = imageDrawInfos;
	}

	void RendererTests::Sprite::rotateImage()
	{
		float time = static_cast<float>(glfwGetTime());
		mvp.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		mvp.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, -1.f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		mvp.proj = glm::perspective(glm::radians(45.0f), 800.f / 400.f, 0.1f, 10.0f);
		mvp.proj[1][1] *= -1;

		uniformBuffers[0].fillWithObject(mvp);
	}

	void RendererTests::Sprite::rotateImage2()
	{
		float time = -1.f;
		time *= static_cast<float>(glfwGetTime());
		mvp.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		mvp.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 1.f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		mvp.proj = glm::perspective(glm::radians(45.0f), 800.f / 400.f, 0.1f, 10.0f);
		mvp.proj[1][1] *= -1;

		uniformBuffers[0].fillWithObject(mvp);
	}

}