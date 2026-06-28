#include "SDLInputSystem.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>

#include <Messenger/Messenger.h>
#include <Messenger/Events/Common.h>

#include <ECS/SystemsManager.h>
#include <ECS/Systems/SDL/SDLWindowSystem.h>

#include <Logger/Logger.h>

#include <array>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(SDLInputSystem)

    void SDLInputSystem::Update()
    {
        const bool* sdlKeyboardState = SDL_GetKeyboardState(NULL);
        std::array<bool, SDL_SCANCODE_COUNT> keysState;
        for (int i = 0; i < SDL_SCANCODE_COUNT; i++) {
            keysState[i] = sdlKeyboardState[i];
        }

        float mousePosX = 0.f;
        float mousePosY = 0.f;
        SDL_MouseButtonFlags mouseState = SDL_GetMouseState(&mousePosX, &mousePosY);
        std::array<bool, 3> buttonsState;
        buttonsState[0] = mouseState | SDL_BUTTON_LEFT;
        buttonsState[1] = mouseState | SDL_BUTTON_RIGHT;
        buttonsState[2] = mouseState | SDL_BUTTON_MIDDLE;

        const bool ctrl = sdlKeyboardState[SDL_GetScancodeFromKey(SDLK_LCTRL, SDL_KMOD_NONE)] || sdlKeyboardState[SDL_GetScancodeFromKey(SDLK_RCTRL, SDL_KMOD_NONE)];
        const bool alt = sdlKeyboardState[SDL_GetScancodeFromKey(SDLK_LALT, SDL_KMOD_NONE)] || sdlKeyboardState[SDL_GetScancodeFromKey(SDLK_RALT, SDL_KMOD_NONE)];
        const bool shift = sdlKeyboardState[SDL_GetScancodeFromKey(SDLK_LSHIFT, SDL_KMOD_NONE)] || sdlKeyboardState[SDL_GetScancodeFromKey(SDLK_RSHIFT, SDL_KMOD_NONE)];

		SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT: {
                Messenger::Instance().Broadcast<Quit>();
                break;
            }
            case SDL_EVENT_KEY_DOWN: {
                Messenger::Instance().Broadcast<KeyEvent>(
                    InputEventType::Down,
                    static_cast<int>(event.key.key),
                    (event.key.mod == SDL_KMOD_LALT || event.key.mod == SDL_KMOD_RALT),
                    (event.key.mod == SDL_KMOD_LSHIFT || event.key.mod == SDL_KMOD_RSHIFT),
                    (event.key.mod == SDL_KMOD_LCTRL || event.key.mod == SDL_KMOD_RCTRL)
                );

                keysState[event.key.scancode] = false;

                break;
            }
            case SDL_EVENT_KEY_UP: {
                Messenger::Instance().Broadcast<KeyEvent>(
                    InputEventType::Up,
                    static_cast<int>(event.key.key),
                    (event.key.mod == SDL_KMOD_LALT || event.key.mod == SDL_KMOD_RALT),
                    (event.key.mod == SDL_KMOD_LSHIFT || event.key.mod == SDL_KMOD_RSHIFT),
                    (event.key.mod == SDL_KMOD_LCTRL || event.key.mod == SDL_KMOD_RCTRL)
                );

                keysState[event.key.scancode] = false;

                break;
            }
            case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                Messenger::Instance().Broadcast<MouseButtonEvent>(
                    InputEventType::Down,
                    static_cast<MouseButton>(event.button.button),
                    static_cast<int>(event.button.x),
                    static_cast<int>(event.button.y),
                    alt,
                    shift,
                    ctrl
                );

                if (event.button.button < 3) {
                    buttonsState[event.button.button] = false;
                }

                break;
            }
            case SDL_EVENT_MOUSE_BUTTON_UP: {
                Messenger::Instance().Broadcast<MouseButtonEvent>(
                    InputEventType::Up,
                    static_cast<MouseButton>(event.button.button),
                    static_cast<int>(event.button.x),
                    static_cast<int>(event.button.y),
                    alt,
                    shift,
                    ctrl
                );

                if (event.button.button < 3) {
                    buttonsState[event.button.button] = false;
                }

                break;
            }
            case SDL_EVENT_MOUSE_MOTION: {
                std::array<bool, 3> buttons;
                buttons[0] = event.motion.state | SDL_BUTTON_LEFT;
                buttons[1] = event.motion.state | SDL_BUTTON_RIGHT;
                buttons[2] = event.motion.state | SDL_BUTTON_MIDDLE;

                MouseButton button = MouseButton::None;
                for (size_t i = 0; i < buttons.size(); i++) {
                    if (buttons[i] == true) {
                        button = static_cast<MouseButton>(i);
                        break;
                    }
                }

                Messenger::Instance().Broadcast<MouseMoveEvent>(
                    button,
                    static_cast<int>(event.motion.x),
                    static_cast<int>(event.motion.y),
                    static_cast<int>(event.motion.xrel),
                    static_cast<int>(event.motion.yrel),
                    alt,
                    shift,
                    ctrl
                );
                break;
            }
            case SDL_EVENT_MOUSE_WHEEL: {
                Messenger::Instance().Broadcast<MouseWheelEvent>(
                    static_cast<int>(event.wheel.mouse_x),
                    static_cast<int>(event.wheel.mouse_y),
                    event.wheel.y,
                    alt,
                    shift,
                    ctrl
                );
                break;
            }
            case SDL_EVENT_WINDOW_FOCUS_GAINED: {
                Messenger::Instance().Broadcast<GainedFocus>();
                break;
            }
            case SDL_EVENT_WINDOW_FOCUS_LOST: {
                Messenger::Instance().Broadcast<LostFocus>();
                break;
            }
            default: {
                break;
            }
            }
        }

        for (int i = 0; i < keysState.size(); i++) {
            if (keysState[i] == true) {
                const SDL_Keycode keycode = SDL_SCANCODE_TO_KEYCODE(static_cast<unsigned int>(keysState[i]));
                Messenger::Instance().Broadcast<KeyEvent>(
                    InputEventType::Hold,
                    static_cast<int>(keycode),
                    alt,
                    shift,
                    ctrl
                );
            }
        }

        for (int i = 0; i < buttonsState.size(); i++) {
            if (buttonsState[i] == true) {
                Messenger::Instance().Broadcast<MouseButtonEvent>(
                    InputEventType::Hold,
                    static_cast<MouseButton>(buttonsState[i]),
                    static_cast<int>(mousePosX),
                    static_cast<int>(mousePosY),
                    alt,
                    shift,
                    ctrl
                );
            }
        }
    }

    //bool SDLInputSystem::IsKeyPressed(sf::Keyboard::Key key) const;
    //bool SDLInputSystem::IsMouseButtonPressed(sf::Mouse::Button button) const;
    
    std::string SDLInputSystem::GetCharByKey(int key) const
    {
        return {};
    }

    int SDLInputSystem::GetKeyByChar(const std::string& charKeyStr, bool silent) const
    {
        auto it = _charKeyMap.find(charKeyStr);
        if (it != _charKeyMap.end()) {
            return it->second;
        }
        return 0;
    }

    void SDLInputSystem::GenerateCharKeyMap()
    {
        //CharKeyMap[{ 'A' }] = SDLK_A;
        //CharKeyMap[{ 'B' }] = SDLK_B;
        //CharKeyMap[{ 'C' }] = SDLK_C;
        //CharKeyMap[{ 'D' }] = SDLK_D;
        //CharKeyMap[{ 'E' }] = SDLK_E;
        //CharKeyMap[{ 'F' }] = SDLK_F;
        //CharKeyMap[{ 'G' }] = SDLK_G;
        //CharKeyMap[{ 'H' }] = SDLK_H;
        //CharKeyMap[{ 'I' }] = SDLK_I;
        //CharKeyMap[{ 'J' }] = SDLK_J;
        //CharKeyMap[{ 'K' }] = SDLK_K;
        //CharKeyMap[{ 'L' }] = SDLK_L;
        //CharKeyMap[{ 'M' }] = SDLK_M;
        //CharKeyMap[{ 'N' }] = SDLK_N;
        //CharKeyMap[{ 'O' }] = SDLK_O;
        //CharKeyMap[{ 'P' }] = SDLK_P;
        //CharKeyMap[{ 'Q' }] = SDLK_Q;
        //CharKeyMap[{ 'R' }] = SDLK_R;
        //CharKeyMap[{ 'S' }] = SDLK_S;
        //CharKeyMap[{ 'T' }] = SDLK_T;
        //CharKeyMap[{ 'U' }] = SDLK_U;
        //CharKeyMap[{ 'V' }] = SDLK_V;
        //CharKeyMap[{ 'W' }] = SDLK_W;
        //CharKeyMap[{ 'X' }] = SDLK_X;
        //CharKeyMap[{ 'Y' }] = SDLK_Y;
        //CharKeyMap[{ 'Z' }] = SDLK_Z;

        _charKeyMap[{ 'a' }] = SDLK_A;
        _charKeyMap[{ 'b' }] = SDLK_B;
        _charKeyMap[{ 'c' }] = SDLK_C;
        _charKeyMap[{ 'd' }] = SDLK_D;
        _charKeyMap[{ 'e' }] = SDLK_E;
        _charKeyMap[{ 'f' }] = SDLK_F;
        _charKeyMap[{ 'g' }] = SDLK_G;
        _charKeyMap[{ 'h' }] = SDLK_H;
        _charKeyMap[{ 'i' }] = SDLK_I;
        _charKeyMap[{ 'j' }] = SDLK_J;
        _charKeyMap[{ 'k' }] = SDLK_K;
        _charKeyMap[{ 'l' }] = SDLK_L;
        _charKeyMap[{ 'm' }] = SDLK_M;
        _charKeyMap[{ 'n' }] = SDLK_N;
        _charKeyMap[{ 'o' }] = SDLK_O;
        _charKeyMap[{ 'p' }] = SDLK_P;
        _charKeyMap[{ 'q' }] = SDLK_Q;
        _charKeyMap[{ 'r' }] = SDLK_R;
        _charKeyMap[{ 's' }] = SDLK_S;
        _charKeyMap[{ 't' }] = SDLK_T;
        _charKeyMap[{ 'u' }] = SDLK_U;
        _charKeyMap[{ 'v' }] = SDLK_V;
        _charKeyMap[{ 'w' }] = SDLK_W;
        _charKeyMap[{ 'x' }] = SDLK_X;
        _charKeyMap[{ 'y' }] = SDLK_Y;
        _charKeyMap[{ 'z' }] = SDLK_Z;

        _charKeyMap[{ '0' }] = SDLK_0;
        _charKeyMap[{ '1' }] = SDLK_1;
        _charKeyMap[{ '2' }] = SDLK_2;
        _charKeyMap[{ '3' }] = SDLK_3;
        _charKeyMap[{ '4' }] = SDLK_4;
        _charKeyMap[{ '5' }] = SDLK_5;
        _charKeyMap[{ '6' }] = SDLK_6;
        _charKeyMap[{ '7' }] = SDLK_7;
        _charKeyMap[{ '8' }] = SDLK_8;
        _charKeyMap[{ '9' }] = SDLK_9;

        _charKeyMap["Esc"] = SDLK_ESCAPE;
        _charKeyMap[{ ' ' }] = SDLK_SPACE;
        _charKeyMap[{ '\t' }] = SDLK_TAB;
        _charKeyMap[{ '\n' }] = SDLK_RETURN;
        _charKeyMap[{ ',' }] = SDLK_COMMA;
        _charKeyMap[{ '.' }] = SDLK_PERIOD;
        _charKeyMap[{ '/' }] = SDLK_SLASH;
        _charKeyMap[{ '\\' }] = SDLK_BACKSLASH;
        _charKeyMap[{ '\'' }] = SDLK_APOSTROPHE;
        _charKeyMap[{ ';' }] = SDLK_SEMICOLON;
        _charKeyMap[{ '[' }] = SDLK_LEFTBRACKET;
        _charKeyMap[{ ']' }] = SDLK_RIGHTBRACKET;
        //CharKeyMap[{ '-' }] = sf::Keyboard::Dash;
        _charKeyMap[{ '=' }] = SDLK_EQUALS;
        _charKeyMap[{ '`' }] = SDLK_TILDE;
        _charKeyMap["Left"] = SDLK_LEFT;
        _charKeyMap["Right"] = SDLK_RIGHT;
        _charKeyMap["Up"] = SDLK_UP;
        _charKeyMap["Down"] = SDLK_DOWN;

        _charKeyMap["F1"] = SDLK_F1;
        _charKeyMap["F2"] = SDLK_F2;
        _charKeyMap["F3"] = SDLK_F3;
        _charKeyMap["F4"] = SDLK_F4;
        _charKeyMap["F5"] = SDLK_F5;
        _charKeyMap["F6"] = SDLK_F6;
        _charKeyMap["F7"] = SDLK_F7;
        _charKeyMap["F8"] = SDLK_F8;
        _charKeyMap["F9"] = SDLK_F9;
        _charKeyMap["F10"] = SDLK_F10;
        _charKeyMap["F11"] = SDLK_F11;
        _charKeyMap["F12"] = SDLK_F12;
    }

    void SDLInputSystem::GenerateKeyCharMap()
    {
        _keyCharMap.clear();
        for (const auto& [str, key] : _charKeyMap) {
            _keyCharMap[key] = str;
        }
    }
}
