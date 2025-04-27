#pragma once

#include "ECS/Systems/BaseSystems/System.h"
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
        unsigned int GetWindowFlags() const;

        sf::Vector2i GetSize();

    private:
        void Load() override;

        void CreateSFMLWindow(unsigned int flags);

    private:
        std::unique_ptr<sf::RenderWindow> _window;
        sf::Vector2i _size;
        std::string _name;

        bool _titlebar = true;
        bool _resize = true;
        bool _close = true;
        bool _fullscreen = false;
    };
}
