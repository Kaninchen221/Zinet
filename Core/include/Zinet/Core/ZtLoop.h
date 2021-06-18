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

    float SecondsForTick = ZtTime(0.016f).GetAsSeconds();

    void DebugGUI();

    void Render();

    void EndPlay();

    sf::RenderWindow Window;

    void CreateRenderWindow();

};