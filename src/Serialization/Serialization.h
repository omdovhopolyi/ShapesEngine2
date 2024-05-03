#pragma once

#include "Utils/Types.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <tinyxml2/tinyxml2.h>
#include <string>
#include <vector>

namespace shen
{
    class Texture;
    class Shader;

    bool LoadBool(const std::string& id, const tinyxml2::XMLElement* element, bool defaultVal = false);
    int LoadInt(const std::string& id, const tinyxml2::XMLElement* element, int defaultVal = 0);
    float LoadFloat(const std::string& id, const tinyxml2::XMLElement* element, float defaultVal = 0.f);
    std::string LoadStr(const std::string& id, const tinyxml2::XMLElement* element, const std::string& defaultVal = {});

    sf::Vector2f LoadVec2(const std::string& id, const tinyxml2::XMLElement* element, sf::Vector2f defaultVal = sf::Vector2f());
    //glm::vec3 LoadVec3(const std::string& id, const tinyxml2::XMLElement* element, glm::vec3 defaultVal = glm::vec3(0.f));

    sf::Vector2f LoadVec2(const tinyxml2::XMLElement* element, sf::Vector2f defaultVal = sf::Vector2f());
    //glm::vec3 LoadVec3(const tinyxml2::XMLElement* element, glm::vec3 defaultVal = glm::vec3(0.f));
    
    sf::FloatRect LoadRect(const std::string& id, const tinyxml2::XMLElement* element, sf::FloatRect def = {});
    sf::FloatRect LoadRect(const tinyxml2::XMLElement* element);

    sf::Color LoadColor(const std::string& id, const tinyxml2::XMLElement* element, sf::Color defaultVal = sf::Color::Red);

    sf::Texture* LoadTexturePtr(const std::string& id, const tinyxml2::XMLElement* elemnt);
    std::vector<sf::FloatRect> LoadVectorRect(const std::string& id, const tinyxml2::XMLElement* element);

    //Shader* LoadShaderPtr(const std::string& id, const tinyxml2::XMLElement* element);

    std::vector<std::string> LoadVecStr(const std::string& id, const tinyxml2::XMLElement* element);
}
