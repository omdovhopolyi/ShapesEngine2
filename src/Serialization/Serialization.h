#pragma once

#include "Utils/Types.h"
#include "ECS/SystemsManager.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <tinyxml2/tinyxml2.h>
#include <string>
#include <vector>

namespace shen
{
    class Serialization
    {
    public:
        Serialization(SystemsManager* systems, tinyxml2::XMLElement* element);

        SystemsManager* GetSystems() const { return _systems; }

        bool LoadBool(const std::string& id, bool defaultVal = false);
        int LoadInt(const std::string& id, int defaultVal = 0);
        float LoadFloat(const std::string& id, float defaultVal = 0.f);
        std::string LoadStr(const std::string& id, const std::string& defaultVal = {});

        bool LoadBoolAttr(const std::string& id, bool defaultVal = false);
        int LoadIntAttr(const std::string& id, int defaultVal = 0);
        float LoadFloatAttr(const std::string& id, float defaultVal = 0.f);
        std::string LoadStrAttr(const std::string& id, const std::string& defaultVal = {});

        sf::Vector2f LoadVec2(const std::string& id, sf::Vector2f defaultVal = sf::Vector2f());
        sf::Vector2f LoadVec2(const tinyxml2::XMLElement* element, sf::Vector2f defaultVal = sf::Vector2f());
        
        sf::FloatRect LoadFloatRect(const std::string& id, sf::FloatRect def = {});
        static sf::FloatRect LoadFloatRect(const tinyxml2::XMLElement* element);

        sf::IntRect LoadIntRect(const std::string& id, sf::IntRect def = {});
        static sf::IntRect LoadIntRect(const tinyxml2::XMLElement* element);

        sf::Color LoadColor(const std::string& id, sf::Color defaultVal = sf::Color::Red);
        static sf::Color LoadColor(const tinyxml2::XMLElement* element);

        sf::Texture* LoadTexturePtr(const std::string& id);
        std::vector<sf::IntRect> LoadVectorRect(const std::string& id);

        std::vector<std::string> LoadVecStr(const std::string& id);

        static sf::Transform LoadTransform(const tinyxml2::XMLElement* element);

        void SaveBool(const std::string& id, bool val);
        void SaveInt(const std::string& id, int val);
        void SaveFloat(const std::string& id, float val);
        void SaveStr(const std::string& id, const std::string& val);

        void SaveBoolAttr(const std::string& id, bool val);
        void SaveIntAttr(const std::string& id, int val);
        void SaveFloatAttr(const std::string& id, float val);
        void SaveStrAttr(const std::string& id, const std::string& val);

        void SaveBoolAttr(tinyxml2::XMLElement* element, const std::string& id, bool val);
        void SaveIntAttr(tinyxml2::XMLElement* element, const std::string& id, int val);
        void SaveFloatAttr(tinyxml2::XMLElement* element, const std::string& id, float val);
        void SaveStrAttr(tinyxml2::XMLElement* element, const std::string& id, const std::string& val);

        void SaveVec2(const std::string& id, const sf::Vector2f& val);
        void SaveVec2Attr(const sf::Vector2f& val);
        void SaveVec2Attr(tinyxml2::XMLElement* element, const sf::Vector2f& val);

        void SaveFloatRect(const std::string& id, const sf::FloatRect& val);
        void SaveFloatRectAttr(const sf::FloatRect& val);
        void SaveFloatRectAttr(tinyxml2::XMLElement* element, const sf::FloatRect& val);

        void SaveIntRect(const std::string& id, const sf::IntRect& val);
        void SaveIntRectAttr(const sf::IntRect& val);
        void SaveIntRectAttr(tinyxml2::XMLElement* element, const sf::IntRect& val);

        void SaveColor(const std::string& id, const sf::Color& val);
        void SaveColorAttr(const sf::Color& val);
        void SaveColorAttr(tinyxml2::XMLElement* element, const sf::Color& val);

        void SaveTexturePtr(const std::string& id, const std::string& texId);
        void SaveVectorRect(const std::string& id, const std::vector<sf::IntRect>& vec);

        void SaveVecStr(const std::string& id, const std::vector<std::string>& vec);

    private:
        SystemsManager* _systems;
        tinyxml2::XMLElement* _element = nullptr;
    };
}
