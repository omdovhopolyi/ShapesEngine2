#pragma once

#include "Utils/Types.h"
#include "ECS/SystemsManager.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <tinyxml2/tinyxml2.h>
#include <string>
#include <vector>

namespace shen
{
    class Serialization
    {
    public:
        Serialization(SystemsManager* systems, tinyxml2::XMLElement* element);

        bool LoadBool(const std::string& id, bool defaultVal = false);
        int LoadInt(const std::string& id, int defaultVal = 0);
        float LoadFloat(const std::string& id, float defaultVal = 0.f);
        std::string LoadStr(const std::string& id, const std::string& defaultVal = {});

        sf::Vector2f LoadVec2(const std::string& id, sf::Vector2f defaultVal = sf::Vector2f());
        sf::Vector2f LoadVec2(const tinyxml2::XMLElement* element, sf::Vector2f defaultVal = sf::Vector2f());
        
        sf::FloatRect LoadRect(const std::string& id, sf::FloatRect def = {});
        sf::FloatRect LoadRect(const tinyxml2::XMLElement* element);

        sf::Color LoadColor(const std::string& id, sf::Color defaultVal = sf::Color::Red);

        sf::Texture* LoadTexturePtr(const std::string& id);
        std::vector<sf::FloatRect> LoadVectorRect(const std::string& id);

        std::vector<std::string> LoadVecStr(const std::string& id);

    private:
        SystemsManager* _systems;
        tinyxml2::XMLElement* _element = nullptr;
    };
}
