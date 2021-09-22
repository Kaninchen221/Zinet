#include "Zinet/Core/ZtLoop.h"

#include <imgui-SFML.h>
#include <imgui.h>

#include "SFML/Graphics.hpp"

void ZtLoop::Start()
{
    CreateRenderWindow();
    ImGui::SFML::Init(Window);

	BeginPlay();

    LoopClock.Start();

    FPSClock.Start();

    while (Window.isOpen())
    {
        LoopStep();
	}

    EndPlay();

    ImGui::SFML::Shutdown();
}

void ZtLoop::LoopStep()
{
    DeltaTime = LoopClock.Restart();

    ProcessEvents();

    float TickDeltaTime = DeltaTime.GetAsSeconds();
    Tick(TickDeltaTime);

    sf::Time UpdateDeltaTime = sf::seconds(TickDeltaTime);
    ImGui::SFML::Update(Window, UpdateDeltaTime);

    Render();

    CalculateFPS();
}

void ZtLoop::BeginPlay()
{
    World.BeginPlay();
}

void ZtLoop::Tick(float DeltaTime)
{
    World.Tick(DeltaTime);
}

#ifdef ZINET_DEBUG_UI
void ZtLoop::DebugUI() const
{
    ImGui::Begin("Debug window", NULL);

    ImGui::BeginGroup();

    LoopDebugUI();

    World.ImGuiChildren();

    ImGui::EndGroup();

    ImGui::End();
}

void ZtLoop::LoopDebugUI() const
{
    if (ImGui::TreeNode("Loop"))
    {
        ImGui::Separator();
        ImGui::Text("Seconds for tick: %f seconds (Unused)", SecondsForTick);
        ImGui::Text("Tick delta time: %f seconds", DeltaTime.GetAsSeconds());
        ImGui::Text("FPS: %i", FPSCount);
        ImGui::NewLine();

        ImGui::TreePop();
    }
}
#endif

void ZtLoop::Render()
{
    DebugUI();

    Window.clear();
    ImGui::SFML::Render(Window);

    /// Here render sfml sprites and etc.

    Window.display();
}

void ZtLoop::EndPlay()
{
    World.EndPlay();
}

void ZtLoop::CreateRenderWindow()
{
    Window.create(sf::VideoMode(800, 600), "Zinet");
}

void ZtLoop::CalculateFPS()
{
    FPSCounter++;
    ZtTime FPSElapsedTime = FPSClock.GetElapsedTime();
    float FPSElapsedTimeSeconds = FPSElapsedTime.GetAsSeconds();
    if (FPSElapsedTimeSeconds >= 1.f)
    {
        FPSClock.Restart();
        FPSCount = FPSCounter;
        FPSCounter = 0;
    }
}

void ZtLoop::ProcessEvents()
{
    sf::Event Event{};
    while (Window.pollEvent(Event))
    {
        ImGui::SFML::ProcessEvent(Event);

        if (Event.type == sf::Event::Closed)
            Window.close();
    }
}
