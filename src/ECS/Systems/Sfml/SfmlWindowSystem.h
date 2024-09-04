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
        SYSTEMS_FACTORY(SfmlGameWindowSystem)

    public:
        void Start() override;
        void Stop() override;

        sf::RenderWindow* GetWindow() const;

    private:
        std::unique_ptr<sf::RenderWindow> _window;
        sf::Vector2i _size;
        std::string _name;
    };
}
