#pragma once

#include "ECS/Systems/System.h"
#include <SDL.h>
#include <set>
#include <functional>

namespace shen
{
    class SDLInputSystem
        : public System
    {
    public:
        void Update() override;

    private:
        std::set<SDL_Keycode> _holdKeys;
        std::set<std::uint8_t> _holdMouseButtons;
        std::vector<std::function<void()>> _scheduledFuncs;
    };
}
