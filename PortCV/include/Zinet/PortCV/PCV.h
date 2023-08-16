#pragma once

#include "Zinet/Core/ZtLogger.h"
#include "Zinet/Core/ZtClock.h"

#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLCamera.h"
#include "Zinet/GraphicLayer/Imgui/ZtGLImgui.h"

namespace core = zt::core;
namespace gl = zt::gl;

class PortCV
{
	inline static auto Logger = core::ConsoleLogger::Create("PortCV");

public:

	void start();

protected:

	void setup();
	void loop();

	gl::Renderer renderer;
	gl::Imgui imgui;
	gl::Camera camera;

	core::Clock gameClock;
};