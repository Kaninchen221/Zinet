#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtClock.h"
#include "Zinet/Core/ZtWorld.h"

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
    void LoopDebugGUI();

    void Render();

    void EndPlay();

    sf::RenderWindow Window;

    void CreateRenderWindow();

    ZtTime DeltaTime;
    float SecondsForTick = ZtTime::FromMilliseconds(16).GetAsSeconds();
    float TickDeltaTimeSum = 0.f;
    float TickLag = 0.f;

    void CalculateFPS();

    ZtClock FPSClock;
    size_t FPSCounter = 0u;
    size_t FPSCount = 0u;

    ZtWorld World;
};