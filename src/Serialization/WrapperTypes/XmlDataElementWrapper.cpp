#include "XmlDataElementWrapper.h"
#include "ECS/SystemsManager.h"
#include "Utils/Assert.h"

namespace shen
{
    XmlDataElementWrapper::XmlDataElementWrapper(SystemsManager* systems, tinyxml2::XMLElement* element)
        : DataElementWrapper(systems)
        , _element(element)
    { }

    XmlDataElementWrapper::XmlDataElementWrapper(SystemsManager* systems)
        : DataElementWrapper(systems)
    { }

    void XmlDataElementWrapper::LoadFile(const std::string& filename)
    {
        _document = std::make_shared<tinyxml2::XMLDocument>();

        _document->LoadFile(filename.c_str());
        if (!_document->Error())
        {
            _element = _document->RootElement();
        }
        else
        {
            Assert(false, std::format("[XmlDataElementWrapper::LoadFile] Can not read file '{}'", filename));
        }
    }

    bool XmlDataElementWrapper::IsValid() const
    {
        return _element != nullptr;
    }

    std::shared_ptr<DataElementWrapper> XmlDataElementWrapper::GetChildElement(const std::string& id) const
    {
        if (_element)
        {
            return std::make_shared<XmlDataElementWrapper>(GetSystems(), _element->FirstChildElement(id.c_str()));
        }

        return nullptr;
    }

    bool XmlDataElementWrapper::HasElement(const std::string& id) const
    {
        if (_element)
        {
            return _element->FirstChildElement(id.c_str()) != nullptr;
        }
        
        return false;
    }

    bool XmlDataElementWrapper::GetBool(const std::string& id, bool defaultVal) const
    {
        if (_element)
        {
            if (const auto attr = _element->FindAttribute(id.c_str()))
            {
                return attr->BoolValue();
            }
        }

        return defaultVal;
    }

    int XmlDataElementWrapper::GetInt(const std::string& id, int defaultVal) const
    {
        if (_element)
        {
            if (const auto attr = _element->FindAttribute(id.c_str()))
            {
                return attr->IntValue();
            }
        }

        return defaultVal;
    }

    float XmlDataElementWrapper::GetFloat(const std::string& id, float defaultVal) const
    {
        if (_element)
        {
            if (const auto attr = _element->FindAttribute(id.c_str()))
            {
                return attr->FloatValue();
            }
        }

        return defaultVal;
    }

    std::string XmlDataElementWrapper::GetStr(const std::string& id, const std::string& defaultVal) const
    {
        if (_element)
        {
            if (const auto attr = _element->FindAttribute(id.c_str()))
            {
                return attr->Value();
            }
        }

        return defaultVal;
    }

    sf::Vector2f XmlDataElementWrapper::GetVec2(const std::string& id, sf::Vector2f defaultVal) const
    {
        if (_element)
        {
            if (const auto child = _element->FirstChildElement(id.c_str()))
            {
                auto childElement = XmlDataElementWrapper{ GetSystems(), child };
                const float x = childElement.GetFloat("x");
                const float y = childElement.GetFloat("y");

                return { x, y };
            }
        }

        return defaultVal;
    }

    sf::Vector2i XmlDataElementWrapper::GetIntVec2(const std::string& id, sf::Vector2i defaultVal) const
    {
        if (_element)
        {
            if (const auto child = _element->FirstChildElement(id.c_str()))
            {
                auto childElement = XmlDataElementWrapper{ GetSystems(), child };
                const int x = childElement.GetInt("x");
                const int y = childElement.GetInt("y");

                return { x, y };
            }
        }

        return defaultVal;
    }

    sf::FloatRect XmlDataElementWrapper::GetFloatRect(const std::string& id, sf::FloatRect defaultVal) const
    {
        if (_element)
        {
            if (const auto child = _element->FirstChildElement(id.c_str()))
            {
                auto childElement = XmlDataElementWrapper{ GetSystems(), child };
                const float x = childElement.GetFloat("x");
                const float y = childElement.GetFloat("y");
                const float w = childElement.GetFloat("w");
                const float h = childElement.GetFloat("h");

                return { x, y, w, h };
            }
        }

        return defaultVal;
    }

    sf::IntRect XmlDataElementWrapper::GetIntRect(const std::string& id, sf::IntRect defaultVal) const
    {
        if (_element)
        {
            if (const auto child = _element->FirstChildElement(id.c_str()))
            {
                auto childElement = XmlDataElementWrapper{ GetSystems(), child };
                const int x = childElement.GetInt("x");
                const int y = childElement.GetInt("y");
                const int w = childElement.GetInt("w");
                const int h = childElement.GetInt("h");

                return { x, y, w, h };
            }
        }

        return defaultVal;
    }

    sf::Color XmlDataElementWrapper::GetColor(const std::string& id, sf::Color defaultVal) const
    {
        if (_element)
        {
            if (const auto child = _element->FirstChildElement(id.c_str()))
            {
                auto childElement = XmlDataElementWrapper{ GetSystems(), child };
                const int r = childElement.GetInt("r");
                const int g = childElement.GetInt("g");
                const int b = childElement.GetInt("b");
                const int a = childElement.GetInt("a");

                return { static_cast<sf::Uint8>(r), static_cast<sf::Uint8>(g), static_cast<sf::Uint8>(b), static_cast<sf::Uint8>(a) };
            }
        }

        return defaultVal;
    }

    std::vector<sf::IntRect> XmlDataElementWrapper::GetVectorIntRect(const std::string& id) const
    {
        std::vector<sf::IntRect> result;

        if (_element)
        {
            if (const auto child = _element->FirstChildElement(id.c_str()))
            {
                auto item = child->FirstChildElement("item");
                while (item)
                {
                     auto wrapper = XmlDataElementWrapper{GetSystems(), item };
                     const auto x = wrapper.GetInt("x");
                     const auto y = wrapper.GetInt("y");
                     const auto w = wrapper.GetInt("w");
                     const auto h = wrapper.GetInt("h");

                     result.emplace_back(x, y, w, h);

                     item = item->NextSiblingElement("item");
                }
            }
        }

        return result;
    }

    std::vector<std::string> XmlDataElementWrapper::GetVecStr(const std::string& id) const
    {
        std::vector<std::string> result;

        if (_element)
        {
            if (const auto child = _element->FirstChildElement(id.c_str()))
            {
                auto item = child->FirstChildElement("item");
                while (item)
                {
                    auto wrapper = XmlDataElementWrapper{ GetSystems(), item };
                    const auto str = wrapper.GetStr("val");

                    result.push_back(str);

                    item = item->NextSiblingElement("item");
                }
            }
        }

        return result;
    }

    sf::Transform XmlDataElementWrapper::GetTransform(const std::string& id, const sf::Transform& defaultVal) const
    {
        if (_element)
        {
            if (const auto child = _element->FirstChildElement(id.c_str()))
            {
                auto wrapper = XmlDataElementWrapper{ GetSystems(), child };
                const int angle = GetInt("angle");
                const auto scale = wrapper.GetVec2("scale", { 1.f, 1.f });
                const auto position = wrapper.GetVec2("position");

                sf::Transform transform;
                transform.translate(position);
                transform.rotate(angle);
                transform.scale(scale);

                return transform;
            }
        }

        return defaultVal;
    }

    void XmlDataElementWrapper::SetBool(const std::string& id, bool val)
    {
        if (_element)
        {
            _element->SetAttribute(id.c_str(), val);
        }
    }

    void XmlDataElementWrapper::SetInt(const std::string& id, int val)
    {
        if (_element)
        {
            _element->SetAttribute(id.c_str(), val);
        }
    }

    void XmlDataElementWrapper::SetFloat(const std::string& id, float val)
    {
        if (_element)
        {
            _element->SetAttribute(id.c_str(), val);
        }
    }

    void XmlDataElementWrapper::SetStr(const std::string& id, const std::string& val)
    {
        if (_element)
        {
            _element->SetAttribute(id.c_str(), val.c_str());
        }
    }

    void XmlDataElementWrapper::SetVec2(const std::string& id, const sf::Vector2f& val)
    {
        if (_element)
        {
            if (auto child = _element->InsertNewChildElement(id.c_str()))
            {
                auto wrapper = XmlDataElementWrapper{ GetSystems(), child };
                wrapper.SetFloat("x", val.x);
                wrapper.SetFloat("y", val.y);
            }
        }
    }

    void XmlDataElementWrapper::SetFloatRect(const std::string& id, const sf::FloatRect& val)
    {
        if (_element)
        {
            if (auto child = _element->InsertNewChildElement(id.c_str()))
            {
                auto wrapper = XmlDataElementWrapper{ GetSystems(), child };
                wrapper.SetFloat("x", val.left);
                wrapper.SetFloat("y", val.top);
                wrapper.SetFloat("w", val.width);
                wrapper.SetFloat("h", val.height);
            }
        }
    }

    void XmlDataElementWrapper::SetIntRect(const std::string& id, const sf::IntRect& val)
    {
        if (_element)
        {
            if (auto child = _element->InsertNewChildElement(id.c_str()))
            {
                auto wrapper = XmlDataElementWrapper{ GetSystems(), child };
                wrapper.SetInt("x", val.left);
                wrapper.SetInt("y", val.top);
                wrapper.SetInt("w", val.width);
                wrapper.SetInt("h", val.height);
            }
        }
    }

    void XmlDataElementWrapper::SetColor(const std::string& id, const sf::Color& val)
    {
        if (_element)
        {
            if (auto child = _element->InsertNewChildElement(id.c_str()))
            {
                auto wrapper = XmlDataElementWrapper{ GetSystems(), child };
                wrapper.SetInt("r", val.r);
                wrapper.SetInt("g", val.g);
                wrapper.SetInt("b", val.b);
                wrapper.SetInt("a", val.a);
            }
        }
    }

    void XmlDataElementWrapper::SetVectorIntRect(const std::string& id, const std::vector<sf::IntRect>& vec)
    {
        if (_element)
        {
            if (const auto child = _element->InsertNewChildElement(id.c_str()))
            {
                for (const auto& item : vec)
                {
                    auto itemElement = child->InsertNewChildElement("item");
                    
                    auto wrapper = XmlDataElementWrapper{ GetSystems(), itemElement };
                    wrapper.SetInt("x", item.left);
                    wrapper.SetInt("y", item.top);
                    wrapper.SetInt("w", item.width);
                    wrapper.SetInt("h", item.height);
                }
            }
        }
    }

    void XmlDataElementWrapper::SetVecStr(const std::string& id, const std::vector<std::string>& vec)
    {
        if (_element)
        {
            if (const auto child = _element->InsertNewChildElement(id.c_str()))
            {
                for (const auto& str : vec)
                {
                    auto itemElement = child->InsertNewChildElement("item");

                    auto wrapper = XmlDataElementWrapper{ GetSystems(), itemElement };
                    wrapper.SetStr("val", str);
                }
            }
        }
    }

    void XmlDataElementWrapper::SetTransform(const std::string& id, const sf::Transform& transform)
    {
        if (_element)
        {
            //
        }
    }

    void XmlDataElementWrapper::ForAllChildren(const std::function<void(const DataElementWrapper& element)>& func) const
    {
        if (_element && func)
        {
            auto child = _element->FirstChildElement();

            while (child)
            {
                auto wrapper = XmlDataElementWrapper{ GetSystems(), child };

                func(wrapper);

                child = child->NextSiblingElement();
            }
        }
    }

    void XmlDataElementWrapper::ForAllChildren(const std::string& id, const std::function<void(const DataElementWrapper& element)>& func) const
    {
        if (_element && func)
        {
            auto child = _element->FirstChildElement(id.c_str());

            while (child)
            {
                auto wrapper = XmlDataElementWrapper{ GetSystems(), child };

                func(wrapper);

                child = child->NextSiblingElement(id.c_str());
            }
        }
    }
}
