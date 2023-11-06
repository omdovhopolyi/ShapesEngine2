#include "Serialization.h"

#include "Game/ManagersProvider.h"
#include "Resources/OpenGLTexturesManager.h"

namespace shen
{
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

    glm::vec2 LoadVec2(const std::string& id, const tinyxml2::XMLElement* element, glm::vec2 defaultVal/* = {}*/)
    {
        if (const auto childElement = element->FirstChildElement(id.c_str()))
        {
            glm::vec2 result = glm::vec2(0.f);

            if (const auto xAttrib = childElement->FindAttribute("x"))
            {
                result.x = xAttrib->IntValue();
            }

            if (const auto yAttrib = childElement->FindAttribute("y"))
            {
                result.y = yAttrib->IntValue();
            }

            return result;
        }

        return defaultVal;
    }

    glm::vec3 LoadVec3(const std::string& id, const tinyxml2::XMLElement* element, glm::vec3 defaultVal/* = {}*/)
    {
        if (const auto childElement = element->FirstChildElement(id.c_str()))
        {
            glm::vec3 result = glm::vec3(0.f);

            if (const auto xAttrib = childElement->FindAttribute("x"))
            {
                result.x = xAttrib->IntValue();
            }

            if (const auto yAttrib = childElement->FindAttribute("y"))
            {
                result.y = yAttrib->IntValue();
            }

            if (const auto zAttrib = childElement->FindAttribute("z"))
            {
                result.z = zAttrib->IntValue();
            }

            return result;
        }

        return defaultVal;
    }

    Rect LoadRect(const std::string& id, const tinyxml2::XMLElement* element, Rect def/* = {}*/)
    {
        if (const auto childElement = element->FirstChildElement(id.c_str()))
        {
            return LoadRect(childElement);
        }

        return def;
    }

    Rect LoadRect(const tinyxml2::XMLElement* element)
    {
        Rect rect;

        if (const auto attrib = element->FindAttribute("x"))
        {
            rect.origin.x = attrib->FloatValue();
        }

        if (const auto attrib = element->FindAttribute("y"))
        {
            rect.origin.y = attrib->FloatValue();
        }

        if (const auto attrib = element->FindAttribute("w"))
        {
            rect.size.x = attrib->FloatValue();
        }

        if (const auto attrib = element->FindAttribute("h"))
        {
            rect.size.y = attrib->FloatValue();
        }

        return rect;
    }

    Texture* LoadTexturePtr(const std::string& id, const tinyxml2::XMLElement* element)
    {
        if (const auto childElement = element->FirstChildElement(id.c_str()))
        {
            if (const auto attrib = childElement->FindAttribute("val"))
            {
                const auto textureId = attrib->Value();
                auto texturesManager = ManagersProvider::Instance().GetOrCreateAssetsManager<OpenGLTexturesManager>();
                return texturesManager->GetAsset(textureId);
            }
        }

        return nullptr;
    }

    std::vector<Rect> LoadVectorRect(const std::string& id, const tinyxml2::XMLElement* element)
    {
        std::vector<Rect> result;

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
}
