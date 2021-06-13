#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class ZtLoop
{

public:

    void Start();

protected:

    void BeginPlay();

    void ProcessEvents();

    void Tick(float ElapsedTime);

    void Render();

    void EndPlay();

    sf::RenderWindow Window;

    void CreateRenderWindow();

};