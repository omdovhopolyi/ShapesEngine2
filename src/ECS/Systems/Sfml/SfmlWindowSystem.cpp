#include "SfmlWindowSystem.h"



namespace shen
{
    void SfmlGameWindowSystem::Start()
    {
        _window = std::make_unique<sf::Window>(sf::VideoMode(800, 600), "Shapes engine");
    }

    void SfmlGameWindowSystem::Stop()
    {
        _window->close();
        _window = nullptr;
    }
}
