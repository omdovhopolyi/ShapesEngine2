#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"
#include <SFML/Window/Keyboard.hpp>
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

        char GetCharByKey(sf::Keyboard::Key key) const;
        sf::Keyboard::Key GetKeyByChar(char charKey) const;

    private:
        void GenerateCharKeyMap();
        void GenerateKeyCharMap();

    private:
        int _lastMouseXPos = -1;
        int _lastMouseYPos = -1;
        std::unordered_map<char, sf::Keyboard::Key> _charKeyMap;
        std::unordered_map<sf::Keyboard::Key, char> _keyCharMap;
    };
}
