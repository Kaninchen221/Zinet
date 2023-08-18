#include "Zinet/PortCV/PCV.h"

#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLSTBImage.h"

#include "imgui.h"

#include <vector>

void PortCV::start()
{
	Logger->info("Start");
	GLFW::Init(false);

	setup();

	loop();

	GLFW::Deinit();
	Logger->info("Stop");
}

void PortCV::setup()
{
	Logger->info("Setup");

	GLFW::UnhideWindow();

	renderer.initialize();

	RendererContext& rendererContext = renderer.getRendererContext();

	commandBuffer.allocateCommandBuffer(rendererContext.getDevice(), rendererContext.getCommandPool());

	vk::SamplerCreateInfo samplerCreateInfo = sampler.createCreateInfo(campfireTexture.getImage().getMipmapLevels());
	sampler.create(rendererContext.getDevice(), samplerCreateInfo);

	setupCampfire();
	setupCharacter();
}

void PortCV::loop()
{
	camera.setPosition({ 0.0f, 0.0f, -30.0f });
	camera.setFar(1000.f);

	RendererContext& rendererContext = renderer.getRendererContext();
	imgui.preinit(rendererContext);
	imgui.init(rendererContext);

	// Campfire RenderStates
	auto campfireTextures = std::vector{ std::cref(campfireTexture) };
	auto campfireSamplers = std::vector{ std::cref(sampler) };
	auto campfireBindings = std::vector<size_t>{ 1u };
	std::vector<RenderStates::Image> images = campfire.flipbook.createRenderStatesImages(campfireTextures, campfireSamplers, campfireBindings);
	std::vector<RenderStates::Descriptor> descriptors = campfire.flipbook.createRenderStatesDescriptors();

	RenderStates campfireRenderStates
	{
		.shaders = campfireShaders,
		.descriptors = descriptors,
		.images = images
	};
	// End Campfire RenderStates

	// Character RenderStates
	auto characterTextures = std::vector{ std::cref(characterTexture) };
	auto characterSamplers = std::vector{ std::cref(sampler) };
	auto characterBindings = std::vector<size_t>{ 1u };
	std::vector<RenderStates::Image> characterImages = character.sprite.createRenderStatesImages(characterTextures, characterSamplers, characterBindings);
	std::vector<RenderStates::Descriptor> characterDescriptors = character.sprite.createRenderStatesDescriptors();

	RenderStates characterRenderStates
	{
		.shaders = characterShaders,
		.descriptors = characterDescriptors,
		.images = characterImages
	};
	// End Character RenderStates

	gameClock.start();
	campfire.flipbook.play();
	campfire.flipbook.update(gameClock.getElapsedTime());
	while (!rendererContext.getWindow().shouldBeClosed())
	{
		imgui.update();

		ImGui::NewFrame();
	
		ImGui::Begin("Debug");

		ImGui::Text("Camera");
		imguiCamera();
		ImGui::Text("Campfire");
		Object::ImguiDrawable2DBase(campfire.flipbook, 0u);
		ImGui::Text("Sprite");
		Object::ImguiDrawable2DBase(character.sprite, 1u);

		ImGui::End();

		ImGui::EndFrame();

		ImGui::Render();

		renderer.preDraw();

		{ // Draw
			{ // Campfire
				auto modelMatrix = campfire.flipbook.getTransform().toMatrix();
				auto viewMatrix = camera.viewMatrix();
				auto projectionMatrix = camera.projectionMatrix();
				campfireRenderStates.mvp = MVP{ modelMatrix, viewMatrix, projectionMatrix };

				campfire.flipbook.update(gameClock.getElapsedTime());
				renderer.draw<Vertex>(campfire.flipbook, campfireRenderStates);
			}

			{ // Character
				auto modelMatrix = character.sprite.getTransform().toMatrix();
				auto viewMatrix = camera.viewMatrix();
				auto projectionMatrix = camera.projectionMatrix();
				characterRenderStates.mvp = MVP{ modelMatrix, viewMatrix, projectionMatrix };
				renderer.draw<Vertex>(character.sprite, characterRenderStates);
			}
		}

		glfwPollEvents();

		imgui.draw(renderer.getDrawCommandBuffer());

		renderer.postDraw();
	}

	rendererContext.getQueue()->waitIdle();
	rendererContext.getDevice()->waitIdle();
}

void PortCV::setupCampfire()
{
	campfireShaders.clear();

	campfireShaders.emplace_back();
	campfireShaders[0].setType(ShaderType::Vertex);
	campfireShaders[0].loadFromFile((ShadersPath / "flipbookShader.vert").string());
	campfireShaders[0].compile();

	campfireShaders.emplace_back();
	campfireShaders[1].setType(ShaderType::Fragment);
	campfireShaders[1].loadFromFile((ShadersPath / "shader.frag").string());
	campfireShaders[1].compile();

	STBImage stbImage;
	if (stbImage.load((TexturesPath / "campfire.png").string()))
	{
		commandBuffer.begin();
		campfireTexture.create({ renderer.getRendererContext(), commandBuffer, false, vk::Format::eR8G8B8A8Srgb, stbImage.getSize() });
		campfireTexture.loadFromSTBImage(commandBuffer, stbImage);
		campfireTexture.getImage().changeLayout(commandBuffer, vk::ImageLayout::eShaderReadOnlyOptimal, vk::PipelineStageFlagBits::eFragmentShader);
		commandBuffer.end();
	}
	else
	{
		Logger->error("Failed load texture");
	}

	renderer.getRendererContext().getQueue().submitWaitIdle(commandBuffer);

	campfire.create();
}

void PortCV::setupCharacter()
{
	characterShaders.clear();

	characterShaders.emplace_back();
	characterShaders[0].setType(ShaderType::Vertex);
	characterShaders[0].loadFromFile((ShadersPath / "shader.vert").string());
	characterShaders[0].compile();

	characterShaders.emplace_back();
	characterShaders[1].setType(ShaderType::Fragment);
	characterShaders[1].loadFromFile((ShadersPath / "shader.frag").string());
	characterShaders[1].compile();

	STBImage stbImage;
	if (stbImage.load((TexturesPath / "hero.png").string()))
	{
		commandBuffer.begin();
		characterTexture.create({ renderer.getRendererContext(), commandBuffer, false, vk::Format::eR8G8B8A8Srgb, stbImage.getSize() });
		characterTexture.loadFromSTBImage(commandBuffer, stbImage);
		characterTexture.getImage().changeLayout(commandBuffer, vk::ImageLayout::eShaderReadOnlyOptimal, vk::PipelineStageFlagBits::eFragmentShader);
		commandBuffer.end();
	}
	else
	{
		Logger->error("Failed load texture");
	}

	renderer.getRendererContext().getQueue().submitWaitIdle(commandBuffer);

	character.create();
}

void PortCV::imguiCamera()
{
	Vector3f cameraPos = camera.getPosition();
	std::array<float, 3> rawCameraPosition;
	rawCameraPosition = Math::FromVectorToArray(cameraPos);
	std::string posName = std::string{ "Camera pos " };
	ImGui::SliderFloat3(posName.c_str(), rawCameraPosition.data(), -30.00f, 30.0f);
	cameraPos = Math::FromArrayToVector(rawCameraPosition);
	camera.setPosition(cameraPos);

	Vector3f cameraTarget = camera.getTarget();
	std::array<float, 3> rawCameraTarget;
	rawCameraTarget = Math::FromVectorToArray(cameraTarget);
	std::string targetName = std::string{ "Camera target " };
	ImGui::SliderFloat3(targetName.c_str(), rawCameraTarget.data(), -5.00f, 5.0f);
	cameraTarget = Math::FromArrayToVector(rawCameraTarget);
	camera.setTarget(cameraTarget);

	float cameraFar = camera.getFar();
	ImGui::SliderFloat("Camera 'Far'", &cameraFar, 10.f, 1000.f);
	camera.setFar(cameraFar);
}
