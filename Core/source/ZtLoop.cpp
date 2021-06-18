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

    ZtClock Clock;
    Clock.Start();

    while (Window.isOpen())
    {
        ProcessEvents();

        ZtTime DeltaTime = Clock.GetElapsedTime();

        float TickDeltaTime = DeltaTime.GetAsSeconds();
        sf::Time UpdateDeltaTime = sf::seconds(TickDeltaTime);
        ImGui::SFML::Update(Window, UpdateDeltaTime);
        Tick(TickDeltaTime);

        /// Show ImGui demo window
        //ImGui::ShowDemoWindow();

        DebugGUI();

        Render();
        Clock.Restart();
	}

    EndPlay();

    ImGui::SFML::Shutdown();
}

void ZtLoop::BeginPlay()
{

}

void ZtLoop::Tick(float DeltaTime)
{
    //std::cout << "DeltaTime: " << DeltaTime << '\n';
}

void ZtLoop::DebugGUI()
{
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
