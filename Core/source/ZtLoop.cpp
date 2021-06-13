#include "..\include\Zinet\Core\ZtLoop.h"

void ZtLoop::Start()
{
	BeginPlay();

    CreateRenderWindow();

    while (Window.isOpen())
	{
        ProcessEvents();
		Tick(1.f);
        Render();
	}

    EndPlay();
}

void ZtLoop::BeginPlay()
{
}

void ZtLoop::Tick(float ElapsedTime)
{
    
}

void ZtLoop::Render()
{
    Window.clear();

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
        if (Event.type == sf::Event::Closed)
            Window.close();
    }
}
