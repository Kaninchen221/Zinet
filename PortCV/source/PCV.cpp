#include "Zinet/PortCV/PCV.h"

#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"

#include "imgui.h"

void PortCV::start()
{
	Logger->info("Start");
	gl::GLFW::Init(false);

	setup();

	loop();

	gl::GLFW::Deinit();
	Logger->info("Stop");
}

void PortCV::setup()
{
	Logger->info("Setup");

	gl::GLFW::UnhideWindow();

	renderer.initialize();
}

void PortCV::loop()
{
	camera.setPosition({ 0.0f, 0.0f, -30.0f });
	camera.setFar(1000.f);

	gl::RendererContext& rendererContext = renderer.getRendererContext();
	imgui.preinit(rendererContext);
	imgui.init(rendererContext);

	gameClock.start();
	while (!rendererContext.getWindow().shouldBeClosed())
	{
		imgui.update();

		ImGui::NewFrame();
	
		ImGui::Begin("Debug");

		ImGui::End();

		ImGui::EndFrame();

		ImGui::Render();

		renderer.preDraw();

		{ // Draw

		}

		glfwPollEvents();

		imgui.draw(renderer.getDrawCommandBuffer());

		renderer.postDraw();
	}

	rendererContext.getQueue()->waitIdle();
	rendererContext.getDevice()->waitIdle();
}
