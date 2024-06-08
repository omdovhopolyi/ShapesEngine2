#include "SfmlWindowSystem.h"

namespace shen
{
    void SfmlGameWindowSystem::Start()
    {
        _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Shapes engine");
    }

    void SfmlGameWindowSystem::Stop()
    {
        _window->close();
        _window = nullptr;
    }

    sf::Window* SfmlGameWindowSystem::GetWindow() const
    {
        return _window.get();
    }

    sf::RenderWindow* SfmlGameWindowSystem::GetRenderWindow() const
    {
        return _window.get();
    }
}
