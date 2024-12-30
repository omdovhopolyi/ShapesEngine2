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
        Serialization() = default;
        Serialization(const std::string& filename);
        Serialization(SystemsManager* systems, const std::string& filename);
        Serialization(SystemsManager* systems, tinyxml2::XMLElement* element);

        SystemsManager* GetSystems() const { return _systems; }

        void LoadDocument(const std::string& filename);
        void SetupElement(const std::string& id);

        bool IsValid() const;
        bool IsElementValid() const;

        Serialization GetElement(const std::string& id) const;

        bool GetBool(const std::string& id, bool defaultVal = false) const;
        int GetInt(const std::string& id, int defaultVal = 0) const;
        float GetFloat(const std::string& id, float defaultVal = 0.f) const;
        std::string GetStr(const std::string& id, const std::string& defaultVal = {}) const;
        sf::Vector2f GetVec2(const std::string& id, sf::Vector2f defaultVal = sf::Vector2f()) const;
        sf::Vector2i GetIntVec2(const std::string& id, sf::Vector2i defaultVal = sf::Vector2i()) const;
        sf::FloatRect GetFloatRect(const std::string& id, sf::FloatRect def = {}) const;
        sf::IntRect GetIntRect(const std::string& id, sf::IntRect def = {}) const;
        sf::IntRect GetIntRect(sf::IntRect def = {}) const;
        sf::Color GetColor(const std::string& id, sf::Color defaultVal = sf::Color::Red) const;
        sf::Texture* GetTexturePtr(const std::string& id = "texture") const;
        std::vector<sf::IntRect> GetVectorIntRect(const std::string& id) const;
        std::vector<std::string> GetVecStr(const std::string& id) const;
        sf::Transform GetTransform() const;
        void ForAllChildElements(const std::string& id, const std::string& elementId, const std::function<void(const Serialization&)>& func) const;
        void ForAllChildElements(const std::string& elementId, const std::function<void(const Serialization&)>& func) const;

        void SetBool(const std::string& id, bool val);
        void SetInt(const std::string& id, int val);
        void SetFloat(const std::string& id, float val);
        void SetStr(const std::string& id, const std::string& val);
        void SetVec2(const std::string& id, const sf::Vector2f& val);
        void SetFloatRect(const std::string& id, const sf::FloatRect& val);
        void SetIntRect(const std::string& id, const sf::IntRect& val);
        void SetColor(const std::string& id, const sf::Color& val);
        void SetTexturePtr(const std::string& id, const std::string& texId);
        void SetVectorIntRect(const std::string& id, const std::vector<sf::IntRect>& vec);
        void SetVecStr(const std::string& id, const std::vector<std::string>& vec);

    private:
        void SetVec2Attr(tinyxml2::XMLElement* element, const sf::Vector2f& val);
        void SetFloatRectAttr(tinyxml2::XMLElement* element, const sf::FloatRect& val);
        void SetIntRectAttr(tinyxml2::XMLElement* element, const sf::IntRect& val);
        void SetColorAttr(tinyxml2::XMLElement* element, const sf::Color& val);
        
    private:
        SystemsManager* _systems = nullptr;
        std::shared_ptr<tinyxml2::XMLDocument> _document;
        tinyxml2::XMLElement* _element = nullptr;
    };
}
