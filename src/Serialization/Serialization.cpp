#include "Serialization.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlTexturesCollection.h"

namespace shen
{
    Serialization::Serialization(SystemsManager* systems, tinyxml2::XMLElement* element)
        : _systems(systems)
        , _element(element)
    {
    }

    bool Serialization::LoadBool(const std::string& id, bool defaultVal/* = false*/)
    {
        if (const auto childElement = _element->FirstChildElement(id.c_str()))
        {
            if (const auto attrib = childElement->FindAttribute("val"))
            {
                return attrib->BoolValue();
            }
        }

        return defaultVal;
    }

    int Serialization::LoadInt(const std::string& id, int defaultVal/* = 0*/)
    {
        if (const auto childElement = _element->FirstChildElement(id.c_str()))
        {
            if (const auto attrib = childElement->FindAttribute("val"))
            {
                return attrib->IntValue();
            }
        }

        return defaultVal;
    }

    float Serialization::LoadFloat(const std::string& id, float defaultVal/* = 0.f*/)
    {
        if (const auto childElement = _element->FirstChildElement(id.c_str()))
        {
            if (const auto attrib = childElement->FindAttribute("val"))
            {
                return attrib->FloatValue();
            }
        }

        return defaultVal;
    }

    std::string Serialization::LoadStr(const std::string& id, const std::string& defaultVal/* = {}*/)
    {
        if (const auto childElement = _element->FirstChildElement(id.c_str()))
        {
            if (const auto attrib = childElement->FindAttribute("val"))
            {
                return attrib->Value();
            }
        }

        return defaultVal;
    }

    sf::Vector2f Serialization::LoadVec2(const std::string& id, sf::Vector2f defaultVal)
    {
        if (const auto childElement = _element->FirstChildElement(id.c_str()))
        {
            return LoadVec2(childElement, defaultVal);
        }

        return defaultVal;
    }

    sf::Vector2f Serialization::LoadVec2(const tinyxml2::XMLElement* element, sf::Vector2f defaultVal)
    {
        sf::Vector2f result;

        if (const auto xAttrib = element->FindAttribute("x"))
        {
            result.x = xAttrib->FloatValue();
        }

        if (const auto yAttrib = element->FindAttribute("y"))
        {
            result.y = yAttrib->FloatValue();
        }

        return result;
    }

    sf::FloatRect Serialization::LoadRect(const std::string& id, sf::FloatRect def/* = {}*/)
    {
        if (const auto childElement = _element->FirstChildElement(id.c_str()))
        {
            return LoadRect(childElement);
        }

        return def;
    }

    sf::FloatRect Serialization::LoadRect(const tinyxml2::XMLElement* element)
    {
        sf::FloatRect rect;

        if (const auto attrib = element->FindAttribute("x"))
        {
            rect.left = attrib->FloatValue();
        }

        if (const auto attrib = element->FindAttribute("y"))
        {
            rect.top = attrib->FloatValue();
        }

        if (const auto attrib = element->FindAttribute("w"))
        {
            rect.width = attrib->FloatValue();
        }

        if (const auto attrib = element->FindAttribute("h"))
        {
            rect.height = attrib->FloatValue();
        }

        return rect;
    }

    sf::Color Serialization::LoadColor(const std::string& id, sf::Color defaultVal)
    {
        if (const auto childElement = _element->FirstChildElement(id.c_str()))
        {
            sf::Color result;

            if (const auto xAttrib = childElement->FindAttribute("r"))
            {
                result.r = xAttrib->IntValue();
            }

            if (const auto yAttrib = childElement->FindAttribute("g"))
            {
                result.g = yAttrib->IntValue();
            }

            if (const auto zAttrib = childElement->FindAttribute("b"))
            {
                result.b = zAttrib->IntValue();
            }

            if (const auto zAttrib = childElement->FindAttribute("a"))
            {
                result.a = zAttrib->IntValue();
            }

            return result;
        }

        return defaultVal;
    }

    sf::Texture* Serialization::LoadTexturePtr(const std::string& id)
    {
        if (const auto childElement = _element->FirstChildElement(id.c_str()))
        {
            if (const auto attrib = childElement->FindAttribute("val"))
            {
                const auto textureId = attrib->Value();

                if (auto textures = _systems->GetSystem<SfmlTexturesCollection>())
                {
                    return textures->GetTexture(textureId);
                }
            }
        }

        return nullptr;
    }

    std::vector<sf::FloatRect> Serialization::LoadVectorRect(const std::string& id)
    {
        std::vector<sf::FloatRect> result;

        if (const auto childElement = _element->FirstChildElement(id.c_str()))
        {
            auto rectElement = childElement->FirstChildElement("rect");
            while (rectElement)
            {
                result.push_back(LoadRect(rectElement));
                rectElement = rectElement->NextSiblingElement();
            }
        }

        return result;
    }

    std::vector<std::string> Serialization::LoadVecStr(const std::string& id)
    {
        std::vector<std::string> result;

        if (const auto childElement = _element->FirstChildElement(id.c_str()))
        {
            auto arrayElement = childElement->FirstChildElement("item");
            while (arrayElement)
            {
                if (const auto attrib = childElement->FindAttribute("val"))
                {
                    result.push_back(attrib->Value());
                }

                arrayElement = arrayElement->NextSiblingElement();
            }
        }

        return result;
    }
}
