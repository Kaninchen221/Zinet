#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtClock.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class ZINET_CORE_API ZtLoop
{

public:

    void Start();

protected:

    void BeginPlay();

    void ProcessEvents();

    void Tick(float DeltaTime);

    void DebugGUI();

    void Render();

    void EndPlay();

    sf::RenderWindow Window;

    void CreateRenderWindow();

    ZtTime DeltaTime;
    float SecondsForTick = ZtTime(16666666).GetAsSeconds();
    float TickDeltaTimeSum = 0.f;
    float TickLag = 0.f;

    size_t FPSCounter = 0u;
    size_t FPSCount = 0u;
    ZtClock FPSClock;
};