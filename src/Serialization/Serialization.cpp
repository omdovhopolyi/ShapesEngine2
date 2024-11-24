#include "Serialization.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlTexturesCollection.h"
#include "Utils/Assert.h"
#include <format>

namespace shen
{
    Serialization::Serialization(const std::string& filename)
    {
        LoadDocument(filename);
    }

    Serialization::Serialization(SystemsManager* systems, const std::string& filename)
        : _systems(systems)
    {
        LoadDocument(filename);
    }

    Serialization::Serialization(SystemsManager* systems, tinyxml2::XMLElement* element)
        : _systems(systems)
        , _element(element)
    {}

    void Serialization::LoadDocument(const std::string& filename)
    {
        _document = std::make_shared<tinyxml2::XMLDocument>();

        _document->LoadFile(filename.c_str());
        if (_document->Error())
        {
            Assert(false, std::format("[Serialization::LoadDocument] Can not read file '{}'", filename));
        }
    }

    void Serialization::SetupElement(const std::string& id)
    {
        if (_document)
        {
            _element = _document->FirstChildElement(id.c_str());
            Assert(_element, std::format("[Serialization::SetupElement] Can not find element '{}'", id));
        }
    }

    bool Serialization::IsValid() const
    {
        if (_document)
        {
            return !_document->Error();
        }
        
        return false;
    }

    Serialization Serialization::GetElement(const std::string& id) const
    {
        const auto child = _element->FirstChildElement(id.c_str());
        return Serialization{ _systems, child };
    }

    bool Serialization::GetBool(const std::string& id, bool defaultVal/* = false*/) const
    {
        if (const auto attr = _element->FindAttribute(id.c_str()))
        {
            return attr->BoolValue();
        }

        return defaultVal;
    }

    int Serialization::GetInt(const std::string& id, int defaultVal/* = 0*/) const
    {
        if (const auto attr = _element->FindAttribute(id.c_str()))
        {
            return attr->IntValue();
        }

        return defaultVal;
    }

    float Serialization::GetFloat(const std::string& id, float defaultVal/* = 0.f*/) const
    {
        if (const auto attr = _element->FindAttribute(id.c_str()))
        {
            return attr->FloatValue();
        }

        return defaultVal;
    }

    std::string Serialization::GetStr(const std::string& id, const std::string& defaultVal/* = {}*/) const
    {
        if (const auto attr = _element->FindAttribute(id.c_str()))
        {
            return attr->Value();
        }

        return defaultVal;
    }

    sf::Vector2f Serialization::GetVec2(const std::string& id, sf::Vector2f defaultVal) const
    {
        if (const auto child = _element->FirstChildElement(id.c_str()))
        {
            sf::Vector2f result;

            if (const auto xAttrib = child->FindAttribute("x"))
            {
                result.x = xAttrib->FloatValue();
            }

            if (const auto yAttrib = child->FindAttribute("y"))
            {
                result.y = yAttrib->FloatValue();
            }

            return result;
        }

        return defaultVal;
    }

    sf::Vector2i Serialization::GetIntVec2(const std::string& id, sf::Vector2i defaultVal) const
    {
        if (const auto child = _element->FirstChildElement(id.c_str()))
        {
            sf::Vector2i result;

            if (const auto xAttrib = child->FindAttribute("x"))
            {
                result.x = xAttrib->IntValue();
            }

            if (const auto yAttrib = child->FindAttribute("y"))
            {
                result.y = yAttrib->IntValue();
            }

            return result;
        }

        return defaultVal;
    }

    sf::FloatRect Serialization::GetFloatRect(const std::string& id, sf::FloatRect def/* = {}*/) const
    {
        if (const auto child = _element->FirstChildElement(id.c_str()))
        {
            sf::FloatRect rect;

            if (const auto attrib = child->FindAttribute("x"))
            {
                rect.left = attrib->FloatValue();
            }

            if (const auto attrib = child->FindAttribute("y"))
            {
                rect.top = attrib->FloatValue();
            }

            if (const auto attrib = child->FindAttribute("w"))
            {
                rect.width = attrib->FloatValue();
            }

            if (const auto attrib = child->FindAttribute("h"))
            {
                rect.height = attrib->FloatValue();
            }

            return rect;
        }

        return def;
    }

    sf::IntRect Serialization::GetIntRect(const std::string& id, sf::IntRect def/* = {}*/) const
    {
        if (const auto child = _element->FirstChildElement(id.c_str()))
        {
            sf::IntRect rect;

            if (const auto attrib = child->FindAttribute("x"))
            {
                rect.left = attrib->IntValue();
            }

            if (const auto attrib = child->FindAttribute("y"))
            {
                rect.top = attrib->IntValue();
            }

            if (const auto attrib = child->FindAttribute("w"))
            {
                rect.width = attrib->IntValue();
            }

            if (const auto attrib = child->FindAttribute("h"))
            {
                rect.height = attrib->IntValue();
            }

            return rect;
        }

        return def;
    }

    sf::IntRect Serialization::GetIntRect(sf::IntRect def) const
    {
        sf::IntRect rect;

        if (const auto attrib = _element->FindAttribute("x"))
        {
            rect.left = attrib->IntValue();
        }

        if (const auto attrib = _element->FindAttribute("y"))
        {
            rect.top = attrib->IntValue();
        }

        if (const auto attrib = _element->FindAttribute("w"))
        {
            rect.width = attrib->IntValue();
        }

        if (const auto attrib = _element->FindAttribute("h"))
        {
            rect.height = attrib->IntValue();
        }

        return rect;
    }

    sf::Color Serialization::GetColor(const std::string& id, sf::Color defaultVal) const
    {
        if (const auto child = _element->FirstChildElement(id.c_str()))
        {
            sf::Color result = sf::Color::White;

            if (const auto rAttrib = child->FindAttribute("r"))
            {
                result.r = rAttrib->IntValue();
            }

            if (const auto gAttrib = child->FindAttribute("g"))
            {
                result.g = gAttrib->IntValue();
            }

            if (const auto bAttrib = child->FindAttribute("b"))
            {
                result.b = bAttrib->IntValue();
            }

            if (const auto aAttrib = child->FindAttribute("a"))
            {
                result.a = aAttrib->IntValue();
            }

            return result;
        }

        return defaultVal;
    }

    sf::Texture* Serialization::GetTexturePtr(const std::string& id) const
    {
        if (!_systems)
        {
            Assert(_systems, "[Serialization::LoadTexturePtr] No systems");
            return nullptr;
        }

        if (const auto attr = _element->FindAttribute(id.c_str()))
        {
            if (const auto textureId = attr->Value())
            {
                if (auto textures = _systems->GetSystem<SfmlTexturesCollection>())
                {
                    return textures->GetTexture(textureId);
                }
            }
        }

        return nullptr;
    }

    std::vector<sf::IntRect> Serialization::GetVectorIntRect(const std::string& id) const
    {
        std::vector<sf::IntRect> result;

        if (!_systems)
        {
            Assert(_systems, "[Serialization::LoadVectorRect] No systems");
            return result;
        }

        if (const auto childElement = _element->FirstChildElement(id.c_str()))
        {
            auto rectElement = childElement->FirstChildElement("rect");
            while (rectElement)
            {
                result.push_back(Serialization(_systems, rectElement).GetIntRect());
                rectElement = rectElement->NextSiblingElement();
            }
        }

        return result;
    }

    std::vector<std::string> Serialization::GetVecStr(const std::string& id) const
    {
        std::vector<std::string> result;

        if (const auto childElement = _element->FirstChildElement(id.c_str()))
        {
            auto arrayElement = childElement->FirstChildElement("item");
            while (arrayElement)
            {
                if (const auto attrib = arrayElement->FindAttribute("val"))
                {
                    result.push_back(attrib->Value());
                }

                arrayElement = arrayElement->NextSiblingElement();
            }
        }

        return result;
    }

    sf::Transform Serialization::GetTransform() const
    {
        sf::Transform transform;

        if (const auto posElement = _element->FirstChildElement("position"))
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

        if (const auto rotationAttr = _element->FindAttribute("rotation"))
        {
            const float angle = rotationAttr->FloatValue();
            transform.rotate(angle);
        }

        if (auto scaleElement = _element->FirstChildElement("scale"))
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

    void Serialization::ForAllChildElements(const std::string& id, const std::string& elementId, const std::function<void(const Serialization&)>& func) const
    {
        if (const auto child = _element->FirstChildElement(id.c_str()))
        {
            auto element = child->FirstChildElement(elementId.c_str());
            while (element)
            {
                func(Serialization(_systems, element));

                element = element->NextSiblingElement();
            }
        }
    }

    void Serialization::ForAllChildElements(const std::string& elementId, const std::function<void(const Serialization&)>& func) const
    {
        auto element = _element->FirstChildElement(elementId.c_str());
        while (element)
        {
            func(Serialization(_systems, element));

            element = element->NextSiblingElement();
        }
    }

    void Serialization::SetBool(const std::string& id, bool val)
    {
        _element->SetAttribute(id.c_str(), val);
    }

    void Serialization::SetInt(const std::string& id, int val)
    {
        _element->SetAttribute(id.c_str(), val);
    }

    void Serialization::SetFloat(const std::string& id, float val)
    {
        _element->SetAttribute(id.c_str(), val);
    }

    void Serialization::SetStr(const std::string& id, const std::string& val)
    {
        _element->SetAttribute(id.c_str(), val.c_str());
    }

    void Serialization::SetVec2(const std::string& id, const sf::Vector2f& val)
    {
        if (auto child = _element->InsertNewChildElement(id.c_str()))
        {
            SetVec2Attr(child, val);
        }
    }

    void Serialization::SetFloatRect(const std::string& id, const sf::FloatRect& val)
    {
        if (auto child = _element->InsertNewChildElement(id.c_str()))
        {
            SetFloatRectAttr(child, val);
        }
    }

    void Serialization::SetIntRect(const std::string& id, const sf::IntRect& val)
    {
        if (auto child = _element->InsertNewChildElement(id.c_str()))
        {
            SetIntRectAttr(child, val);
        }
    }

    void Serialization::SetColor(const std::string& id, const sf::Color& val)
    {
        if (auto child = _element->InsertNewChildElement(id.c_str()))
        {
            SetColorAttr(child, val);
        }
    }

    void Serialization::SetTexturePtr(const std::string& id, const std::string& texId)
    {
        if (auto child = _element->InsertNewChildElement(id.c_str()))
        {
            child->SetAttribute("val", texId.c_str());
        }
    }

    void Serialization::SetVectorIntRect(const std::string& id, const std::vector<sf::IntRect>& vec)
    {
        if (auto childElement = _element->InsertNewChildElement(id.c_str()))
        {
            for (const auto& rect : vec)
            {
                if (auto rectElem = childElement->InsertNewChildElement("rect"))
                {
                    SetIntRectAttr(rectElem, rect);
                }
            }
        }
    }

    void Serialization::SetVecStr(const std::string& id, const std::vector<std::string>& vec)
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

    void Serialization::SetVec2Attr(tinyxml2::XMLElement* element, const sf::Vector2f& val)
    {
        if (element)
        {
            element->SetAttribute("x", val.x);
            element->SetAttribute("y", val.y);
        }
    }

    void Serialization::SetFloatRectAttr(tinyxml2::XMLElement* element, const sf::FloatRect& val)
    {
        if (element)
        {
            element->SetAttribute("x", val.left);
            element->SetAttribute("y", val.top);
            element->SetAttribute("w", val.width);
            element->SetAttribute("h", val.height);
        }
    }

    void Serialization::SetIntRectAttr(tinyxml2::XMLElement* element, const sf::IntRect& val)
    {
        if (element)
        {
            element->SetAttribute("x", val.left);
            element->SetAttribute("y", val.top);
            element->SetAttribute("w", val.width);
            element->SetAttribute("h", val.height);
        }
    }

    void Serialization::SetColorAttr(tinyxml2::XMLElement* element, const sf::Color& val)
    {
        if (element)
        {
            element->SetAttribute("r", val.r);
            element->SetAttribute("g", val.g);
            element->SetAttribute("b", val.b);
            element->SetAttribute("a", val.a);
        }
    }
}
