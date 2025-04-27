#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <unordered_map>

namespace shen
{
    class SfmlInputSystem
        : public UpdateSystem
    {
        SYSTEMS_FACTORY(SfmlInputSystem)

    public:
        void Start() override;
        void Update() override;

        bool IsKeyPressed(sf::Keyboard::Key key) const;
        bool IsMouseButtonPressed(sf::Mouse::Button button) const;

        std::string GetCharByKey(sf::Keyboard::Key key) const;
        sf::Keyboard::Key GetKeyByChar(const std::string& charKeyStr, bool silent = false) const;

    private:
        void GenerateCharKeyMap();
        void GenerateKeyCharMap();

    private:
        int _lastMouseXPos = -1;
        int _lastMouseYPos = -1;
        std::unordered_map<std::string, sf::Keyboard::Key> _charKeyMap;
        std::unordered_map<sf::Keyboard::Key, std::string> _keyCharMap;
    };
}
