#include "..\include\Zinet\Core\ZtLoop.h"

#include <iostream>
#include <limits>
#include <iomanip>
#include <cmath>

#include <imgui-SFML.h>
#include <imgui.h>

void ZtLoop::Start()
{
    CreateRenderWindow();
    ImGui::SFML::Init(Window);

	BeginPlay();

    ZtClock LoopClock;
    LoopClock.Start();

    FPSClock.Start();

    while (Window.isOpen())
    {

        TickDeltaTimeSum = TickLag;
        while (SecondsForTick > TickDeltaTimeSum)
        {
            ProcessEvents();

            DeltaTime = LoopClock.GetElapsedTime();
            float TickDeltaTime = DeltaTime.GetAsSeconds();
            Tick(TickDeltaTime);
            TickDeltaTimeSum += TickDeltaTime;

            DeltaTime = LoopClock.Restart();

            LoopClock.Restart();
        }
        TickLag = TickDeltaTimeSum - SecondsForTick;

        sf::Time UpdateDeltaTime = sf::seconds(TickDeltaTimeSum);
        ImGui::SFML::Update(Window, UpdateDeltaTime);

        DebugGUI();

        Render();

        FPSCounter++;
        ZtTime FPSElapsedTime = FPSClock.GetElapsedTime();
        float FPSElapsedTimeSeconds = FPSElapsedTime.GetAsSeconds();
        if (FPSElapsedTimeSeconds >= 1.f)
        {
            FPSClock.Restart();
            FPSCount = FPSCounter;
            FPSCounter = 0u;
        }
	}

    EndPlay();

    ImGui::SFML::Shutdown();
}

void ZtLoop::BeginPlay()
{

}

void ZtLoop::Tick(float DeltaTime)
{

}

void ZtLoop::DebugGUI()
{
    ImGui::Begin("Debug window");

    ImGui::BeginChild("ZtLoop", {}, true);

    ImGui::Text("ZtLoop");
    ImGui::Text("SecondsForTick: %f seconds", SecondsForTick);
    ImGui::Text("TickDeltaTimeSum: %f seconds", TickDeltaTimeSum);
    ImGui::Text("TickLag: %f seconds", TickLag);
    ImGui::Text("DeltaTime: %f seconds", DeltaTime.GetAsSeconds());
    ImGui::Text("FPS: %i", FPSCount);

    ImGui::EndChild();

    ImGui::End();
}

void ZtLoop::Render()
{
    Window.clear();
    ImGui::SFML::Render(Window);



    Window.display();
}

void ZtLoop::EndPlay()
{

}

void ZtLoop::CreateRenderWindow()
{
    Window.create(sf::VideoMode(800, 600), "Zinet");
}

void ZtLoop::ProcessEvents()
{
    sf::Event Event;
    while (Window.pollEvent(Event))
    {
        ImGui::SFML::ProcessEvent(Event);

        if (Event.type == sf::Event::Closed)
            Window.close();
    }
}
