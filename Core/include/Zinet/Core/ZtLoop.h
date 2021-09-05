#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtClock.h"
#include "Zinet/Core/ZtWorld.h"
#include "Zinet/Core/ZtRenderer.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class ZINET_CORE_API ZtLoop
{

public:

    void Start();

protected:

    void LoopStep();

    void BeginPlay();

    void ProcessEvents();

    void Tick(float DeltaTime);

#ifdef ZINET_DEBUG_UI
    void DebugUI() const;
    void LoopDebugUI() const;
#endif

    void Render();

    void EndPlay();

    sf::RenderWindow Window;

    void CreateRenderWindow();

    ZtClock LoopClock;
    ZtTime DeltaTime;
    float SecondsForTick = ZtTime::FromMilliseconds(16).GetAsSeconds();

    void CalculateFPS();

    ZtClock FPSClock;
    int FPSCounter = 0;
    int FPSCount = 0;

    ZtRenderer Renderer;
    ZtWorld World;
};