#pragma once

#include "ECS/Systems/BaseSystems/System.h"

#include <SFML/Window.hpp>

#include <memory>

namespace shen
{
    class SfmlGameWindowSystem
        : public System
    {
    public:
        void Start() override;
        void Stop() override;

    private:
        std::unique_ptr<sf::Window> _window;
    };
}
