#pragma once

#include <ECS/Systems/BaseSystems/PlayerWindowInputSystem.h>
#include <unordered_map>

namespace shen
{
    class SDLInputSystem final
        : public PlayerWindowInputSystem
    {
        SYSTEMS_FACTORY(SDLInputSystem)

    public:
        void Update() override;

        //bool IsKeyPressed(sf::Keyboard::Key key) const;
        //bool IsMouseButtonPressed(sf::Mouse::Button button) const;
        
        std::string GetCharByKey(int key) const override;
        int GetKeyByChar(const std::string& charKeyStr, bool silent = false) const override;

    private:
        void GenerateCharKeyMap() override;
        void GenerateKeyCharMap() override;
    };
}
