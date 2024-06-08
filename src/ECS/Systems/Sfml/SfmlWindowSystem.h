#pragma once

#include "ECS/Systems/BaseSystems/System.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

namespace shen
{
    class SfmlGameWindowSystem
        : public System
    {
    public:
        void Start() override;
        void Stop() override;

        sf::Window* GetWindow() const;
        sf::RenderWindow* GetRenderWindow() const;

    private:
        std::unique_ptr<sf::RenderWindow> _window;
    };
}
