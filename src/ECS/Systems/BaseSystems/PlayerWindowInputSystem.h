#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"
#include <unordered_map>

namespace shen
{
    class PlayerWindowInputSystem
        : public UpdateSystem
    {
    public:
        void Start() override;

        //bool IsKeyPressed(sf::Keyboard::Key key) const;
        //bool IsMouseButtonPressed(sf::Mouse::Button button) const;

        virtual std::string GetCharByKey(int key) const { return {}; }
        virtual int GetKeyByChar(const std::string& charKeyStr, bool silent = false) const { return -1; }

    protected:
        virtual void GenerateCharKeyMap() {}
        virtual void GenerateKeyCharMap() {}

    protected:
        std::unordered_map<std::string, uint32_t> _charKeyMap;
        std::unordered_map<uint32_t, std::string> _keyCharMap;
    };
}
