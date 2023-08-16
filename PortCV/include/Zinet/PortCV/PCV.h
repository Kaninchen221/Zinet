#pragma once

#include "Zinet/Core/ZtLogger.h"
#include "Zinet/Core/ZtClock.h"

#include "Zinet/GraphicLayer/Imgui/ZtGLImgui.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLCamera.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"
#include "Zinet/GraphicLayer/ZtGLSampler.h"

#include <filesystem>

#include "Objects.h"

using namespace zt::core;
using namespace zt::gl;

class PortCV
{
	inline static auto Logger = ConsoleLogger::Create("PortCV");
	const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH;
	const inline static std::filesystem::path TexturesPath = ContentPath / "textures";
	const inline static std::filesystem::path ShadersPath = ContentPath / "shaders";

public:

	void start();

protected:

	void setup();
	void loop();

	void imguiCamera();

	Renderer renderer;
	Imgui imgui;
	Camera camera;

	Clock gameClock;

	Campfire campfire;
	std::vector<Shader> campfireShaders;
	Texture campfireTexture;

	void setupCampfire();

	Character character;
	std::vector<Shader> characterShaders;
	Texture characterTexture;

	void setupCharacter();

	Sampler sampler;

	CommandBuffer commandBuffer;
};