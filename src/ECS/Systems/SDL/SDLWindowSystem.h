#pragma once

#include <ECS/Systems/BaseSystems/System.h>
#include <SDL3/SDL.h>

namespace shen
{
    class SDLWindowSystem
        : public System
    {
        SYSTEMS_FACTORY(SDLWindowSystem)

    public:
        void Start() override;
        void Stop() override;

        SDL_Window* GetWindow() const;
        unsigned int GetWindowFlags() const;

        //sf::Vector2i GetSize();

    private:
        void Load() override;

        void CreateSDLWindow();

    private:
        SDL_Window* _window = nullptr;
        //sf::Vector2i _size;
        std::string _name;

        bool _titlebar = true;
        bool _resize = true;
        bool _close = true;
        bool _fullscreen = false;
    };
}
