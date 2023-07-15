#pragma once

#include "ECS/Systems/System.h"
#include <SDL.h>
#include <set>

namespace shen
{
    class SDLInputSystem
        : public System
    {
    public:
        void Update() override;

    private:
        std::set<SDL_Keycode> _holdKeys;
    };
}
