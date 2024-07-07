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

    bool Serialization::LoadBoolAttr(const std::string& id, bool defaultVal)
    {
        if (const auto attrib = _element->FindAttribute(id.c_str()))
        {
            return attrib->BoolValue();
        }
        return defaultVal;
    }

    int Serialization::LoadIntAttr(const std::string& id, int defaultVal)
    {
        if (const auto attrib = _element->FindAttribute(id.c_str()))
        {
            return attrib->IntValue();
        }
        return defaultVal;
    }

    float Serialization::LoadFloatAttr(const std::string& id, float defaultVal)
    {
        if (const auto attrib = _element->FindAttribute(id.c_str()))
        {
            return attrib->FloatValue();
        }
        return defaultVal;
    }

    std::string Serialization::LoadStrAttr(const std::string& id, const std::string& defaultVal)
    {
        if (const auto attrib = _element->FindAttribute(id.c_str()))
        {
            return attrib->Value();
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

    sf::FloatRect Serialization::LoadFloatRect(const std::string& id, sf::FloatRect def/* = {}*/)
    {
        if (const auto childElement = _element->FirstChildElement(id.c_str()))
        {
            return LoadFloatRect(childElement);
        }

        return def;
    }

    sf::FloatRect Serialization::LoadFloatRect(const tinyxml2::XMLElement* element)
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

    sf::IntRect Serialization::LoadIntRect(const std::string& id, sf::IntRect def/* = {}*/)
    {
        if (const auto childElement = _element->FirstChildElement(id.c_str()))
        {
            return LoadIntRect(childElement);
        }

        return def;
    }

    sf::IntRect Serialization::LoadIntRect(const tinyxml2::XMLElement* element)
    {
        sf::IntRect rect;

        if (const auto attrib = element->FindAttribute("x"))
        {
            rect.left = attrib->IntValue();
        }

        if (const auto attrib = element->FindAttribute("y"))
        {
            rect.top = attrib->IntValue();
        }

        if (const auto attrib = element->FindAttribute("w"))
        {
            rect.width = attrib->IntValue();
        }

        if (const auto attrib = element->FindAttribute("h"))
        {
            rect.height = attrib->IntValue();
        }

        return rect;
    }

    sf::Color Serialization::LoadColor(const std::string& id, sf::Color defaultVal)
    {
        if (const auto childElement = _element->FirstChildElement(id.c_str()))
        {
            return LoadColor(childElement);
        }

        return defaultVal;
    }

    sf::Color Serialization::LoadColor(const tinyxml2::XMLElement* element)
    {
        sf::Color result;

        if (const auto rAttrib = element->FindAttribute("r"))
        {
            result.r = rAttrib->IntValue();
        }

        if (const auto gAttrib = element->FindAttribute("g"))
        {
            result.g = gAttrib->IntValue();
        }

        if (const auto bAttrib = element->FindAttribute("b"))
        {
            result.b = bAttrib->IntValue();
        }

        if (const auto aAttrib = element->FindAttribute("a"))
        {
            result.a = aAttrib->IntValue();
        }

        return result;
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

    std::vector<sf::IntRect> Serialization::LoadVectorRect(const std::string& id)
    {
        std::vector<sf::IntRect> result;

        if (const auto childElement = _element->FirstChildElement(id.c_str()))
        {
            auto rectElement = childElement->FirstChildElement("rect");
            while (rectElement)
            {
                result.push_back(LoadIntRect(rectElement));
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

    sf::Transform Serialization::LoadTransform(const tinyxml2::XMLElement* element)
    {
        sf::Transform transform;

        if (const auto posElement = element->FirstChildElement("position"))
        {
            float xPos = 0.f;
            float yPos = 0.f;

            if (const auto xPosAttr = posElement->FindAttribute("x"))
            {
                xPos = xPosAttr->FloatValue();
            }
            if (const auto yPosAttr = posElement->FindAttribute("y"))
            {
                yPos = yPosAttr->FloatValue();
            }

            transform.translate({ xPos, yPos });
        }

        if (const auto rotationElement = element->FirstChildElement("rotation"))
        {
            if (const auto angleAttr = rotationElement->FindAttribute("angle"))
            {
                const float angle = angleAttr->FloatValue();
                transform.rotate(angle);
            }
        }

        if (auto scaleElement = element->FirstChildElement("scale"))
        {
            float xScale = 0.f;
            float yScale = 0.f;

            if (const auto xScaleAttr = scaleElement->FindAttribute("x"))
            {
                xScale = xScaleAttr->FloatValue();
            }
            if (const auto yScaleAttr = scaleElement->FindAttribute("y"))
            {
                yScale = yScaleAttr->FloatValue();
            }

            transform.scale({ xScale, yScale });
        }

        return transform;
    }

    void Serialization::SaveBool(const std::string& id, bool val)
    {
        if (auto childElement = _element->InsertNewChildElement(id.c_str()))
        {
            childElement->SetAttribute("val", val);
        }
    }

    void Serialization::SaveInt(const std::string& id, int val)
    {
        if (auto childElement = _element->InsertNewChildElement(id.c_str()))
        {
            childElement->SetAttribute("val", val);
        }
    }

    void Serialization::SaveFloat(const std::string& id, float val)
    {
        if (auto childElement = _element->InsertNewChildElement(id.c_str()))
        {
            childElement->SetAttribute("val", val);
        }
    }

    void Serialization::SaveStr(const std::string& id, const std::string& val)
    {
        if (auto childElement = _element->InsertNewChildElement(id.c_str()))
        {
            childElement->SetAttribute("val", val.c_str());
        }
    }

    void Serialization::SaveBoolAttr(const std::string& id, bool val)
    {
        SaveBoolAttr(_element, id, val);
    }

    void Serialization::SaveIntAttr(const std::string& id, int val)
    {
        SaveIntAttr(_element, id, val);
    }

    void Serialization::SaveFloatAttr(const std::string& id, float val)
    {
        SaveFloatAttr(_element, id, val);
    }

    void Serialization::SaveStrAttr(const std::string& id, const std::string& val)
    {
        SaveStrAttr(_element, id, val);
    }

    void Serialization::SaveBoolAttr(tinyxml2::XMLElement* element, const std::string& id, bool val)
    {
        if (element)
        {
            element->SetAttribute(id.c_str(), val);
        }
    }

    void Serialization::SaveIntAttr(tinyxml2::XMLElement* element, const std::string& id, int val)
    {
        if (element)
        {
            element->SetAttribute(id.c_str(), val);
        }
    }

    void Serialization::SaveFloatAttr(tinyxml2::XMLElement* element, const std::string& id, float val)
    {
        if (element)
        {
            element->SetAttribute(id.c_str(), val);
        }
    }

    void Serialization::SaveStrAttr(tinyxml2::XMLElement* element, const std::string& id, const std::string& val)
    {
        if (element)
        {
            element->SetAttribute(id.c_str(), val.c_str());
        }
    }

    void Serialization::SaveVec2(const std::string& id, const sf::Vector2f& val)
    {
        if (auto childElement = _element->InsertNewChildElement(id.c_str()))
        {
            SaveVec2Attr(childElement, val);
        }
    }

    void Serialization::SaveVec2Attr(const sf::Vector2f& val)
    {
        SaveVec2Attr(_element, val);
    }

    void Serialization::SaveVec2Attr(tinyxml2::XMLElement* element, const sf::Vector2f& val)
    {
        if (element)
        {
            element->SetAttribute("x", val.x);
            element->SetAttribute("y", val.y);
        }
    }

    void Serialization::SaveFloatRect(const std::string& id, const sf::FloatRect& val)
    {
        if (auto childElement = _element->InsertNewChildElement(id.c_str()))
        {
            SaveFloatRectAttr(childElement, val);
        }
    }

    void Serialization::SaveFloatRectAttr(const sf::FloatRect& val)
    {
        SaveFloatRectAttr(_element, val);
    }

    void Serialization::SaveFloatRectAttr(tinyxml2::XMLElement* element, const sf::FloatRect& val)
    {
        if (element)
        {
            element->SetAttribute("x", val.left);
            element->SetAttribute("y", val.top);
            element->SetAttribute("w", val.width);
            element->SetAttribute("h", val.height);
        }
    }

    void Serialization::SaveIntRect(const std::string& id, const sf::IntRect& val)
    {
        if (auto childElement = _element->InsertNewChildElement(id.c_str()))
        {
            SaveIntRectAttr(childElement, val);
        }
    }

    void Serialization::SaveIntRectAttr(const sf::IntRect& val)
    {
        SaveIntRectAttr(_element, val);
    }

    void Serialization::SaveIntRectAttr(tinyxml2::XMLElement* element, const sf::IntRect& val)
    {
        if (element)
        {
            element->SetAttribute("x", val.left);
            element->SetAttribute("y", val.top);
            element->SetAttribute("w", val.width);
            element->SetAttribute("h", val.height);
        }
    }

    void Serialization::SaveColor(const std::string& id, const sf::Color& val)
    {
        if (auto childElement = _element->InsertNewChildElement(id.c_str()))
        {
            SaveColorAttr(childElement, val);
        }
    }

    void Serialization::SaveColorAttr(const sf::Color& val)
    {
        SaveColorAttr(_element, val);
    }

    void Serialization::SaveColorAttr(tinyxml2::XMLElement* element, const sf::Color& val)
    {
        if (element)
        {
            element->SetAttribute("r", val.r);
            element->SetAttribute("g", val.g);
            element->SetAttribute("b", val.b);
            element->SetAttribute("a", val.a);
        }
    }

    void Serialization::SaveTexturePtr(const std::string& id, const std::string& texId)
    {
        if (auto childElement = _element->InsertNewChildElement(id.c_str()))
        {
            childElement->SetAttribute("val", texId.c_str());
        }
    }

    void Serialization::SaveVectorRect(const std::string& id, const std::vector<sf::IntRect>& vec)
    {
        if (auto childElement = _element->InsertNewChildElement(id.c_str()))
        {
            for (const auto& rect : vec)
            {
                if (auto rectElem = childElement->InsertNewChildElement("rect"))
                {
                    SaveIntRectAttr(rectElem, rect);
                }
            }
        }
    }

    void Serialization::SaveVecStr(const std::string& id, const std::vector<std::string>& vec)
    {
        if (auto childElement = _element->InsertNewChildElement(id.c_str()))
        {
            for (const auto& str : vec)
            {
                if (auto rectElem = childElement->InsertNewChildElement("item"))
                {
                    rectElem->SetAttribute("val", str.c_str());
                }
            }
        }
    }
}
