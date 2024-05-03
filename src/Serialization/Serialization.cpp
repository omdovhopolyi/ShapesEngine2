#include "Serialization.h"

//#include "Resources/ShadersManager.h"

namespace shen
{
    bool LoadBool(const std::string& id, const tinyxml2::XMLElement* element, bool defaultVal/* = false*/)
    {
        if (const auto childElement = element->FirstChildElement(id.c_str()))
        {
            if (const auto attrib = childElement->FindAttribute("val"))
            {
                return attrib->BoolValue();
            }
        }

        return defaultVal;
    }

    int LoadInt(const std::string& id, const tinyxml2::XMLElement* element, int defaultVal/* = 0*/)
    {
        if (const auto childElement = element->FirstChildElement(id.c_str()))
        {
            if (const auto attrib = childElement->FindAttribute("val"))
            {
                return attrib->IntValue();
            }
        }

        return defaultVal;
    }

    float LoadFloat(const std::string& id, const tinyxml2::XMLElement* element, float defaultVal/* = 0.f*/)
    {
        if (const auto childElement = element->FirstChildElement(id.c_str()))
        {
            if (const auto attrib = childElement->FindAttribute("val"))
            {
                return attrib->FloatValue();
            }
        }

        return defaultVal;
    }

    std::string LoadStr(const std::string& id, const tinyxml2::XMLElement* element, const std::string& defaultVal/* = {}*/)
    {
        if (const auto childElement = element->FirstChildElement(id.c_str()))
        {
            if (const auto attrib = childElement->FindAttribute("val"))
            {
                return attrib->Value();
            }
        }

        return defaultVal;
    }

    sf::Vector2f LoadVec2(const std::string& id, const tinyxml2::XMLElement* element, sf::Vector2f defaultVal)
    {
        if (const auto childElement = element->FirstChildElement(id.c_str()))
        {
            return LoadVec2(childElement, defaultVal);
        }

        return defaultVal;
    }

    /*sf::Vector2f LoadVec3(const std::string& id, const tinyxml2::XMLElement* element, sf::Vector2f defaultVal)
    {
        if (const auto childElement = element->FirstChildElement(id.c_str()))
        {
            return LoadVec3(childElement, defaultVal);
        }

        return defaultVal;
    }*/

    sf::Vector2f LoadVec2(const tinyxml2::XMLElement* element, sf::Vector2f defaultVal)
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

    //glm::vec3 LoadVec3(const tinyxml2::XMLElement* element, glm::vec3 defaultVal/* = glm::vec3(0.f)*/)
    //{
    //    glm::vec3 result = glm::vec3(0.f);

    //    if (const auto xAttrib = element->FindAttribute("x"))
    //    {
    //        result.x = xAttrib->FloatValue();
    //    }

    //    if (const auto yAttrib = element->FindAttribute("y"))
    //    {
    //        result.y = yAttrib->FloatValue();
    //    }

    //    if (const auto zAttrib = element->FindAttribute("z"))
    //    {
    //        result.z = zAttrib->FloatValue();
    //    }

    //    return result;
    //}

    sf::FloatRect LoadRect(const std::string& id, const tinyxml2::XMLElement* element, sf::FloatRect def/* = {}*/)
    {
        if (const auto childElement = element->FirstChildElement(id.c_str()))
        {
            return LoadRect(childElement);
        }

        return def;
    }

    sf::FloatRect LoadRect(const tinyxml2::XMLElement* element)
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

    sf::Color LoadColor(const std::string& id, const tinyxml2::XMLElement* element, sf::Color defaultVal)
    {
        if (const auto childElement = element->FirstChildElement(id.c_str()))
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

    sf::Texture* LoadTexturePtr(const std::string& id, const tinyxml2::XMLElement* element)
    {
        return nullptr;

        /*auto texturesManager = ManagersProvider::Instance().GetOrCreateAssetsManager<OpenGLTexturesManager>();
        Texture* texture = nullptr;

        if (const auto childElement = element->FirstChildElement(id.c_str()))
        {
            if (const auto attrib = childElement->FindAttribute("val"))
            {
                const auto textureId = attrib->Value();
                texture = texturesManager->GetAsset(textureId);
            }
        }

        return texture ? texture : texturesManager->GetAsset("Empty");*/
    }

    //Shader* LoadShaderPtr(const std::string& id, const tinyxml2::XMLElement* element)
    //{
    //    /*if (const auto childElement = element->FirstChildElement(id.c_str()))
    //    {
    //        if (const auto attrib = childElement->FindAttribute("val"))
    //        {
    //            const auto shaderId = attrib->Value();
    //            auto shaders = ManagersProvider::Instance().GetOrCreateAssetsManager<ShadersManager>();
    //            return shaders->GetAsset(shaderId);
    //        }
    //    }*/

    //    return nullptr;
    //}

    std::vector<sf::FloatRect> LoadVectorRect(const std::string& id, const tinyxml2::XMLElement* element)
    {
        std::vector<sf::FloatRect> result;

        if (const auto childElement = element->FirstChildElement(id.c_str()))
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

    std::vector<std::string> LoadVecStr(const std::string& id, const tinyxml2::XMLElement* element)
    {
        std::vector<std::string> result;

        if (const auto childElement = element->FirstChildElement(id.c_str()))
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
